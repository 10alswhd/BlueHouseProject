#include <stdio.h>
#include <time.h>
#include <sys/time.h>

char *mon_full[12] = {
  "January", "February", "March", "April",
  "May", "June", "July", "August",
  "September", "October", "November", "December"
};

char *mon_short[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

char *day_full[7] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

char *day_short[7]={
  "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

#define isleap(year) ((((year) % 4) == 0 && ((year) % 100) != 0) || ((year) % 400)==0)
#define YEAR_BASE 1900

static int day_tab[2][12] = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int date(char *,long int ,char **);

int date(char *format,long int timestamp,char **ret){

  char buf[11]={0};
  char *ret_tmp;
  char chr;
  int cnt=0;
  int mem_size=0,str_len=0;
  int num_tmp=0,wd,yd,fd,wk;
  struct tm *tm_date;
  time_t time_date;

  if(timestamp<0){
    time_date=time(NULL);
  }else{
    time_date=timestamp;
  }
    
  while((chr=*(format+cnt))){

    switch(chr){

      case '\\':
        ++cnt;
        ++mem_size;
        break;
      case 'U':
        mem_size+=10;
        break;
      case 'Y':
        mem_size+=4;
        break;
      case 'B':
      case 'D':
      case 'M':
        mem_size+=3;
        break;
      case 'l':
      case 'F':
        mem_size+=9;//l Wednesday,F September
        break;
      case 'g':
      case 'G':
      case 'h':
      case 'm':
      case 'd':
      case 'H':
      case 'i':
      case 'j':
      case 's':
      case 'A':
      case 'a':
      case 'n':
      case 't':
      case 'W':
      case 'y':
      case 'z':
        mem_size+=2;
        break;
      case 'I':
      case 'L':
      case 'w':
      default:
        ++mem_size;
        break;

    }

    ++cnt;

  }

  (*ret)=(char *)malloc(sizeof(char)*mem_size+1);
  memset((*ret),0x0,sizeof(char)*mem_size+1);
  ret_tmp=(*ret);
  
  cnt=0;
  tm_date=gmtime((time_t *)&time_date);

  while((chr=*(format+cnt))){

    switch(chr){

      case '\\':
        ++cnt;
        *(*ret)=*(format+cnt);
        ++(*ret);
        break;
      case 'U':
        sprintf(buf,"%ld",time_date);
        str_len=strlen(buf);
        memcpy((*ret),buf,str_len);
        (*ret)+=str_len;
        break;
      case 'Y':
        sprintf(buf,"%04d",(tm_date->tm_year)+YEAR_BASE);
        memcpy((*ret),buf,4);
        (*ret)+=4;
        break;
      case 'B':
        num_tmp=(((((long)time_date)-(((long)time_date)-
        ((((long)time_date)%86400)+3600)))*10)/864);
        while(num_tmp<0){
          num_tmp+=1000;
        }
        num_tmp=num_tmp%1000;
        sprintf(buf,"%03d",num_tmp);
        memcpy((*ret),buf,3);
        (*ret)+=3;
        break;
      case 'D':
        memcpy((*ret),day_short[tm_date->tm_wday],3);
        (*ret)+=3;
        break;
      case 'M':
        memcpy((*ret),mon_short[tm_date->tm_mon],3);
        (*ret)+=3;
        break;
      case 'l':
        str_len=strlen(day_full[tm_date->tm_wday]);
        memcpy((*ret),day_full[tm_date->tm_wday],str_len);
        (*ret)+=str_len;
        break;
      case 'F':
        str_len=strlen(mon_full[tm_date->tm_mon]);
        memcpy((*ret),mon_full[tm_date->tm_mon],str_len);
        (*ret)+=str_len;
        break;
      case 'g':
        num_tmp=tm_date->tm_hour%12;
        if(num_tmp==0) num_tmp=12;
        sprintf(buf,"%d",num_tmp);
        str_len=strlen(buf);
        memcpy((*ret),buf,str_len);
        (*ret)+=str_len;
        break;
      case 'G':
        sprintf(buf,"%d",tm_date->tm_hour);
        str_len=strlen(buf);
        memcpy((*ret),buf,str_len);
        (*ret)+=str_len;
        break;
      case 'h':
        num_tmp=tm_date->tm_hour%12;
        if(num_tmp==0) num_tmp=12;
        sprintf(buf,"%02d",num_tmp);
        str_len=strlen(buf);
        memcpy((*ret),buf,str_len);
        (*ret)+=2;
        break;
      case 'm':
        sprintf(buf,"%02d",(tm_date->tm_mon)+1);
        memcpy((*ret),buf,2);
        (*ret)+=2;
        break;
      case 'd':
        sprintf(buf,"%02d",tm_date->tm_mday);
        memcpy((*ret),buf,2);
        (*ret)+=2;
        break;
      case 'H':
        sprintf(buf,"%02d",tm_date->tm_hour);
        memcpy((*ret),buf,2);
        (*ret)+=2;
        break;
      case 'i':
        sprintf(buf,"%02d",tm_date->tm_min);
        memcpy((*ret),buf,2);
        (*ret)+=2;
        break;
      case 'j':
        sprintf(buf,"%d",tm_date->tm_mday);
        str_len=strlen(buf);
        memcpy((*ret),buf,str_len);
        (*ret)+=str_len;
        break;
      case 's':
        sprintf(buf,"%02d",tm_date->tm_sec);
        memcpy((*ret),buf,2);
        (*ret)+=2;
        break;
      case 'A':
        memcpy((*ret),(tm_date->tm_hour>=12 ? "PM" : "AM"),2);
        (*ret)+=2;
        break;
      case 'a':
        memcpy((*ret),(tm_date->tm_hour>=12 ? "pm" : "am"),2);
        (*ret)+=2;
        break;
      case 'n':
        sprintf(buf,"%d",(tm_date->tm_mon)+1);
        str_len=strlen(buf);
        memcpy((*ret),buf,str_len);
        (*ret)+=str_len;
        break;
      case 't':
        sprintf(buf,"%d",day_tab[isleap((tm_date->tm_year+YEAR_BASE))][tm_date->tm_mon]);
        memcpy((*ret),buf,2);
        (*ret)+=2;
        break;
      case 'W':
        wd=(tm_date->tm_wday==0 ? 6 : tm_date->tm_wday-1); /* weekday */
        yd=tm_date->tm_yday+1;  /* days since January 1st */

        fd=(7+wd-yd%7+1)%7; /* weekday (1st January) */

        /* week is a last year week (52 or 53) */
        if((yd<=7-fd)&&fd>3){
          wk=((fd==4||(fd==5&&isleap((tm_date->tm_year+YEAR_BASE-1)))) ? 53 : 52);
        }
        /* week is a next year week (1) */
        else if(isleap((tm_date->tm_year+YEAR_BASE))+365-yd<3-wd){
          wk=1;
        }
        /* normal week */
        else{
          wk=(yd+6-wd+fd)/7-(fd>3);
        }

        sprintf(buf,"%d",wk);  /* SAFE */
        str_len=strlen(buf);
        memcpy((*ret),buf,str_len);
        (*ret)+=str_len;
        break;
      case 'y':
        sprintf(buf,"%02d",((tm_date->tm_year)%100));
        memcpy((*ret),buf,2);
        (*ret)+=2;
        break;
      case 'z':
        sprintf(buf,"%d",tm_date->tm_yday);
        str_len=strlen(buf);
        memcpy((*ret),buf,str_len);
        (*ret)+=str_len;
        break;
      case 'I':
        sprintf(buf,"%d",tm_date->tm_isdst);
        memcpy((*ret),buf,1);
        ++(*ret);
        break;
      case 'L':
        sprintf(buf,"%d",(isleap((tm_date->tm_year+YEAR_BASE)) ? 1 : 0));
        memcpy((*ret),buf,1);
        ++(*ret);
        break;
      case 'w':
        sprintf(buf,"%d",tm_date->tm_wday);
        memcpy((*ret),buf,1);
        ++(*ret);
        break;
      default:
        *(*ret)=chr;
        ++(*ret);
        break;

    }

    ++cnt;

  }

  (*ret)=ret_tmp;

  return 0;

}

EXAMPLE CODE BELOW

#include <stdio.h>
#include <date.h>

int main(int argc,char **argv){

  char *format="\\suppor\\te\\d \\l\\e\\t\\t\\er\\s : \\Y\\m\\d\\H\\i\\s\\A\\a\\B\\D\\l\\F\\g\\G\\h\\I\\j\\L\\M\\n\\t\\w\\W\\U\\y\\Z \n\\ex\\a\\mp\\l\\e\\s : Y년 m월 d일 (A/a) H시 i분 s초 D l B F g G h I j L M n t w W U y z";
  char *ret=NULL;
  
  date(format,-1,&ret); 

  printf("%s\n",ret);

  free(ret);

  return 0;

}
