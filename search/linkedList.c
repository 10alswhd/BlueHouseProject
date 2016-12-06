#include <stdio.h>
#typedef int integer
#typedef char *string
struct studentData {
   integer rollNumber;
   string name;
   student *link;
};
main()
{
  integer numOfStudents,i,rollNumber;
  char *str;
  struct studentData *student;
  student = (studentData*)malloc(sizeof(struct studentData)); 
  printf("Enter the number of students in the linked list:")
  scanf("%d", &numOfStudents);
  for (i=0;i<numOfStudents;i++) 
  {
   printf("Enter the name of the student");
   scanf("%s",&str);
   printf("Enter the Roll number") ;
   scanf("%d",&rollNumber);
   addStudent(&student,rollNumber,str);
  }
  printf("Enter the name of the student looking for");
  scanf("%s",&str);
  loc=search(&student,str);
  if(loc > -1)
  {
   printf("The location where we found the name was %d",loc);
  }
  else {
    printf("The string was not found");
  }
   printf("Enter the name of the student to delete");
  scanf("%s",&str);
  loc=delete(&student,str);
}

addStudent(struct studentData **stud, int roll, char *s)
{
   struct studentData *a;
   a=*stud;
   if {a->link==NULL} {
   //Empty list
   a->rollNumber = roll;
   a->name = s;
   a->link = NULL; 
   } 
   else 
   {
     // parse till the end of linked list and add the data
     while (a->link!=NULL) {
        a = a->link;
     } 
     a->rollNumber  = roll;
     a->name = s;
     a->link =NULL;
   }
  }
}

int search(struct studentData **a, char *s) 
{
  struct studentData *t;
  int loc = 0;
  t = *a;
  while(t->link != NULL) 
  { loc++;
    if {strcmp(t->name,s)} {
     return loc;
    }
   t=t->link;
  }
 return -1;
}

delete(struct studentData **a, char *s)
{
   struct studentData *t,*temp, *old;
   
   t = *a;
   while(t != NULL) 
   { 
     loc++;
     if {strcmp(t->name,s)} {
      //Found match Hence deleting
      if (loc==1) {
       // First element;
       a = &(t->link);
       free(t);
      }
      elseif (t->link == NULL) {
         old->link = NULL;
      } else {
         old->link = t->link;
         free(t);
      }
     }
   old = t;  
   t=t->link;
    
   }
  

}
