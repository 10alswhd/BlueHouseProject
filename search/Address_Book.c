//Simple Address Book To Add New Contact & Search For Existing Contact, Remove Contact(s) and Format the Address Book
//Needs to improve by saving contacts to a file.
//@John Almardeny
//26/06/2016

#include<stdio.h>
#include <string.h>
#include<stdlib.h>



int contact_index;
int option;
int number_of_contacts_found;
int *container; // dynamic array to hold -temporary- the user choice to remove specific contacts from the address book
int container_index; // index of the container, will be used as a reference of the work in the remove_contact function
struct Address_Book{   //Structure to contain the contact info
char f_name[31]; // first name
char l_name[31]; // last name
char phone[31]; // phone number
char fax[31]; // fax
char email[31]; // email
char address[56]; //address
} static contacts[100]; // array struct variable to hold every new entry and retrieve the existing ones

void main_options(); // shows the main options to the user
void add_new_contact(); // to add new contact
int receive_and_validate_input (int x); // to validate options and search_options chosen by user / numbers
void search_for_existing_contact(); // search for existing-specific contact via its first name, surname or phone number
void remove_contact(); // to remove existing-specific contact via its first name, surname or phone number
void format_addressBook(); // delete all the contacts (all the address_book content)
const char *validate_string_input(int x); // it validates the input in different cases and return a static string
void evaluate_contact_before_add(); // to check if the user inserted all empty fields
void select_contacts_to_remove();

typedef enum{
TRUE,
FALSE,
}boolean;
boolean evaluate_contact_before_save; //reference to "void evaluate_contact_before_add()"
boolean exit_from_remove_by_search;
int main (){
contact_index =0; // initialize the global variable
option =0; // initialize the global variable
printf ("Address Book \n Created by Yahya Almardeny \n");
printf ("***********************************************************************************************\n");


while (option != 5){ //while user does not choose to exit

main_options();

    switch (option){
        case 1: // option 1 is to add new contact
            add_new_contact();
            break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
        case 2: // option 2 is to search for existing contact
            search_for_existing_contact();
            break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
        case 3: // option 3 is to search for existing contact and remove it
            remove_contact();
            break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
        case 4: // option 4 is to delete the entire content of Address_Book and format it
            format_addressBook();
            break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
        case 5: // option 5 to exit
            printf("Bye!\n");
            exit(0); //simply exit
    }
}

return 0;
}





void main_options(){

printf("(1)Add New Contact, (2)Search for Contact, (3) Remove Contact, (4)Format Address Book, (5)Exit: ");
option = receive_and_validate_input(1); //get input and validate it, 1 for positive integers only between 1 to 5 , no empty input is accepted!
printf ("***********************************************************************************************\n");
}



void add_new_contact(){

if (contact_index!=100){ // check if there is a place for a new contact
evaluate_contact_before_save = FALSE; // to know if all the inputs are empty, so it will not save the contact
printf ("NEW CONTACT:\n");
printf ("-First Name: ");
strcpy(contacts[contact_index].f_name , validate_string_input(1)); //add first name in contact number[contact_index], validate it: it accepts any input even empty one!
printf ("-Surname: ");
strcpy(contacts[contact_index].l_name,  validate_string_input(1));   //add Surname in contact number[contact_index], validate it: it accepts any input even empty one!
printf ("-Phone: ");
strcpy(contacts[contact_index].phone , validate_string_input(2)); //it accepts digits only and can accept empty input
printf ("-Fax: ");
strcpy(contacts[contact_index].fax , validate_string_input(2));  //it accepts digits only and can accept empty input
printf ("-Email: ");
strcpy(contacts[contact_index].email , validate_string_input(3));  //it must contains "@" and dot ".", it accepts empty input as well
printf ("-Address: ");
strcpy(contacts[contact_index].address , validate_string_input(4));  //it accepts any input even empty one! up to 55 char/digit
contact_index++; // increment the contact_index for next input
evaluate_contact_before_add(); // the reference here is the boolean value of "evaluate_contact_before_save" which equals TRUE if there is any "nonempty" field/input
}

else {printf("Address Book is Full!\n");}//There no place to add more contacts!
printf ("\nWhat Next?:\n");
}


