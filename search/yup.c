#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//to do
//variablen umbennen wo nötig
//Quellcode richtig kommentieren
//history [n]
//void -> int !!!methoden ändern!!!
//quellenangaben! (grep date print_directory)

// 	compile:		gcc -Wall -ggdb -std=c99 -lm hhush.c -o hhush


int print_current_dir();
int error_msg();
int is_empty();
int date();
int echo();
int change_directory();
int print_directory();
int search_pattern();
void push_command();
int print_history();
void print_full_history();
void free_history();
void write_histfile();
void read_histfile();
void push_to_output();
void print_output();
void free_output();
int search_output_pattern();
int search_echo_pattern();

char delimiter[] = " \t\n";
char *ptr;
char **history = NULL;
char **output = NULL;
unsigned int output_length = 0;
unsigned int history_length = 0;

int main() 
{	
	FILE* pfilehandle;
	if((pfilehandle = fopen(".hhush.histfile", "r")) == NULL)  //falls kein histfile besteht wird hier eins erstellt
	{
		pfilehandle = fopen(".hhush.histfile", "w");
		fclose(pfilehandle);
	}
	
	read_histfile();
	
	char input[256];
	while(1) 
	{	
		print_current_dir(); //bei jedem schleifendurchlauf wird das aktuelle verzeichnis ausgegeben
		free_output();	//output wird bei jedem schleifendurchlauf gefreed, damit im output array nur die werte des aktuellen inputs stehen
		
		fgets(input, sizeof(input), stdin); //liest die chars, die man in die konsole eingibt, in das char array input ein
		
		if(is_empty(input)) 
		{
			//Leere Zeile gefunden, while schleife wird von neu gestarted
			continue;
		}
		
		push_command(input);   //pushed den input in das array, welches die history beinhaltet
		
		//initialisieren und ersten Abschnitt erstellen
		ptr = strtok(input, delimiter);
		
		
		if(strncmp(ptr, "date", 5) == 0)   //date anfang
		{
			ptr = strtok(NULL, delimiter);    //pipe abfrage
			if(ptr != NULL && *ptr == '|')
			{
				date();
				
				ptr = strtok(NULL, delimiter);
				if(ptr == NULL) 		//fehlermeldung falls nach dem pipe-symbol nichts steht
				{
					error_msg(0);
					continue;
				}
				if(strncmp(ptr, "grep", 5) == 0)  //verbindung mit grep abfrage
				{
					char *pattern;
					ptr = strtok(NULL, delimiter); // rückt den pointer auf die pattern
					if(ptr == NULL) 
					{
						error_msg(0);
					}
					else
					{
						pattern = ptr;		// der wert von ptr wird pattern zugewiesen
					
						ptr = strtok(NULL, delimiter);
						if(ptr != NULL) error_msg(0);
						else 
						{
							unsigned int i; 
							for(i = 0; i < output_length; i++) // for schleife geht den gesamten output array durch
							{
								search_output_pattern(pattern, output[i]);  //sucht nach der pattern welche hinter grep steht, ausgeführt auf output[i]
							}				
						}

					}
				}
			}
			else if(ptr != NULL) error_msg(0); //falls außer dem pipe symbol irgendetwas nach date steht: invalid arguments
			else // wenn keiner der fälle eintrifft, führe date durch
			{
				date();   //speichert das ergebnis der date methode im output array
				print_output();//gibt das output array aus
			}
			
		}
		else if(strncmp(ptr, "exit", 5) == 0)
		{
			write_histfile(); 		//speichert die letzten 1000 einträge der history im .histfile
			free_history();			//vor beenden der shell wird alles gefreed
			free_output();
			
			return EXIT_SUCCESS;
		}
		else if(strncmp(ptr, "echo", 5) == 0)
		{	
			echo();
		}
		else if(strncmp(ptr, "cd", 3) == 0)
		{
			change_directory();
		}
		else if(strncmp(ptr, "ls", 3) == 0)
		{
			ptr = strtok(NULL, delimiter);
			if(ptr != NULL && *ptr == '|')
			{
				print_directory();
				
				ptr = strtok(NULL, delimiter);
				if(ptr == NULL) 
				{
					error_msg(0);
					continue;
				}
				if(strncmp(ptr, "grep", 5) == 0)
				{
					char *pattern;
					ptr = strtok(NULL, delimiter); // rückt den pointer auf die pattern
					if(ptr == NULL) 
					{
						error_msg(0);
					}
					else
					{
						pattern = ptr;		// der wert von ptr wird pattern zugewiesen
					
						ptr = strtok(NULL, delimiter);
						if(ptr != NULL) error_msg(0);
						else 
						{
							unsigned int i; 
							for(i = 0; i < output_length; i++)
							{
								search_output_pattern(pattern, output[i]);
							}				
						}

					}
				}
			}
			else if(ptr != NULL) error_msg(0);
			else 
			{
				print_directory();
				print_output();
			}
		}	
			
		else if(strncmp(ptr, "grep", 5) == 0)
		{
			char *pattern, *file, *pipepattern;
			ptr = strtok(NULL, delimiter);
			if(ptr == NULL)
			{
				error_msg(0);
			}
			else
			{
				pattern = ptr;
			
				ptr = strtok(NULL, delimiter);
				if(ptr == NULL)
				{
					error_msg(0);
				}
				else
				{
					file = ptr;
			
					ptr = strtok(NULL, delimiter);
					if(ptr != NULL && *ptr == '|')
					{
						ptr = strtok(NULL, delimiter);
						if(ptr == NULL) 
						{
							error_msg(0);
							continue;
						}
						if(strncmp(ptr, "grep", 5) == 0)
						{
						
							ptr = strtok(NULL, delimiter);// rückt den pointer auf die pattern
							pipepattern = ptr;  // speichert den aktuellen string in pipepattern
							if(ptr == NULL) 
							{
								error_msg(0);
							}
							else
							{	// der wert von ptr wird pattern zugewiesen
								
								search_pattern(pattern, file); 
								//speichert das ergebnis von search_pattern im output,
								//so kann ich mit dem output weiterarbeiten und erneut im output nach einer neuen pattern suchen
								
								ptr = strtok(NULL, delimiter);
								
								if(ptr != NULL) error_msg(0); //invalid arguments wenn außer der pattern noch ein 2tes argument übergeben wird
								else 
								{
									unsigned int i; 
									for(i = 0; i < output_length; i++)
									{
										search_output_pattern(pipepattern, output[i]);
									}				
								}

							}
						}					
					}
					else if(ptr != NULL) error_msg(0);
					else 
					{
						//wenn nichts außer 2 argumente nach grep steht, wird grep normal ausgeführt
						search_pattern(pattern, file);
						print_output();				
					}
				}
			}
		}
		else if(strncmp(ptr, "history", 8) == 0)
		{
			ptr = strtok(NULL, delimiter);
			char *temp = strtok(NULL, delimiter);
		   	if(temp != NULL) error_msg(0);
			else if(ptr == NULL) print_full_history();
			else if(strncmp(ptr, "-c", 3) == 0) free_history();
			else if(ptr != NULL)
			{
				int i;
				i = atoi(ptr);		// macht aus dem string von ptr ein tatsächliches int und speichert es in i
				print_history(i);	// so kann ich print_history einen zahlenwert übergeben, mit dem die methode arbeiten kann
			}
			else error_msg(0);
		}
		else error_msg(1);
	}
}

