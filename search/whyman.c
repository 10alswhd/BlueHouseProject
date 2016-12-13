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

char delimiter[] = " \t\n";
char *ptr;
char **history = NULL;
char **output = NULL;
unsigned int output_length = 0;
unsigned int history_length = 0;

int main() 
{	
	read_histfile();
	
	char input[256];
	while(1) 
	{	
		print_current_dir(); //bei jedem schleifendurchlauf wird das aktuelle verzeichnis ausgegeben
		free_output();	//output wird bei jedem schleifendurchlauf gefreed, damit im output array nur die werte des aktuellen inputs stehen
		
		fgets(input, sizeof(input), stdin); //liest die chars, die man in die konsole eingibt, in das char array input ein
		
		if(is_empty(input)) 
		{
			//Leere Zeile gefunden
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
			free_history();			//free_history, da ab hier kein neuer speicherplatz gebraucht wird
			
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
			char *pattern, *file;
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
					if(ptr != NULL) error_msg(0);
					else search_pattern(pattern, file);
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
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		(void) printf("%s $ ", cwd);
	else
	   	perror("getcwd() error");
	return EXIT_SUCCESS;
}

int date() 
{
	/* Obtain current time as seconds elapsed since the Epoch. */
	time_t current_time;
	current_time = time(NULL);

	/* Convert to local time format. */
	char* current_time_string;
	current_time_string = ctime(&current_time);

	/* Print to stdout. */
	//(void) printf("%s", c_time_string);
	push_to_output(current_time_string);
	return EXIT_SUCCESS;
}

int echo()
{
	ptr = strtok(NULL, delimiter);

	while(ptr != NULL)
	{
		push_to_output(ptr);		// abschnitt im output array speichern
		ptr = strtok(NULL, delimiter); 	// zum naechsten Abschnitt springen
		if(ptr == NULL || ((ptr != NULL && *ptr == '|'))) break;		// kein Nächster: verlasse Schleife	
		else push_to_output(" ");
		//printf(" ");		// ex. Nächster: Leerzeichen
	}
	
	unsigned int j;
	char outputcombined[256];
	for(j = 0; j < output_length; j++)
	{
		strcat(outputcombined, output[j]);
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
					//push_to_output(&outputcombined);
					/*unsigned int i; 
					for(i = 0; i < output_length; i++) // for schleife geht den gesamten output array durch
					{
						search_output_pattern(pattern, output[i]);
					 //sucht nach der pattern welche hinter grep steht, ausgeführt auf output[i]
					}*/
					search_output_pattern(pattern, outputcombined);	
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
	//push_to_output("\n");
	
	//(void) printf("\n");
	
	return EXIT_SUCCESS;
}

int change_directory()
{
	ptr = strtok(NULL, delimiter);
	//printf("Pfadname = [%s]\n", ptr);
	
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
				else //printf ("%s\n", ent->d_name);
				{
					push_to_output(ent->d_name);
					push_to_output("\n");
				}
			}
		closedir (dir);
		} 
		else 
		{
			/* could not open directory */
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
	// fopen will return if something goes wrong.  In that case errno will
	// contain the error code describing the problem (could be used with
	// strerror to produce a user friendly error message
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
		    printf("%s\n", fline);
		 
		}
    	}
   	return EXIT_SUCCESS;
}

void push_command(char *command) 
{
	history_length++;
	history = realloc(history, history_length * sizeof(char*));
	history[history_length - 1] = malloc(sizeof(char) * strlen(command) + 1);
	strcpy(history[history_length - 1], command);
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
		check = line;
		while(*check && (isdigit(*check) || isspace(*check)))
		{ 
			check++;
		}
		push_command(check);
	}
}

void write_histfile()
{
	FILE *fp;
	unsigned int temp;
	fp = fopen("./.hhush.histfile", "w");
	
	if(history_length > 1000)
	{
		temp = history_length - 1000;
	}
	else temp = 0;
	
	unsigned int i;
	for(i = temp; i < history_length + temp; i++)
		fprintf(fp, "%u %s", i, history[i]);
	fclose(fp);
}

int error_msg(int msg)
{
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
	}
   	return EXIT_SUCCESS;	
}	
