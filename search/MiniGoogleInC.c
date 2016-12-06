#include <stdio.h>       
#include <stdlib.h>      
#include <string.h>
#include "wordlist.h"
#include "stopwords.h"
#include <ctype.h>


typedef struct {
  char *keyword;
  char **urls;
  int *freq;
  int urlcount;
}Dictionary;

Dictionary *dictionary;

char *get_page(char *);
char **get_all_links(char *);
char *get_next_target(char *);
char **crawl_web(char *);
char **stopwords(char *);
char **getkeywords(char *);
char add_to_index(char*,char *);
char *add_pages_to_index(char **);
 void printDictionary();
 void searchDictionary(char *);


int main(){
    char **urls ;

    char ur[10];
    int l,k=0,i,count=0,j;
    strcpy(ur, "Homepage.html");
    urls = crawl_web(ur);   
/*
    for(i=0; urls[i] != NULL ; i++){
    keyword=getkeywords(urls[i]);
	}*/
	  //for(i=0; urls[i] != NULL ; i++){
	  	add_pages_to_index(urls);
	  //}
      printDictionary();
      char *searchString = (char *) malloc(sizeof(char) * 100 );
      printf("enter the search string");
    scanf("%s",searchString);

  searchDictionary(searchString);

   // for(i=0; urls[i] != NULL ; i++)
    //	printf("%s\n",urls[i] );

/*    for(i=0; keyword[i] != NULL ; i++)
		printf("\n Return keywords %s",keyword[i]);
*/

return 0;
}

char *get_page(char *url){
    char *str, ch;
    FILE *fptr;  
    fptr=fopen(url,"r");
    str = (char *) malloc(sizeof(char) * 100000);
        if(str==NULL){
            printf("\n Memory allocation error...");
            return NULL;
        }
        else if(fptr == NULL) {     
           printf("error to open the file\n");
        }
        else {
            ch=fgetc(fptr);
            int i=0;
            while(ch!=EOF){                            
            str[i]=ch;
            i++;
            ch=fgetc(fptr);
        }
    str[i]='\0';
        }
    free(str);
    return str;
}

char **get_all_links(char *htmlstring){
   
    char **url;
    int l;
    url = (char **) malloc(sizeof(char *) * 3000);
    char *stripedstring;
    stripedstring = (char *) malloc(sizeof(char) * 100000);
    stripedstring=strstr(htmlstring,"<a href=");
    int k=0;
    while(stripedstring!=NULL)
    {   
    url[k]=get_next_target(stripedstring);
    stripedstring=strstr(stripedstring,"\">");
    stripedstring=strstr(stripedstring,"<a href=");
    k++;
    }
    url[k] = NULL;
    return url;
}

char *get_next_target(char *string){        
	   char *p;
	   char *url;
	   url = (char *) malloc(sizeof(char) * 100000);
	   int i=0,j=0;
        p = (char *) malloc(sizeof(char) * 100000);
	   p = strstr(string,"<a href=");
        //printf("%s",p);
   
	   if(p!=NULL) {
	      p=p+9;
		  char *q = strstr(p,"\">");
		  char *link = (char *)malloc(sizeof(char)*(q-p+1));		  
		  strncpy(link, p, q-p);
		  link[q-p]='\0';
		//  printf("\n %s",link);
		  return link;
        }
}

char **crawl_web(char *seedpage)
{        
    
    int first=0,i=0,j;
    char *hcontent,**url;
    char **furl = (char **) malloc(sizeof(char *) * 500);
    furl[0] = seedpage;
    furl[1] = NULL;
    int last = 1;
    
    for(first=0; furl[first]!=NULL; first++){ 
        int count;
        hcontent=get_page(furl[first]);
        url = get_all_links(hcontent);
        for(i=0; url[i]!=NULL; i++)
        {
            for(j=0; furl[j]!=NULL; j++){
                if(strcmp(furl[j],url[i]) == 0)
                    count++;
            }
            if(count==0)
            {
                furl[last]=url[i];    
                last++;
            }
        
        }
        furl[last] = NULL;  
    }
     //for(i=0; url[i] != NULL ; i++)
   // printf("%s\n",url[i]);
    return url;
       
  }

  int compare_strings(char a[], char b[])
{
   int c = 0,i;
   for(i=0;i<=strlen(b);i++){
      if(b[i]>=65 && b[i]<=90)
       b[i]=b[i]+32;
   }
   while (a[c] == b[c])
   {
      if(a[c]=='\0'||b[c]=='\0')
      break;
      c++;
   }
   if (a[c] == '\0' && b[c] == '\0')
      return 0;
   else
      return -1;
}


  char **getkeywords(char *urls){

  	int l,k=0,i,count=0,j;
  	char **test = (char **) malloc(sizeof(char *) * 5000);
    char **stop = (char **) malloc(sizeof(char *) * 5000);
    char **sort = (char **) malloc(sizeof(char *) * 5000);
    char **frequency = (char **) malloc(sizeof(char *) * 5000);

  	char s[10];
  
   strcpy(s, "StopWords.txt");
    test=word_list(urls);
  	
 // for(i=0;test[i]!=NULL;i++)
   //printf("\n Total words : %s",test[i]);
    stop=stopwords(s);
/*
     for(i=0;stop[i]!=NULL;i++)
     printf("\n stopWords : %s",stop[i]);
*/
    *sort = (char *) malloc(sizeof(char ) * 1000);
   
       
    for(i=0; test[i]!=NULL ; i++) {   

        for(j=0; stop[j]!=NULL ; j++){

            if(compare_strings(stop[j], test[i])==0)
                break;
            }

        if(stop[j] == NULL) {
            sort[k] = (char *)malloc(sizeof(char)*strlen(test[i])+1);
            strcpy(sort[k] , test[i]) ;
            k++;
        }
    }
    sort[k]=NULL;


 /*for(k=0;sort[k]!=NULL;k++){
 frequency=freq(sort[k]);*/


 /*for(k=0;sort[k]!=NULL;k++)
  printf("%s ",sort[k]);
   */
    return sort;

  }