int is_empty(const char *s)		//methode übernommen von: http://stackoverflow.com/questions/3981510/getline-check-if-line-is-whitespace (siehe antwort von User: Casablanca)
{
	while (*s!= '\0')		//methode, die überprüft ob const char *s leer ist (whitespace)
	{
		if (!isspace(*s))
			return 0;
		s++;
	}
	return 1;
}
	 
int print_current_dir()
{
	char cwd[256];
	if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s $ ", cwd);
	else perror("getcwd() error");
	return EXIT_SUCCESS;
}

int date() 
{
	//methode von http://en.wikipedia.org/wiki/C_date_and_time_functions übernommen und leicht verändert
	
	time_t current_time;
	current_time = time(NULL);
	// gibt die aktuelle zeit des systems in unixzeit zurück
	
	char* current_time_string;
	current_time_string = ctime(&current_time); 
	//konvertiert das time_t objekt in einen text, den ich ausgeben kann

	push_to_output(current_time_string);
	return EXIT_SUCCESS;
}

int echo()
{
	ptr = strtok(NULL, delimiter);

	while(ptr != NULL)
	{
		push_to_output(ptr);		// abschnitt im output array speichern
		ptr = strtok(NULL, delimiter); 	// zum naechsten abschnitt springen
		if(ptr == NULL || ((ptr != NULL && *ptr == '|'))) break;// kein nächster/pipe symbol verlasse schleife	
		else push_to_output(" ");//nächster abschnitt durch 1 leerzeichen gekennzeichnet
	}
	if(ptr != NULL && *ptr == '|')
	{
		ptr = strtok(NULL, delimiter);
		if(ptr == NULL) 		//fehlermeldung falls nach dem pipe-symbol nichts steht
		{
			error_msg(0);
		}
		if(strncmp(ptr, "grep", 5) == 0)  //verbindung mit grep abfrage
		{
			char *pattern;
			ptr = strtok(NULL, delimiter); // rückt den pointer auf die pattern
			if(ptr == NULL) 
			{
				error_msg(0);
			}
			else
			{
				pattern = ptr;		// der wert von ptr wird pattern zugewiesen
		
				ptr = strtok(NULL, delimiter);
				if(ptr != NULL)
				{
					error_msg(0);
				}
					
				else 
				{
					unsigned int i; 
					for(i = 0; i < output_length; i++) // for schleife geht den gesamten output array durch
					{
						(search_echo_pattern(pattern, output[i]));
					 	//suche nach der pattern welche hinter grep steht, ausgeführt auf output[i]
					}	
				}

			}
		}
		else error_msg(0);
	}
	else 
	{
		push_to_output("\n");
		print_output();
	}	
	return EXIT_SUCCESS;
}

