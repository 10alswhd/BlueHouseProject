/*
* Cristina Silva <cristina.silva@openmailbox.org>
* GNU Public License
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ERROR_OPEN NULL

typedef struct
{
    int registry;
    char name[32];
    float gpa;
} tp_student;

int mainMenu( void );

tp_student readStudent();

bool insertOnFile( FILE* file, tp_student student );
tp_student searchStudentFromRegistry( FILE* file, int studentRegistry );

char* convertToUpper( char* nameStudent );
void printStudentData( tp_student stundet );

int main ( int argc, char *argv[] )
{
    const char nameFile[16] = "school.bin";
    const char modeOpen[4] = "a+b";

    FILE* file;

    file = fopen( nameFile, modeOpen );
    if ( file != ERROR_OPEN )
    {
		bool exitOption = false;
        do
        {
			switch ( mainMenu() )
			{
				case 0 :
				{
					exitOption = true;
					break;
				}
				case 1 :
				{
					if ( insertOnFile( file, readStudent() ) )
					{
						printf( "\nRegistry saved.\n\n" );
					} else
					{
						printf( "\nRegistry is not saved.\n\n" );
					}
					break;
				}
				case 2 :
				{
					printf( "\nWhat is the enrollment of a student?\t" );
					int registry;
					scanf( "%d", &registry );
					printStudentData( searchStudentFromRegistry( file, registry ) );
					break;
				}
				default :
					printf( "Invalid Choise.\n" );
			}
		} while( exitOption != true );
        
        fclose( file );
    } else
    {
        printf( "You can't open this file!" );
    }

    return 0;
}

int mainMenu( void )
{
    int choose = 0;
    printf( "Academic System\n\n" );
    printf( "1 - Insert Student\n" );
    printf( "2 - Search Student From Registry\n" );
    printf( "0 - Exit\n\n" );
    printf( "Number of Option:\t" );
    scanf( "%d", &choose );

    return choose;
}

tp_student readStudent()
{
	tp_student student;
	
    printf( "\nRegistry:\t" );
    scanf( " %d", &student.registry );
    printf( "Name:\t" );
    scanf( " %[^\n]s", student.name );
    strcpy( student.name, convertToUpper( student.name ) );
    printf( "GPA:\t" );
    scanf( "%f", &student.gpa );
    
    printStudentData( student );

    return student;
}

bool insertOnFile( FILE* file, tp_student student )
{
    printf( "\nYou really want save this stundent in the file? (y/n)\t" );
    char answer;
    scanf( " %c", &answer );
	if ( answer == 'y' )
	{
		return fwrite( &student, sizeof(student), 1, file );
	} else
	{
		return false;
	}
}

tp_student searchStudentFromRegistry( FILE* file, int studentRegistry )
{
	tp_student student;
	fseek( file, (studentRegistry-1) * sizeof(tp_student), SEEK_SET );
	fread( &student, sizeof(tp_student), 1, file );
	return student;
}

char* convertToUpper( char* nameStudent )
{
	int cont = 0;
	for( cont = 0; cont <= strlen( nameStudent ); cont++ )
	{
		nameStudent[ cont ] = toupper( nameStudent[ cont ] );
	}
	return nameStudent;
}

void printStudentData( tp_student student )
{
	printf( "\nStudent Registration:" );
	printf( "\nRegistry Number:\t%d", student.registry );
	printf( "\nName:\t%s", student.name );
	printf( "\nGPA:\t%.2f\n\n", student.gpa );
}
