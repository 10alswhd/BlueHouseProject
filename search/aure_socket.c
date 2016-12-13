#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
 
#include<pthread.h> //for threading , link with lpthread

void *ear_Handler (void *);
void *client_connect(void *);
void *connection_handler(void *);
/***************************** setcolor.h *************************/
/* This is a Unix API for changing the color in console                                             
/******************************************************************/
#ifndef _SETCOLOR_H
#define _SETCOLOR_H

#define BLACK       "\033[22;30m"
#define RED         "\033[22;31m"
#define GREEN       "\033[22;32m"
#define YELLOW      "\033[22;33m"
#define BLUE        "\033[22;34m"
#define MAGENTA "\033[22;35m"
#define CYAN        "\033[22;36m"
#define WHITE       "\033[22;37m"
#define BGBALCK "\033[22;40m"
#define BGRED       "\033[22;41m"
#define BGGREEN "\033[22;42m"
#define BGYELLOW    "\033[22;43m"
#define BGBLUE      "\033[22;44m"
#define BGMAGENTA   "\033[22;45m"
#define BGCYAN      "\033[22;46m"
#define BGWHITE "\033[22;47m"
#define BGDEFAULT   "\033[22;49m"
#define BBLACK      "\033[1;30m"
#define BRED        "\033[1;31m"
#define BGREEN      "\033[1;32m"
#define BYELLOW "\033[1;33m"
#define BBLUE       "\033[1;34m"
#define BMAGENTA    "\033[1;35m"
#define BCYAN       "\033[1;36m"
#define BWHITE      "\033[1;37m"

static void setColor(const char* color);
static void setColor(const char* color)
{
    printf("%s",color);
}

#endif
 
#define PAUSE printf("Press any key to continue..."); fgetc(stdin);

typedef struct cli_data{
        char *des_IP;
        int des_Port;
}cli_data;

int connect_flag = 0;