int change_directory()
{
	ptr = strtok(NULL, delimiter);
	
	if(ptr == NULL) error_msg(0);
   	else 			
   	{
   		char *temp = strtok(NULL, delimiter);
   		if(temp != NULL) error_msg(0);
   		else if(chdir(ptr) == -1) error_msg(2); //  Überprüft, ob Verzeichnis existiert (-1 bei Fehler)
   	}
    	return EXIT_SUCCESS;
}

int print_directory()
{
	DIR *dir;
	struct dirent *ent;
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if((dir = opendir(cwd)) != NULL) 
		{
			/* print all the files and directories within directory */
			while((ent = readdir(dir)) != NULL) 
			{
				if(strncmp(ent->d_name, ".", 1) == 0 || 
					strncmp(ent->d_name, "..", 2) == 0) {}
				else
				{
					push_to_output(ent->d_name);
					push_to_output("\n");
				}
			}
		closedir (dir);
		} 
		else 
		{
			//falls verzeichnis nicht geöffnet werden kann
			perror ("");
			return EXIT_FAILURE;
		}
	}
	else perror("getcwd() error");
	return EXIT_SUCCESS;
}

int search_pattern(char *pattern, char *file)
{
	FILE *fp;
	char fline[256];
    	char *newline;
    	
	fp = fopen(file, "r");
	if (fp == NULL) 
	{
		error_msg(2);
		return EXIT_FAILURE;
    	} 
    	
    	while (fgets(fline, 256, fp) != NULL) 
    	{
		if ((newline = strchr(fline, '\n'))) 
		{
			*newline = '\0';
		}
		
		if (strstr(fline, pattern) != NULL) 
		{
		    // jede zeile im code bekommt seine eigene Zeile in der Shell,
		    // erzeugt durch: \n
		    push_to_output(fline);
		    push_to_output("\n");
		}
    	}
   	return EXIT_SUCCESS;
}

void push_command(char *command) 
{
	history_length++;	//da man mit 0 nicht rechnen kann, umgehe ich dieses problem indem ich am anfang length++ benutze,
				// und length-1 um die richtigen plätze im array zu finden
	history = realloc(history, history_length * sizeof(char*));
	history[history_length - 1] = malloc(sizeof(char) * strlen(command) + 1); //speicherreservierung, + 1 da im speicher für strings 1 extra platz reserviert werden muss
	strcpy(history[history_length - 1], command); // hier wird der command in das history array gespeichert
}
 