void search_for_existing_contact(){
int search_option, loop_var, loop_var1, results =0 /*variable to check if there is any contact has been found and how many they are!*/;
struct Address_Book temporary_contacts_holder[100];  /*to hold results to be printed out properly*/
printf("Type (1)to search by first name , (2)by Surname , (3)by phone number , (4)to show all contacts: "); // ask the user what is the way to search
            search_option = receive_and_validate_input(4); //get input and validate it


                    if (search_option == 1){ // if chose to search by name
                        printf("Insert the name: "); // ask to insert the name
                        char *name = malloc(25 * sizeof(char)); // declare a char pointer to hold the string(the name)
                        if (name == NULL){printf("Failure\n"); exit(0);} // report error if any happened
                        fgets (name, 25, stdin); // get the name
                        printf("\n--Search Results--\n");
                        for (loop_var=0 , loop_var1 =0; loop_var<contact_index ; loop_var++) // cycle through the contacts array , the reference is the contact_index value

                                {
                                     if (!(strcasecmp(contacts[loop_var].f_name , name))){ // if found the contact, this function returns 0
                                           strcpy(temporary_contacts_holder[loop_var1].f_name , contacts[loop_var].f_name); // copy the contact to the temporary_contacts_holder
                                           strcpy(temporary_contacts_holder[loop_var1].l_name , contacts[loop_var].l_name);
                                           strcpy(temporary_contacts_holder[loop_var1].phone , contacts[loop_var].phone);
                                           strcpy(temporary_contacts_holder[loop_var1].fax , contacts[loop_var].fax);
                                           strcpy(temporary_contacts_holder[loop_var1].email , contacts[loop_var].email);
                                           strcpy(temporary_contacts_holder[loop_var1].address , contacts[loop_var].address);
                                           loop_var1++;
                                           results++;

                                    }
                                }


                                    if (results>0){
                                            if (results>1){printf(" %d contacts found:\n", results);}
                                            else {printf("One contact found:\n");}
                                            printf("-----------------------------------------------------------\n");
                                            for (loop_var =0; loop_var<results ; loop_var++){// print info
                                                    printf(" First Name: %s" ,temporary_contacts_holder[loop_var].f_name ); // print info
                                                    printf(" Last Name: %s" ,temporary_contacts_holder[loop_var].l_name );  // print info
                                                    printf(" Phone Number: %s" ,temporary_contacts_holder[loop_var].phone );
                                                    printf(" Fax: %s", temporary_contacts_holder[loop_var].fax);
                                                    printf(" Email: %s", temporary_contacts_holder[loop_var].email);
                                                    printf(" Address: %s", temporary_contacts_holder[loop_var].address);
                                                    printf("-----------------------------------------------------------\n");

                                            }

                                    }

                                    if (results==0){ // if did not find any contact

                                            printf("Search did not find your contact\n\n");} //inform the user

                    free(name); //free the allocated memory

                    }


                    if (search_option == 2){ // if chose to search by name
                        printf("Insert the Surname: "); // ask to insert the name
                        char *sure_name = malloc(25 * sizeof(char)); // declare a char pointer
                        if (sure_name == NULL){printf("Failure\n"); exit(0);}
                        fgets (sure_name, 25, stdin); // get the name
                        printf("\n--Search Results--\n"); int r =0; //variable to check by the printf returning value if there any contact has be found!
                         for (loop_var=0 , loop_var1 =0; loop_var<contact_index ; loop_var++) // cycle through the contacts array , the reference is the contact_index value
                        {
                                    if (!strcasecmp(contacts[loop_var].l_name , sure_name)){ // if found the contact, this function returns 0
                                           strcpy(temporary_contacts_holder[loop_var1].f_name , contacts[loop_var].f_name); // copy the contact to the temporary_contacts_holder
                                           strcpy(temporary_contacts_holder[loop_var1].l_name , contacts[loop_var].l_name);
                                           strcpy(temporary_contacts_holder[loop_var1].phone , contacts[loop_var].phone);
                                           strcpy(temporary_contacts_holder[loop_var1].fax , contacts[loop_var].fax);
                                           strcpy(temporary_contacts_holder[loop_var1].email , contacts[loop_var].email);
                                           strcpy(temporary_contacts_holder[loop_var1].address , contacts[loop_var].address);
                                           loop_var1++;
                                           results++;

                                    }
                        }


                                    if (results>0){
                                            if (results>1){printf(" %d contacts found:\n", results);}
                                            else {printf("One contact found:\n");}
                                            printf("-----------------------------------------------------------\n");
                                            for (loop_var =0; loop_var<results ; loop_var++){ // print info
                                                    printf(" First Name: %s" ,temporary_contacts_holder[loop_var].f_name ); // print info
                                                    printf(" Last Name: %s" ,temporary_contacts_holder[loop_var].l_name );  // print info
                                                    printf(" Phone Number: %s" ,temporary_contacts_holder[loop_var].phone );
                                                    printf(" Fax: %s", temporary_contacts_holder[loop_var].fax);
                                                    printf(" Email: %s", temporary_contacts_holder[loop_var].email);
                                                    printf(" Address: %s", temporary_contacts_holder[loop_var].address);
                                                    printf("-----------------------------------------------------------\n");

                                            }

                                    }

                                    if (results==0){ // if not this function won't return 0

                                            printf("Search did not find your contact\n\n");} //inform the user


                    free(sure_name);//free the allocated memory
                    }


                    if (search_option == 3){ //if user chose to search by phone number
                        printf("Insert the phone number: ");
                        char *phone = malloc(25 * sizeof(char)); // declare a char pointer
                        if (phone == NULL){printf("Failure\n"); exit(0);}
                        fgets (phone, 25, stdin); // get the name
                        printf("\n--Search Results--\n");

                        for (loop_var=0 , loop_var1 =0; loop_var<contact_index ; loop_var++) // cycle through the contacts array , the reference is the contact_index value

                        {
                                    if (!strcasecmp(contacts[loop_var].phone , phone)){ // if found the contact, this function returns 0
                                           strcpy(temporary_contacts_holder[loop_var1].f_name , contacts[loop_var].f_name); // copy the contact to the temporary_contacts_holder
                                           strcpy(temporary_contacts_holder[loop_var1].l_name , contacts[loop_var].l_name);
                                           strcpy(temporary_contacts_holder[loop_var1].phone , contacts[loop_var].phone);
                                           strcpy(temporary_contacts_holder[loop_var1].fax , contacts[loop_var].fax);
                                           strcpy(temporary_contacts_holder[loop_var1].email , contacts[loop_var].email);
                                           strcpy(temporary_contacts_holder[loop_var1].address , contacts[loop_var].address);
                                           loop_var1++;
                                           results++;

                                    }
                        }


                        if (results>0){
                                    if (results>1){printf(" %d contacts found:\n", results);}
                                    else {printf("One contact found:\n");}
                                    printf("-----------------------------------------------------------\n");
                                            for (loop_var =0; loop_var<results ; loop_var++){
                                                    printf(" First Name: %s" ,temporary_contacts_holder[loop_var].f_name ); // print info
                                                    printf(" Last Name: %s" ,temporary_contacts_holder[loop_var].l_name );  // print info
                                                    printf(" Phone Number: %s" ,temporary_contacts_holder[loop_var].phone );
                                                    printf(" Fax: %s", temporary_contacts_holder[loop_var].fax);
                                                    printf(" Email: %s", temporary_contacts_holder[loop_var].email);
                                                    printf(" Address: %s", temporary_contacts_holder[loop_var].address);
                                                    printf("-----------------------------------------------------------\n");

                                            }

                                    }

                                    if (results==0){ // if did not find any contact

                                            printf("Search did not find your contact\n\n");} //inform the user
                free(phone);//free the allocated memory
                    }

            if (search_option == 4){
                for(loop_var = 0 ; loop_var < contact_index ; loop_var++){
                                                    printf(" First Name: %s" ,contacts[loop_var].f_name ); // print info
                                                    printf(" Last Name: %s" ,contacts[loop_var].l_name );  // print info
                                                    printf(" Phone Number: %s" ,contacts[loop_var].phone );
                                                    printf(" Fax: %s", contacts[loop_var].fax);
                                                    printf(" Email: %s", contacts[loop_var].email);
                                                    printf(" Address: %s", contacts[loop_var].address);
                                                    printf("-----------------------------------------------------------\n");


                }
                printf(" %d Contact(s) Found\n" , loop_var);
            }
printf ("\nWhat Next?:\n");

}


