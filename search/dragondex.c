/* Eric Entenberg
 * 11/24/2014
 * dragondex.c
 * implemented all 4 parts
 */

//included libraries
#include <stdio.h>
#include <string.h>

//constants
 # define MAX_LENGTH 40
 # define MAX_TEAM 100

//structures
struct dragon
{
	char name[MAX_LENGTH];
	char color[MAX_LENGTH];
};

struct collection
{
	struct dragon team[MAX_TEAM];
	int num_dragons;
};

//prototypes
void add_dragon(struct collection * dragon_index);
void remove_dragon(struct collection * dragon_index, char dragon_to_remove[]);
void search_dex(struct collection * dragon_dex, char search_dragon[]);
void print_color(struct collection * dragon_dex, char color[]);
//main function
int main()
    {
    	FILE * ifp = fopen("dragon.txt", "r");
    	int i;
    	int num_updates;
    	char user_command[7];
    	char color[8];

        struct collection dragon_dex;
        char dragon_to_remove[MAX_LENGTH];
        char search_dragon[MAX_LENGTH];
        dragon_dex.num_dragons = 0;
        fscanf(ifp , "%d", &num_updates);



        for(i=0; i<num_updates; i++)
        {


            fscanf(ifp, "%s", user_command);
            toupper(user_command);
            if(user_command == "ADD")
            {

                fscanf(ifp, "%s", dragon_dex.team[dragon_dex.num_dragons].name);
                fscanf(ifp, "%s", dragon_dex.team[dragon_dex.num_dragons].color);
                add_dragon(&dragon_dex);
                dragon_dex.num_dragons++;


            }

            if(user_command ==  "REMOVE")
            {

                fscanf(ifp, "%s", dragon_to_remove);
                remove_dragon(&dragon_dex, dragon_to_remove);

                dragon_dex.num_dragons--;



            }

            if(user_command ==  "SEARCH")
            {
                fscanf(ifp, "%s", search_dragon);
                search_dex(&dragon_dex, search_dragon);

            }

            if(user_command == "LIST")
              {
                fscanf(ifp, "%s", color);

                print_color(&dragon_dex, color);
              }


    }
    fclose(ifp);
    return 0;
    }


//other functions
void add_dragon(struct collection *dragon_index)
{

    printf("%s the %s dragon has been added to the team.\n", dragon_index->team[dragon_index->num_dragons].name, dragon_index->team[dragon_index->num_dragons].color);



    return;

}

void remove_dragon(struct collection * dragon_index, char dragon_to_remove[])
{
    int i;
    

    struct dragon temp;



    for(i=0; i<dragon_index->num_dragons; i++)
    {
        if(strcmp(dragon_index->team[i].name, dragon_to_remove) == 0)
        {
            strcpy(temp.name, dragon_index->team[i].name);
            strcpy(dragon_index->team[i].name, dragon_index->team[dragon_index->num_dragons].name);
            strcpy(dragon_index->team[dragon_index->num_dragons].name, '\0');

            strcpy(temp.color, dragon_index->team[i].color);
            strcpy(dragon_index->team[i].color, dragon_index->team[dragon_index->num_dragons].color);
            strcpy(dragon_index->team[dragon_index->num_dragons].color, '\0');



        }
    }
    printf("%s the %s dragon has been removed from the team.\n", temp.name, temp.color);
    return;
}

void search_dex(struct collection * dragon_index, char search_dragon[])
{
    int i, on_team=0;

    for(i=0; i<dragon_index->num_dragons; i++)
    {
        if(strcmp(search_dragon, dragon_index->team[i].name) == 0)
            {
                printf("%s the dragon is on the team.\n", dragon_index->team[i].name);
                on_team++;
            }

        if(on_team == 0)
            {
                printf("%s the dragon is not on the team.\n", dragon_index->team[i].name);
            }


    }

    return;

}

void print_color(struct collection * dragon_index, char color[])
{
    int i;

    printf("%s dragons:\n", color);

    for(i=0; i<dragon_index->num_dragons; i++)
    {

        if(strcmp(dragon_index->team[i].color, color) == 0)
            printf("%s\n", dragon_index->team[i].name);

    }

    printf("\n");

    return;
}