int main(int argc , char *argv[])
{
    int client_sockfd;
    struct sockaddr_in server_addr;
    char message[80]  = {}; 
    int new_socket;
    char cli_lis_port[10] = {};
    int count;
    
    // /* listen thread
    pthread_t ear_thread;
    int *ear_sock;
    cli_data client_num = {NULL,0};
    //////

    // Useraccount Part
    char ac_name[80]   = {};  
    char listen_p[10] = {};
    char server_reply[1000] ;
    //////

    // List User part
    char List_msg[80] = {};  
    char serList_reply[1000] ;
    //////

    //  /*Get user data part
    char cmp_array[40] = {};
    char *search_User = NULL; 
    
    char List_for_s[80] = {};
    char *sepRecv  = NULL;  
    
    int flag1 = 0;
    char *des_IP = NULL;
    int des_Port = 0;
    //////

    // /* P2P connect
    pthread_t ptop_thread;
    int *p2p_sock;
    
    


    //Create socket
    client_sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (client_sockfd == -1)
    {
        printf("Could not create socket");
    }
         
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.103");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( 60001 );

    //Connect to remote server_addr

    /*
    printf("Choose u'r option,'l' for listing the online listing'c' for key in the user u want to chat'e' for leaving the chat room");
        
        scanf("%c", &choose);
        printf("%c", choose);
           while(choose != 'l' && choose != 'c' && choose == 'e')
        {
            scanf("%c", &choose);
        }
    */
    printf("Enter u'r listenning port\n");
    scanf("%s", cli_lis_port);
    
    
    /*
    if (new_socket = connect(client_sockfd , (struct sockaddr *)&server_addr , sizeof(server_addr)) < 0)
    {
        puts("connect error");
        return 1;
    }
    */
    //puts("stop!");
    while (new_socket = connect( client_sockfd , (struct sockaddr *)&server_addr , sizeof(server_addr) ) >= 0)
    {
        puts("Connected");

        // /* listenning thread create ///////////////
        
        ear_sock = malloc(1);
        *ear_sock = atoi(cli_lis_port);

         if(  pthread_create( &ear_thread , NULL ,  ear_Handler , (void*) ear_sock) < 0 )
        {
            perror("could not create thread");
            return 1;
        }

       
        ////////////////////////////////////////////////////////




        // Send Useraccount
        printf("Enter your account\n");
        scanf("%s", ac_name);
        for(count = 0;count < 10;count++)
            listen_p[count] = cli_lis_port[count];
        printf("Wellcome %s to the chaating room\n", ac_name);        
        strcat(message, ac_name);
        strcat(message, "#");
        strcat(message, listen_p);
        strcat(message, "\n");
        
        //printf("%s\n", message);


        
        if ( send( client_sockfd , message , strlen(message) , 0) < 0)    
            puts("Send failed");
        if ( recv( client_sockfd, server_reply, 1000, 0 ) < 0 ) 
            puts("recv failed");

        setColor(RED);
        puts(server_reply);
        setColor(WHITE);   
        
     
        //if(choose == 'l')
        //{
            // sending request for LIST

            strcat(List_msg, "List\n");

            if ( send( client_sockfd , List_msg , strlen(List_msg) , 0) < 0)
            {       
                puts("Send failed");
                return 1;
            }
            //puts("Data send");

            if ( recv( client_sockfd, serList_reply, 1000, 0 ) < 0 ) 
            {
                puts("recv failed");
                return 1;
            }
            //puts("recv succeed");
            setColor(GREEN);
            puts(serList_reply);
            setColor(WHITE);
            //char str[] = "   This, is a sample string.";
         //}   


        
        // Search for the user in List
        //if(choose == 'c' )
        //{    
            //while(client_num.des_IP != NULL)
            //{
                setColor(BLUE);
                
                printf("Type the User u want to talk to: \n"); 
               
                scanf("%s",cmp_array);                          // because cmp_array is a array to input the user fir search
                //printf("before asdasdasdasd %d\n", connect_flag);
                while(connect_flag == 1){ sleep(10);}
               // printf("after dsadasdasdaasd %d\n", connect_flag);
                search_User = strtok(cmp_array, "");    // but to compare with the sepRecv it's a (char *) so use the same strtok() to change it type
                //printf("%s\n", search_User);
                
                strcat(List_for_s, "List\n");

                if ( send( client_sockfd , List_for_s , strlen(List_for_s) , 0) < 0)
                {       
                    puts("Send failed");
                    return 1;
                }
                //puts("Data send");

                if ( recv( client_sockfd, serList_reply, 1000, 0 ) < 0 ) 
                {
                    puts("recv failed");
                    return 1;
                }

                sepRecv = strtok(serList_reply, " #\n");

                /* 
                    Looping the seperated Recv message and first compare the username to the search_User
                    flag start from 0 and user equal change to 1
                    when flag is 1 at the same time the sepRecv loop to the IP and record it, flag add to 2
                    when flag is 2 at the same time the sepRecv loop to the Port and record it, flag added
                */

                while(sepRecv != NULL)
                {
                    //printf("%s\n", sepRecv);  // output  and then add the result in the next line
                    sepRecv = strtok(NULL, " #\n");

                    if (flag1 == 2)
                    {
                        client_num.des_Port = atoi(sepRecv);
                        printf("des_Port GET !!\n");
                        flag1 = 0;
                    }

                     if(flag1 == 1)
                    {
                        client_num.des_IP = sepRecv;
                        printf("des_IP GET !!\n");
                        flag1++;
                    }

                    if(sepRecv != NULL)
                    {  
                        if( strcmp(search_User, sepRecv) == 0 )
                        flag1++;
                    }
               }

                printf("The destination IP is  %s\n", client_num.des_IP);
                printf("The destination Port is  %d\n", client_num.des_Port);    
                
                setColor(WHITE);

              //}       //p2p_sock = malloc(1);
                    //*p2p_sock = client_num;

                 if(  pthread_create( &ptop_thread , NULL ,  client_connect , (void*) &client_num) < 0 )
                 {
                     perror("could not create thread");
                     return 1;
                 }

       // }
        //if(choose == 'e')
      
     break;

    } // end of new_socket connect while loop

while(1)
{      sleep(30);}

} // end of main