void remove_contact(){
int search_option, loop_var, loop_var1, results =0;
int temporary_holder[100]; // container array to hold the indexes that the search found
exit_from_remove_by_search = FALSE;
printf("Type (1) to remove by first name , (2) to remove by last name , (3) to remove by phone number: "); // ask the user what is the way to search and remove
    search_option = receive_and_validate_input(3); //get input and validate it
        if (search_option == 1){ // if chose to search by name
                        printf("Insert the name: "); // ask to insert the name
                        char *name = malloc(25 * sizeof(char)); // declare a char pointer
                        if (name== NULL){printf("Failure\n"); exit(0);}
                        fgets (name, 25, stdin); // get the name
                        printf("\n--Search Results--\n");
                        number_of_contacts_found=1;
                        for (loop_var=0 ; loop_var<contact_index ; loop_var++) // cycle through the contacts array , the reference is the contact_index value
                            {
                                     if (!(strcasecmp(contacts[loop_var].f_name , name))){ // if found, this function return 0
                                            printf(" [%d] First Name: %s" ,number_of_contacts_found,contacts[loop_var].f_name ); // print info
                                            printf("     Last Name: %s" ,contacts[loop_var].l_name );
                                            printf("     Phone Number: %s" ,contacts[loop_var].phone );
                                            printf("     Fax: %s", contacts[loop_var].fax);
                                            printf("     Email: %s", contacts[loop_var].email);
                                            printf("     Address: %s", contacts[loop_var].address);
                                            temporary_holder[number_of_contacts_found-1] = loop_var; // assign the index of the where the contact found to the the container first index and so on..

                                            number_of_contacts_found++;
                                     }
                            }
                                            if (number_of_contacts_found>1){
                                                select_contacts_to_remove();

                                           int x=0; int loop_counter=1;
                                            while(x<container_index){ // loop based on how many contacts to be removed chosen by user input
                                                for ( loop_var1 = temporary_holder[container[x]-1] ; loop_var1<contact_index ; loop_var1++){/*backward the elements by 1, starting from the index the contact found at*/
                                                    strcpy(contacts[loop_var1].f_name , contacts[loop_var1+1].f_name);
                                                    strcpy(contacts[loop_var1].l_name , contacts[loop_var1+1].l_name);
                                                    strcpy(contacts[loop_var1].phone ,  contacts[loop_var1+1].phone);
                                                    strcpy(contacts[loop_var1].fax , contacts[loop_var1+1].fax);
                                                    strcpy(contacts[loop_var1].email , contacts[loop_var1+1].email);
                                                    strcpy(contacts[loop_var1].address , contacts[loop_var1+1].address);


                                            }
                                            results++;
                                            contact_index--; // decrease the numbers of contacts to -at the end- terminate the loop, logically contacts should be reduced by 1
                                            x++;
                                            temporary_holder[container[x]-1] = temporary_holder[container[x]-1]-loop_counter;/*because the number of contacts is decreasing = what was at index 1 now is at index 0 and so on
                                            thus we need to decrement the value inside the temporary_holder based on how many loops have been done until now, that can be determined
                                            by using a counter*/
                                            loop_counter++;






                                     }

                                            }
                                    printf("-----------------------------------------------------------\n");
                                    /*inform the user about the result*/
                                    if (results==1){printf(" One contact has been removed\n\n");}
                                    if (results>1){printf(" %i contacts have been removed\n\n", results);}
                                    if (!(results) && (exit_from_remove_by_search!=TRUE)){printf("Search did not find your contact\n\n");}

    free(name);
    free(container);

}


                    if (search_option == 2){ // if chose to search by surname
                        printf("Insert the Surname: "); // ask to insert the surname
                        char *sure_name = malloc(25 * sizeof(char)); // declare a char pointer
                        if (sure_name == NULL){printf("failure\n"); exit(0);}
                        fgets (sure_name, 25, stdin); // get the name
                        printf("\n--Search Results--\n\n");
                        number_of_contacts_found=1;
                        for (loop_var=0 ; loop_var<contact_index ; loop_var++) // cycle through the contacts array , the reference is the contact_index value
                            {
                                     if (!(strcasecmp(contacts[loop_var].l_name , sure_name))){ // if found, this function return 0
                                            printf(" [%d] First Name: %s" ,number_of_contacts_found,contacts[loop_var].f_name ); // print info
                                            printf("     Last Name: %s" ,contacts[loop_var].l_name );
                                            printf("     Phone Number: %s" ,contacts[loop_var].phone );
                                            printf("     Fax: %s", contacts[loop_var].fax);
                                            printf("     Email: %s", contacts[loop_var].email);
                                            printf("     Address: %s", contacts[loop_var].address);
                                            temporary_holder[number_of_contacts_found-1] = loop_var; // assign the index of the where the contact found to the the container first index and so on..

                                            number_of_contacts_found++;
                                     }
                            }
                                            if (number_of_contacts_found>1){
                                                select_contacts_to_remove();

                                           int x=0; int loop_counter=1;
                                            while(x<container_index){ // loop based on how many contacts to be removed chosen by user input
                                                for ( loop_var1 = temporary_holder[container[x]-1] ; loop_var1<contact_index ; loop_var1++){/*backward the elements by 1, starting from the index the contact found at*/
                                                    strcpy(contacts[loop_var1].f_name , contacts[loop_var1+1].f_name);
                                                    strcpy(contacts[loop_var1].l_name , contacts[loop_var1+1].l_name);
                                                    strcpy(contacts[loop_var1].phone ,  contacts[loop_var1+1].phone);
                                                    strcpy(contacts[loop_var1].fax , contacts[loop_var1+1].fax);
                                                    strcpy(contacts[loop_var1].email , contacts[loop_var1+1].email);
                                                    strcpy(contacts[loop_var1].address , contacts[loop_var1+1].address);


                                            }

                                            results++;
                                            contact_index--; // decrease the numbers of contacts to -at the end- terminate the loop, logically contacts should be reduced by 1
                                            x++;
                                            temporary_holder[container[x]-1] = temporary_holder[container[x]-1]-loop_counter;/*because the number of contacts is decreasing = what was at index 1 now is at index 0 and so on
                                            thus we need to decrement the value inside the temporary_holder based on how many loops have been done until now, that can be determined
                                            by using a counter*/
                                            loop_counter++;






                                     }

                                            }
                                    printf("-----------------------------------------------------------\n");
                                    /*inform the user about the result*/
                                    if (results==1){printf(" One contact has been removed\n\n");}
                                    if (results>1){printf(" %i contacts have been removed\n\n", results);}
                                    if (!results){printf("Search did not find your contact\n\n");}

     free(sure_name);
    free(container);

}





                    if (search_option == 3){ //if user chose to search by phone number
                        printf("Insert the phone number: ");
                        char *phone_num = malloc(20 * sizeof(char)); // allocate memory to hold the phone inserted by user
                        fgets(phone_num, 20 , stdin); // get the phone number
                        printf("\n--Search Results--\n");
                        number_of_contacts_found=1;
                        for (loop_var=0 ; loop_var<contact_index ; loop_var++) // cycle through the contacts array , the reference is the contact_index value
                            {
                                     if (!(strcasecmp(contacts[loop_var].phone , phone_num))){ // if found, this function return 0
                                               printf(" [%d] First Name: %s" ,number_of_contacts_found,contacts[loop_var].f_name ); // print info
                                            printf("     Last Name: %s" ,contacts[loop_var].l_name );
                                            printf("     Phone Number: %s" ,contacts[loop_var].phone );
                                            printf("     Fax: %s", contacts[loop_var].fax);
                                            printf("     Email: %s", contacts[loop_var].email);
                                            printf("     Address: %s", contacts[loop_var].address);
                                            temporary_holder[number_of_contacts_found-1] = loop_var; // assign the index of the where the contact found to the the container first index and so on..

                                            number_of_contacts_found++;
                                     }
                            }
                                            if (number_of_contacts_found>1){
                                                select_contacts_to_remove();

                                           int x=0; int loop_counter=1;
                                            while(x<container_index){ // loop based on how many contacts to be removed chosen by user input
                                                for ( loop_var1 = temporary_holder[container[x]-1] ; loop_var1<contact_index ; loop_var1++){/*backward the elements by 1, starting from the index the contact found at*/
                                                    strcpy(contacts[loop_var1].f_name , contacts[loop_var1+1].f_name);
                                                    strcpy(contacts[loop_var1].l_name , contacts[loop_var1+1].l_name);
                                                    strcpy(contacts[loop_var1].phone ,  contacts[loop_var1+1].phone);
                                                    strcpy(contacts[loop_var1].fax , contacts[loop_var1+1].fax);
                                                    strcpy(contacts[loop_var1].email , contacts[loop_var1+1].email);
                                                    strcpy(contacts[loop_var1].address , contacts[loop_var1+1].address);


                                            }

                                            results++;
                                            contact_index--; // decrease the numbers of contacts to -at the end- terminate the loop, logically contacts should be reduced by 1
                                            x++;
                                            temporary_holder[container[x]-1] = temporary_holder[container[x]-1]-loop_counter;/*because the number of contacts is decreasing = what was at index 1 now is at index 0 and so on
                                            thus we need to decrement the value inside the temporary_holder based on how many loops have been done until now, that can be determined
                                            by using a counter*/
                                            loop_counter++;






                                     }

                                            }
                                    printf("-----------------------------------------------------------\n");
                                    /*inform the user about the result*/
                                    if (results==1){printf(" One contact has been removed\n\n");}
                                    if (results>1){printf(" %i contacts have been removed\n\n", results);}
                                    if (!results){printf("Search did not find your contact\n\n");}

     free(phone_num);
    free(container);

}

printf ("\nWhat Next?:\n");
}