int print_history(int n)
{
	unsigned int i;
	unsigned int temp;
	if(n <= 0) 
	{
		error_msg(0);
		return EXIT_FAILURE;
	}
	else if(n > history_length) 
	{
		n = history_length;
		temp = 0;
		//temp wird =  0 damit falls n > history_length ist das gesamte array durchlaufen wird.
	}
	else temp = history_length - n;
	//printf("%u\n", history_length);
	// die for schleife beginnt bei temp(history länge - n) und gibt die n-letzten strings im array
	// der history aus
	for(i = temp; i < history_length; i++) 
	{
		// i < history_length geht die gesamte history durch, 
		// da history_length um 1 größer ist als die tatsächliche länge.
		// temp ist der zähler, der length - input (history(n)) rechnet
		printf("%u %s", i, history[i]);
	}
	return EXIT_SUCCESS;
}
 
void print_full_history() 
{
	unsigned int i;
	for(i = 0; i < history_length; i++) 
	{
		printf("%u %s", i, history[i]);
	}
}
 
void free_history() 
{
	if(history_length > 0) 
	{
		unsigned int i;
		for(i = 0; i < history_length; i++) 
		{
			free(history[i]);
		}
		if(history != NULL)
		{
			free(history);
		}
		history = NULL;
		history_length = 0;
	}
}

void read_histfile()
{
	FILE *fp;
	fp = fopen("./.hhush.histfile", "r");
	
	char line[256];
	char *check;
	
	while(fgets(line, sizeof(line), fp) != NULL)
	{
		//die schleife beseitigt die zahlen, die vor den inputs stehen
		//dies ist notwendig, da bei jedem push_command sowieso die histoy_length mit gepusht wird
		//deshalb beseitige ich mit while !isspace(); alle zahlen vor dem leerzeichen, 
		//gehe noch einen schritt weiter und was bleibt ist der input den man eingegeben hat
		check = line;
		while(!isspace(*check))
		{ 
			check++;
		}
		check++;
		push_command(check);
	}
}

void write_histfile()
{
	FILE *fp;
	unsigned int temp;
	fp = fopen("./.hhush.histfile", "w"); //öffnet das histfile, um darin zu schreiben
	
	if(history_length > 1000)
	{
		temp = history_length - 1000;
	}
	else temp = 0;
	
	//mit temp erreiche ich, das nur die letzten 1000 Einträge der history im histfile gespeichert werden
	
	unsigned int i;
	for(i = temp; i < history_length + temp; i++)
	{
		fprintf(fp, "%u %s", i, history[i]);	//fprintf schreibt direkt in das File hinein
	}
	fclose(fp);
}

int error_msg(int msg)
{
	//methode für die error messages, um es mir selbst leichter zu machen
	if(msg == 0)
	{
		(void) printf("invalid arguments\n");
	}
	
	else if(msg == 1)
	{
		(void) printf("command not found\n");
	}
	
	else if(msg == 2)
	{
		(void) printf("no such file or directory\n");
	}
	return EXIT_SUCCESS;
}

void push_to_output(char *command)
{
	// siehe history
	output_length++;
	output = realloc(output, output_length * sizeof(char*));
	output[output_length - 1] = malloc(sizeof(char) * strlen(command) + 1);
	strcpy(output[output_length - 1], command);
}

void free_output()
{
	if(output_length > 0) 
	{
		unsigned int i;
		for(i = 0; i < output_length; i++) 
		{
			free(output[i]);
		}
		if(output != NULL)
		{
			free(output);
		}
		output = NULL;
		output_length = 0;
	}
}

void print_output() 
{
	unsigned int i;
	for(i = 0; i < output_length; i++) 
	{
		printf("%s", output[i]);
	}
}

int search_output_pattern(char *pattern, char *line)
{
	char *newline;
	
	if((newline = strchr(line, '\n'))) 
	{
		*newline = '\0';
	}
	if (strstr(line, pattern) != NULL) 
	{
	    // jede zeile im code bekommt seine eigene Zeile in der Shell,
	    // erzeugt durch: \n
	    printf("%s\n", line);
	    return EXIT_SUCCESS;
	}
   	return EXIT_FAILURE;
}	

int search_echo_pattern(char *pattern, char *line)
{
	char *newline;
	
	if((newline = strchr(line, '\n'))) 
	{
		*newline = '\0';
	}
	if (strstr(line, pattern) != NULL) 
	{
		push_to_output("\n");
		print_output();
	  	// hier kann direkt der output geprinted werden, da ich in echo nur überprüfe ob die pattern in irgeneinem der token aus strtok
	    	// vorkommt, so werden trotzdem alle token geprinted
	    return EXIT_SUCCESS;
	}
   	return EXIT_FAILURE;
}
