#define MAX 128
#include <string.h>


struct student{
        int id;
        char pass[MAX];
        };
        
struct subjects{
       char name[MAX];
       char section[MAX];
       char units[MAX];
       char days[MAX];
       char time[MAX];
       char room[MAX];
       };
       
struct shop{
       char sname[MAX];
       char ssection[MAX];
       char sunits[MAX];
       char sdays[MAX];
       char stime[MAX];
       char sroom[MAX];
       };
       
struct shop sar[MAX];
       
struct subjects ar[10];

void subjlist(){    
strcpy(ar[0].name,"STATICS");
strcpy(ar[0].section,"EE");
strcpy(ar[0].units,"3");
strcpy(ar[0].days,"TH");
strcpy(ar[0].time,"0915-1045");
strcpy(ar[0].room,"AG1108");


strcpy(ar[1].name,"THERMO2");
strcpy(ar[1].section,"EE");
strcpy(ar[2].units,"3");
strcpy(ar[1].days,"MW");
strcpy(ar[1].time,"0915-1045");
strcpy(ar[1].room,"VL204");


strcpy(ar[2].name,"HUMALIT");
strcpy(ar[2].section,"EE");
strcpy(ar[2].units,"3");
strcpy(ar[2].days,"TH");
strcpy(ar[2].time,"0730-9000");
strcpy(ar[2].room,"VL204");



strcpy(ar[3].name,"NUMERIC");
strcpy(ar[3].section,"EE");
strcpy(ar[3].units,"3");
strcpy(ar[3].days,"F");
strcpy(ar[3].time,"0915-1015");
strcpy(ar[3].room,"VL406");


strcpy(ar[4].name,"LBYMEEN");
strcpy(ar[4].section,"EE2");
strcpy(ar[4].units,"3");
strcpy(ar[4].days,"W");
strcpy(ar[4].time,"1800-2100");
strcpy(ar[4].room,"VL310");


strcpy(ar[5].name,"ADMEMAT");
strcpy(ar[5].section,"EE");
strcpy(ar[5].units,"3");
strcpy(ar[5].days,"TH");
strcpy(ar[5].time,"1100-1200");
strcpy(ar[5].room,"VL204");


strcpy(ar[6].name,"INTFILO");
strcpy(ar[6].section,"EE");
strcpy(ar[6].units,"3");
strcpy(ar[6].days,"MW");
strcpy(ar[6].time,"0730-0900");
strcpy(ar[6].room,"VL306");


strcpy(ar[7].name,"LBYME13");
strcpy(ar[7].section,"EE2");
strcpy(ar[7].units,"3");
strcpy(ar[7].days,"M");
strcpy(ar[7].time,"1430-1730");
strcpy(ar[7].room,"SM108");


strcpy(ar[8].name,"LBYME15");
strcpy(ar[8].section,"EE2");
strcpy(ar[8].units,"1");
strcpy(ar[8].days,"M");
strcpy(ar[8].time,"1430-1730");
strcpy(ar[8].room,"SM112");

strcpy(ar[9].name,"LBYMEEB");
strcpy(ar[9].section,"EE2");
strcpy(ar[9].units,"3");
strcpy(ar[9].days,"W");
strcpy(ar[9].time,"1430-1730");
strcpy(ar[9].room,"VL208A");


}