void format_addressBook(){
int loop_var, loop_var1 , user_choice;
printf("Are You Sure That You Want To Delete All The Contacts? (1)Yes , (2) No! ");

    user_choice = receive_and_validate_input(2);

        if(user_choice==1){
             for (loop_var =0 ; loop_var<contact_index ; loop_var++){ // cycle through all the contacts/indices for contact_index times/loops
                 for (loop_var1=0 ; loop_var1<contact_index ; loop_var1++){
                        strcpy(contacts[loop_var1].f_name , contacts[loop_var1+1].f_name);
                        strcpy(contacts[loop_var1].l_name , contacts[loop_var1+1].l_name);
                        strcpy(contacts[loop_var1].phone , contacts[loop_var1+1].phone);
                        strcpy(contacts[loop_var1].fax , contacts[loop_var1+1].fax);
                        strcpy(contacts[loop_var1].email , contacts[loop_var1+1].email);
                        strcpy(contacts[loop_var1].address , contacts[loop_var1+1].address);
                        }
             }
             contact_index =0; // we have now no contacts
             printf("Address Book has been formatted successfully!\n\n"); //inform the user

        }
        printf ("***********************************************************************************************\n");

printf ("\nWhat Next?:\n");
}




int receive_and_validate_input (int x){ // function that receives and validates the user input and returns the validated user input to pass it to the input_matrix
    /* 1 for positive integers only between 1 to 5, 2 for positive integers only 1&2 , 3 for positive integers only 1 , 2 and 3 , 4 for any positive integer between 1 to 4*/

long validated_input; // the value to be returned
int y=0; //loop variable
while (y<6){
boolean reject_input = FALSE; // to determine if the user inserted a negative value to be a size of the matrix
int returned_value = -1;
char line[256];
char *line_pointer = line;
char *p_new = line;
char *p_old = line;
   if (fgets(line, sizeof(line), stdin)){//return 0 if not execute


                /*first remove spaces from the entire string*/
                while (*p_old != '\0'){// loop as long as has not reached the end of string
               *p_new = *p_old; // assign the current value the *line is pointing at to p
                    if (*p_new != ' '){p_new++;} // check if it is not a space , if so , increment p
                p_old++;// increment p_old in every loop
                }
                *p_new = '\0'; // add terminator

                /* check if the first char is (-) or (+) sign to point to next place*/
                if (*line_pointer== '+'){reject_input = TRUE; returned_value = 3;}
                if (*line_pointer == '-'){reject_input = TRUE; returned_value = 2;}// because it is a negative number

    while (*line_pointer != '\n' && reject_input == FALSE){ // no need to execute this if the number starts with + or -
            if (!(isdigit(*line_pointer))) {returned_value = 0; break;} // Illegal char found , will return 0 and stop because isdigit() returns 0 if the it finds non-digit
            line_pointer++;}

            returned_value=1;}
     /*it will return -1 if there is no input at all because while loop has not executed, will return >0 if successful, 0 if non-digit found , 2 if negative number inserted , 3 if inserted number start with +*/



if (returned_value==1){ /* if successful that means returned_value = 1 , then check if the string contains only the required numbers*/
                     validated_input = strtol(line, NULL, 10); // change the authentic string to long and assign it
                      if (x==1){
                            if (validated_input <= 0 || validated_input>5){printf("Invalid Input, Choose between 1 to 5!\n");}
                            else {break;}
                      }
                      if (x==2){
                            if (validated_input != 1 && validated_input !=2){printf("Invalid Input, Choose between 1 and 2!\n");}
                            else {break;}
                      }
                      if (x==3){
                            if (validated_input != 1 && validated_input !=2 && validated_input !=3 ){printf("Invalid Input, Choose between 1 to 3!\n");}
                            else {break;}
                      }
                      if (x==4){
                            if (validated_input != 1 && validated_input !=2 && validated_input !=3 && validated_input !=4 ){printf("Invalid Input, Choose between 1 to 4!\n");}
                            else {break;}
                      }
}




else if (returned_value==0){printf("Invalid Input, Insert Numbers Only!\n");} // if returned_value==0 that means a non-digit found
else if (returned_value==2){printf("Insert Positive Numbers Only!\n");} // if returned_value==2 that means a negative number found
else if (returned_value==3){printf("Insert Numbers Without + Sign!\n");} // if returned_value==3 that means a number starts with "+" sign found
else if (returned_value==-1){printf("Empty Input!\n ");} // if returned_value==-1 that means empty input (did not change returned_value)

y++;
if (y==6){printf("****Failure to receive any valid input, No More Retries****\n"); getchar(); exit(0);}
}

printf("\n");
return validated_input;
}