int checkKeywordInDictionary(char *keyword) {
  int index;
  for( index=0; dictionary[index].keyword!=NULL ; index++)
    if(strcmp(dictionary[index].keyword , keyword) == 0) 
      break;
  if(dictionary[index].keyword == NULL)
    return -1;
  else
    return index;
}

int checkURLInDictionary(int index, char *url) {
  int j;
  for(j=0; dictionary[index].urls[j]!=NULL ; j++)
    if(strcmp(dictionary[index].urls[j] , url ) == 0 )
      break;
  if(dictionary[index].urls[j]==NULL)
    return -1;
  else
    return j;
}

int dindex = 0;
char add_to_index(char *keyword , char *url) {
 // printf("\n Adding : %s : %s", keyword, url);
  int kwindex, urlindex;
  if(dindex==0) {
    dictionary = (Dictionary *)malloc(sizeof(Dictionary) * 20000);
    Dictionary dictionaryEntery;
    dictionaryEntery.keyword = (char *)malloc(sizeof(char) * 20000);
    dictionaryEntery.keyword = keyword;
    dictionaryEntery.urls = (char **)malloc(sizeof(char *)*20000);
    dictionaryEntery.urls[0] = url;
    dictionaryEntery.urls[1] = NULL;
    dictionaryEntery.freq = (int *)malloc(sizeof(int) * 20000);
    dictionaryEntery.freq[0] = 1;
    dictionaryEntery.freq[1] = -1;
    dictionaryEntery.urlcount = 1;
    dictionary[dindex++] = dictionaryEntery;
  } else {
    kwindex = checkKeywordInDictionary(keyword);
    if(kwindex==-1) {
      dictionary = (Dictionary *)
          realloc(dictionary, dindex+20000);
      if(dictionary==NULL)
        printf("\n Memory alloc error");
      Dictionary dictionaryEntery;
      dictionaryEntery.keyword = (char *)malloc(sizeof(char) * 20000);
      dictionaryEntery.keyword = keyword;
      dictionaryEntery.urls = (char **)malloc(sizeof(char *)*20000);
      dictionaryEntery.urls[0] = url;
      dictionaryEntery.urls[1] = NULL;
      dictionaryEntery.freq = (int *)malloc(sizeof(int) * 20000);
      dictionaryEntery.freq[0] = 1;
      dictionaryEntery.freq[1] = -1;
      dictionaryEntery.urlcount = 1;
      dictionary[dindex++] = dictionaryEntery;
    } else {
      urlindex = checkURLInDictionary(kwindex, url);
      if(urlindex==-1) {
        dictionary[kwindex].urls = (char **) 
            realloc(dictionary[kwindex].urls, 
              dictionary[kwindex].urlcount+20000);
        dictionary[kwindex].urls[dictionary[kwindex].urlcount] = url;
        dictionary[kwindex].urls[dictionary[kwindex].urlcount+1] = NULL;
        dictionary[kwindex].freq[dictionary[kwindex].urlcount] = 1;
        dictionary[kwindex].freq[dictionary[kwindex].urlcount+1] = -1;
        dictionary[kwindex].urlcount++;
      } else {
        dictionary[kwindex].freq[urlindex]++;
      }
    }
  } 
}

void printDictionary() {
  FILE *fp = fopen("Dictionary.txt","a");
  if(fp==NULL) {
    printf("File Open error");
  } else {
    int i;
    for( i=0; i<dindex; i++) {
      fprintf(fp, "\nKeyword::%s::", dictionary[i].keyword);
      //fprintf(fp, "\nurl count::%d::", dictionary[i].urlcount);
      int j;
      for(j=0; j<dictionary[i].urlcount; j++) 
        fprintf(fp, "\nurls::%s:freq :%d::", dictionary[i].urls[j], dictionary[i].freq[j]);
    }
    fclose(fp);
  }
}
void searchDictionary(char *searchString) {
  int index;
  for( index=0; dictionary[index].keyword!=NULL ; index++)
    if(strcmp(dictionary[index].keyword , searchString) == 0) 
      break;
  if(dictionary[index].keyword==NULL)
    printf("No URLs found");
  else {
    int i;
    for( i=0; i< dictionary[index].urlcount; i++)
      printf("URL is : %s\n", dictionary[index].urls[i]);
  }
}

char *add_pages_to_index(char **urlarray)

{
  int i,j=0;

  for(i=0; urlarray[i]!=NULL; i++) {
    char **keywords = getkeywords(urlarray[i]);
    for(j=0; keywords[j]!=NULL ; j++) {
     // printf("\n KW is : %s", keywords[j]);
      add_to_index(keywords[j] , urlarray[i]) ;
    }
  }
}
