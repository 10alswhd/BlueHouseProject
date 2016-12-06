//CS3211 Scanning Text

#include <stdio.h>

#include <string.h>

#include <ctype.h>

#include "mpi.h"

#define PRESENT_NO 0 //indicators for presence of string

#define PRESENT_YES 1

#define PRESENT_END 2

#define PRESENT_START 3

#define MAXDATA 50000

#define MAXNUMPROCS 20

char const searchString[15] = "CRYPTOSPORIDIUM";

FILE *fp;

int ii,kount;

char curr,*found=0;

char data[MAXDATA], *subdata=0, *substring1=0,*substring2=0,t1[15],t2[15],t3[MAXDATA/MAXNUMPROCS],senddata[MAXDATA];

int datainfo[1],myresult[2],mresult[MAXNUMPROCS],mstart[MAXNUMPROCS],mend[MAXNUMPROCS];

int i=0,j,myid,numprocs,x,low,high,msgtag;

int search=PRESENT_NO,foundflag;

MPI_Status status;

int datanum=0;

double tstart,tend;

//fn prototype

int searchFinal(int,int);

//fn main

void main(int argc, char *argv[]){

  MPI_Init(&argc,&argv);

  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  //

  //#####################################Master

  //

  if(myid==0){

    printf("*********************************************\n");

    printf("Minimum 2 process, However for bigger files may give error if few processes(Buffer Limit)\nMax processes currently set to %d\nMax String size currently set to %d\n\n",MAXNUMPROCS,MAXDATA);

    printf("0 means Not Found\n1 mean Found\n2 means found at End of Block\n3 means found at Start of Block\n");

    printf("*********************************************\n");

    tstart=MPI_Wtime();

    fp=fopen("text.txt","r");

    while(!feof(fp)){

      fscanf(fp,"%c",&curr);

      if((curr>='a' && curr<='z')||(curr>='A' && curr<='Z')){

     data[i++]=toupper(curr);//only alphabets and converted to uppercase

      }

    }

    datanum=strlen(data);

    tend=MPI_Wtime();

    printf("TIME: tstartup=%f10\n",tend-tstart);

    //#######################sending to slaves

    tstart=MPI_Wtime();

    x=datanum/numprocs;

    for(i=0;i<numprocs;i++){

      low=i*x;

      high=x+low;

           //assign last process extra chars if left

      if(i==numprocs-1){

     if(x*numprocs!=datanum){

       high=low+x+(datanum-(x*numprocs));

     }

      }

      datainfo[0]=high-low;

      mstart[i]=low;

      mend[i]=high;

      kount=0;

      for(ii=low;ii<high;ii++) senddata[kount++]=data[ii];

      MPI_Send(datainfo,1,MPI_INT,i,10,MPI_COMM_WORLD);

      MPI_Send(senddata,datainfo[0],MPI_CHAR,i,20,MPI_COMM_WORLD);

    }

    tend=MPI_Wtime();

    printf("TIME: tcomm1=%f10\n",tend-tstart);

  }

  //Bcast

  // MPI_Bcast(data,datanum,MPI_CHAR,0,MPI_COMM_WORLD); <-- somehow doesnt work so have to make point to point message passing

  //

  //

  //Slaves

  //

  MPI_Recv(datainfo,1,MPI_INT,0,10,MPI_COMM_WORLD,&status);

  MPI_Recv(senddata,datainfo[0],MPI_CHAR,0,20,MPI_COMM_WORLD,&status);

  tstart=MPI_Wtime();

  subdata=strncat(t3,&senddata[0],datainfo[0]);

  //Search Full String

  search=PRESENT_NO;

  found=strstr(subdata,searchString);

  if(found!=NULL){

    search=PRESENT_YES;

  }

  else{

    //search at start and end(for partial occourance)

    for(j=1;j<15;j++){

      //15 cos length of "cryptosporidium"=15

      //Search Front

      *t1=NULL;*t2=NULL;substring1=0;substring2=0;

      substring1=strncat(t1,subdata,j);

      substring2=strncat(t2,&searchString[15-j],j);

      if(strcmp(substring1,substring2)==0) {

     search=PRESENT_START;

     break;

      }

      //search end

      *t1=NULL;*t2=NULL;substring1=0;substring2=0;

      substring1=strncat(t1,&subdata[strlen(subdata)-j],j);

      substring2=strncat(t2,searchString,j);

      if(strcmp(substring1,substring2)==0){

     search=PRESENT_END;

     break;

      }

    }

   }

  tend=MPI_Wtime();

  //send result

  printf("Result on process id %d is %d TIME: tcomp%d=%f15\n",myid,search,myid,tend-tstart);

  myresult[0]=myid;

  myresult[1]=search;

  MPI_Send(myresult,2,MPI_INT,0,99,MPI_COMM_WORLD);

  //

  //end slave

  //

  if(myid==0){

    //master collects and computes final result

    tstart=MPI_Wtime();

    for(i=0;i<numprocs;i++){

      MPI_Recv(myresult,2,MPI_INT,MPI_ANY_SOURCE,99,MPI_COMM_WORLD,&status);

      mresult[myresult[0]]=myresult[1];

    }

    tend=MPI_Wtime();

    printf("TIME: tcomm2=%f10\n",tend-tstart);

    foundflag=1;

    tstart=MPI_Wtime();

    for(i=0;i<numprocs;i++){

      //printf("myid=%d result=%d\n",i,mresult[i]);

      if (mresult[i]==PRESENT_YES){

     foundflag=0;

     break;

      }

      else{

     if(mresult[i]!=PRESENT_NO){

       if(i!=numprocs-1){

         if((searchFinal(mstart[i],mend[i+1]))==1){

           foundflag=0;

         }

         else{

           if(i!=0){

          if((searchFinal(mstart[i-1],mend[i]))==1){

            foundflag=0;

          }

           }

         }

       }

     }

      }

    }

    tend=MPI_Wtime();

    if(foundflag==1){

      printf("Overall Final Result::Word %s NOT present\n",searchString);

    }

    else{

      printf("Overall Final Result::Word %s found in text!\n",searchString);

    }

    printf("TIME: tcompmaster=%f10\n",tend-tstart);

    printf("TIME TOTAL: tstartup+tcomm1+(tcomp0+tcomp1....+tcompn)+tcomm2+tcompmaster\n");

  }

  MPI_Finalize();

}

int searchFinal(int low1,int high1){

  //return 0 of not found, 1 if found

  *t3=NULL;

  subdata=strncat(t3,&data[low1],high1-low1);

  //Search Full String

  found=strstr(subdata,searchString);

  if(found!=NULL){

    return 1;

  }

  else{

    return 0;

  }

}