const char *validate_string_input(int x){
/* this is a char pointer function that points to a constant variable (cannot change its value)*/

if (x==1 || x==4){ //it accepts any input even if it is empty input
static char line[256]; // static means that this variable can be invoked and used outside this function

 if (x==1){while (strlen(fgets(line , sizeof(line), stdin))>31){ // count how many char is the input , if it exceeds the limit then report the error (there is a space for the terminator \0)
        printf("Insert no more than 30 char including spaces!\n");
          }
 }

 if (x==4){while (strlen(fgets(line , sizeof(line), stdin))>56){ // count how many char is the input , if it exceeds the limit then report the error, fgets()On success, the function returns the same str parameter.

        printf("Insert no more than 55 char/digit including spaces!\n");
          }
 }

    char *line_pointer = line;
        while (*line_pointer != '\n'){ // while did not reach the end of the line, this will not execute if user did not insert anything (i.e. hit enter only)
            if (*line_pointer != ' '){ // check if there is anything other than spaces
                evaluate_contact_before_save = TRUE; // if so , that means it is not empty and it does not only contain spaces!
            }
            line_pointer++;
        }


return line;
}


if (x==2){ // it accepts empty input but only digits
int y=0;
while (y<6){ // six retries available
boolean detect_non_digit = FALSE;
boolean detect_empty_input = TRUE;
        static char line[256]; // static means that this variable can be invoked and used outside this function
        char *line_pointer = line; // pointer to the string

while (strlen(fgets(line , sizeof(line), stdin))>31){ // count how many char is the input , if it exceeds the limit then report the error
        printf("Insert no more than 30 digit without spaces!\n");
          }

                while (*line_pointer != '\n'){ // while did not reach the end of the line
                        if (*line_pointer != ' '){// check if there is any non-space
                        detect_empty_input = FALSE; // if so, that means it is not empty input nor spaces input
                   }
                 if ((!isdigit(*line_pointer)) && (detect_empty_input == FALSE) ){ //check if there is any non-digit, isdigit returns 0 if did not find a digit
                    printf("Insert Only Numbers Without Spaces\n"); // inform the user
                    detect_non_digit = TRUE; // then change the boolean to true if detected non-digit
                    break; // break this while loop to go to the main while loop
                 }

                 line_pointer++; // if still search , move to next char
                }

    if (detect_non_digit == FALSE && detect_empty_input == FALSE) {evaluate_contact_before_save = TRUE; return line;} // terminate the main while loop and return the static line only if two conditions achieved (no empty input + all are digits)
    else if (detect_empty_input == TRUE){return line;} // if its empty input or it contains only spaces, return the line


    y++;
    }
}


if (x==3){ // it accepts empty input but must contain "@" and "." dot
int y=0;
while (y<6){
boolean detect_no_AT = TRUE; // detect if there is @
boolean detect_no_dot = TRUE; //detect if there is dot
boolean detect_empty_input = TRUE; // detect if it is empty input or spaces input
static char line[256]; // static means that this variable can be invoked and used outside this function
while (strlen(fgets(line , sizeof(line), stdin))>31){ // count how many char is the input , if it exceeds the limit then report the error, fgets() returns NULL if reach EOF and did not read any char
        printf("Insert no more than 30 char/digit including spaces!\n");
          }
            char *line_pointer = line; // pointer to the string
            while (*line_pointer != '\n'){ // while did not reach the end of the line
                   if (*line_pointer == '@'){ // if found the @
                        detect_no_AT = FALSE;
                   }

                   else if (*line_pointer == '.'){//if found dot
                        detect_no_dot = FALSE;
                   }
                   else if (*line_pointer != ' '){ // check if there is any input = check if it is not only spaces input
                        detect_empty_input = FALSE;
                   }

                line_pointer++; // move to next char
            }


        if (detect_no_dot == FALSE && detect_no_AT == FALSE ){evaluate_contact_before_save = TRUE; return line;}
        else if (detect_empty_input == TRUE){return line;} // if it's empty input or input contains only spaces
        else {printf("Invalid Email Address!\n");} // if it is not empty input and it does not contain @ nor dot

    y++;
}

}
printf("No More Retries!\n");
exit(0);
}