void *ear_Handler(void *listen_p) // the thread function for each client to listen
{
    setColor(BGREEN);
    int listenning = *(int*)listen_p;
    int socket_ear , ear_new_socket , c , *ear_new_sock;
    struct sockaddr_in server , client;
    char *message;
     
    //Create socket
    socket_ear = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_ear == -1)
    {
        printf("Could not create ear_socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( listenning );
     
    //Bind
    if( bind(socket_ear,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        //return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_ear , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    setColor(WHITE);
    c = sizeof(struct sockaddr_in);
    if( (ear_new_socket = accept(socket_ear, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
        connect_flag = 1;
         
        //Reply to the client
        message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
        write(ear_new_socket , message , strlen(message));
         
        pthread_t sniffer_thread;
        ear_new_sock = malloc(1);
        *ear_new_sock = ear_new_socket;
         
        if(  pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) ear_new_sock) < 0 )
        {
            perror("could not create thread");
            //return 1;
        }
        else
            {printf("Connect Handler create succeed.\n");}
         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( sniffer_thread , NULL);
        puts("Handler assigned");
    }
     
    if (ear_new_socket<0)
    {
        perror("accept failed");
        //return 1;
    }
     
    sleep(30);
    
}
void *client_connect(void *client_data)  // a thread make a client to connect to another client
{
    setColor(YELLOW);
    cli_data data = *(cli_data*)client_data;
    printf("%s\n", data.des_IP);
    printf("%d\n", data.des_Port);
    int client_sockfd;
    struct sockaddr_in client_addr;
    int p2p_new_socket;
    char client_message[80] = {};
    char message[80]  = {}; 
    char client_reply[1000] ;
    

     client_sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (client_sockfd == -1)
    {
        printf("Could not create socket");
    }
         
    client_addr.sin_addr.s_addr = inet_addr(data.des_IP);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons( data.des_Port );

    //Connect to remote client_addr   
    while (p2p_new_socket = connect(client_sockfd , (struct sockaddr *)&client_addr , sizeof(client_addr)) >= 0)
    {
        printf("Send the message to the server_side clinet\n");
        scanf("%s", message);
         strcat(client_message, message);

        if ( send( client_sockfd , client_message , strlen(message) , 0) < 0)    
            puts("Send failed");
        if ( recv( client_sockfd, client_reply, 1000, 0 ) < 0 ) 
            puts("recv failed");
        puts(client_reply);
        //puts("connect error");
        
    }
    if ( recv( client_sockfd, client_reply, 1000, 0 ) < 0 )  // client server-side connect's message (by ear-handler thread writen)
            puts("recv failed");       
    puts(client_reply);
    if ( recv( client_sockfd, client_reply, 1000, 0 ) < 0 )  // ear-handler thread make connection_handler threader thread's message
            puts("recv failed");
    puts(client_reply);
    setColor(WHITE);   
    
    
}
void *connection_handler(void *socket_desc)
{
    setColor(BMAGENTA);
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char message1[5000] ;
    char client_message2[2000];
     
    //Send some messages to the client
    strcpy(message1, "Greetings! I am your connection handler\n");
    write(sock , message1 , strlen(message1));

    memset(message1,0,sizeof(message1));
     
       strcpy(message1,  "Now type something and i shall repeat what you type \n");
    write(sock , message1 , strlen(message1));


     
    //Receive a message from client
    while( (read_size = recv(sock , client_message2 , 2000 , 0)) > 0 )
    {
        //Send the message back to clientd

        printf("rec %s \n",client_message2);
        write(sock , client_message2 , strlen(client_message2));
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    //Free the socket pointer
    free(socket_desc);
    setColor(BGWHITE);
    return 0;
}