void evaluate_contact_before_add(){
if (evaluate_contact_before_save != TRUE){ // it becomes TRUE if there is even a single nonempty field inserted by the user
//remove the current contact because it is empty (it may contains only spaces!)
      strcpy(contacts[contact_index].f_name , contacts[contact_index+1].f_name);
      strcpy(contacts[contact_index].l_name , contacts[contact_index+1].l_name);
      strcpy(contacts[contact_index].phone , contacts[contact_index+1].phone);
      strcpy(contacts[contact_index].fax , contacts[contact_index+1].fax);
      strcpy(contacts[contact_index].email , contacts[contact_index+1].email);
      strcpy(contacts[contact_index].address , contacts[contact_index+1].address);
      contact_index--;
      printf("You did not insert any contact!\n\n");
      printf ("***********************************************************************************************\n");
      }
else{printf("\nDone!\n"); printf ("***********************************************************************************************\n");}
}


void select_contacts_to_remove(){
printf("\nInsert the number of the contact(s) to be removed , separate them by comma(,) e.g 1,2,3 or insert 101 to remove them all\n");
printf("or type main to back to main options\n");
int y=0;

while(y<6){

boolean detect_non_digit = FALSE; // reference to detect any non-digit input
boolean out_of_bound = FALSE; // reference to detect if user chose number bigger than the number of the resulted contacts after search
boolean detect_non_space = FALSE; // reference for detecting a space input only
boolean remove_all = FALSE; // reference if the user chose to remove all the contacts resulted in the search
container = calloc(number_of_contacts_found, sizeof(int)); // create dynamic array to hold the number of contacts the user chose
container_index=0; // variable
char line[256]; // String array to hold the entire input line
char *line_pointer = line;
char *line_pointer1 = line;
char *p_new = line;
char *p_old = line;

if (fgets(line, sizeof(line), stdin)){ // reads the entire line and then do the follows


        if (!(strcasecmp(line, "MAIN\n"))){ // I added \n because it already exists in the line array when user hits enter it is generated
        exit_from_remove_by_search = TRUE;
        break;
        }

while (*p_old != '\n'){ // remove spaces and check of there is any non-digit and any non-space input
        if (!(isdigit(*p_old))){ // return 0 if found non-digit
            if (*p_old != ' ' && *p_old != ','){// if found non-digit, check if it's a space of a comma which are legals, if not then it is a real non-digit
                detect_non_digit = TRUE; // if so, boolean becomes TRUE
                break; // break the loop, no need to check the rest of the input

             }
          }

        if (*p_old != ' '){ // check if there is any non-space input
              detect_non_space = TRUE; // if so, boolean becomes TRUE

        }

          *p_new = *p_old; // the process of removing spaces
          if (*p_new != ' '){p_new++;}
          p_old++;
    }


if (detect_non_digit == FALSE && detect_non_space == TRUE){// if all are legal, add comma to the end of the string and then add line-break
    *p_new = ','; // add comma anyway because at the end of the string
     p_new++; // increment to point to next place
    *p_new = '\n';

/* now because all are legal , continue and start the real work */
while (*line_pointer!='\n'){ // while did not reach the end of the string
int x =0;
    while(*line_pointer!=','){ // while still read before the comma
        char temporary_holder[4]; // because the highest number of the contacts can be saved is 100 (consists of 3 digits) and one more place for the terminator, all equals 4
        temporary_holder[x] = *line_pointer; // assign the char to the first index in the array
        x++; // increment for next index
        line_pointer++; // increment pointer to point to next place
            if (*line_pointer==','){ // now if the char is comma
            temporary_holder[x] = '\0';// add terminator to the end of the string
            container[container_index]= strtol(temporary_holder , NULL, 10); // change this authentic string to a number and add it to the container

            container_index++; // increment container_index for the next index in the container

            if (container[container_index-1] == 101) {remove_all = TRUE; break;} // if the number is 101 then change the boolean to true and break this loop
            if ((container[container_index-1] <=0 || container[container_index-1] > (number_of_contacts_found-1)) && remove_all == FALSE){// check if the user inserted a number less than or equals zero or greater than the number of contacts found during the search
                    printf("Invalid Input - out of range!\n");
                    out_of_bound = TRUE;
                    break;}  //break this while loop
    }
    }


if (out_of_bound == TRUE){ free (container); break;} // break this while loop too if invalid digit input found (out of bound) or if all the user chose to remove all and free the container
if (remove_all == TRUE){break;}
line_pointer++; // if everything is o.k, move to next place
}
} // end of if statement

else if (detect_non_digit == TRUE){printf("Invalid Input!\n"); free(container);} // if detect_non_digit is TRUE that means illegal input found
else if (detect_non_space == FALSE && detect_non_digit == FALSE ) {printf("Empty Input!\n"); free(container);} // if it is not non_digit and not non_space, it is empty input
}
if (remove_all == TRUE){ // if user chose to remove all the contacts resulted in the search then
        int x = 1;
    for ( ; x<number_of_contacts_found ; x++){ // fill in the container with numbers starts from 1 to number_of_contacts_found-1
        container[x-1] = x;
    }
    container_index = number_of_contacts_found-1; // and also change the container_index (which is a reference of the remove_contact function) to number_of_contacts_found-1
    break; // break the main while loop
}
if (out_of_bound == FALSE && detect_non_digit == FALSE && detect_non_space == TRUE){break;} // if all are legals , break the accepts the input and break the main loop

y++;
if (y==6){printf("No More Retries!\n");}
}

}
