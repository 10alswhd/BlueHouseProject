#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#if (defined(__unix__) || defined(unix)) && !defined(USG)
    #include <sys/param.h>
#endif
#ifdef __APPLE__
    #include <sys/types.h>
    #include <sys/sysctl.h>
#elif __linux
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <time.h>
    #include <unistd.h>
#endif 


int isNumber(char str[])
{
    int i=0;
    int len = strlen(str);
    for (i=0; i<len; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int GetPIDByName(char* pidName)
{
    FILE *fp;
    char pidofCmd[50]={0};
    int pidValue=-1;
    
    if(pidName != 0) {
        strcpy(pidofCmd, "pidof ");
        strcat(pidofCmd, pidName);
        FILE *fp = popen(pidofCmd, "r");
        if(fp) {
            fscanf( fp, "%d", &pidValue );
        }
    }
    return pidValue;
}

int find_nth_space (char *search_buffer, int   space_ordinality)
{
    int jndex;
    int space_count;
    space_count=0;

    for(jndex=0; search_buffer[jndex]; jndex++) {
        if(search_buffer[jndex]==' ') {
        space_count++;
            if(space_count>=space_ordinality) {
                return jndex;
            }
        }
    }
    fprintf(stderr,"looking for too many spaces\n");
    exit(1);
}

double GetRuntimeByPID (int pid)
{
    double retval = 0;
    #if defined(BSD)    
        int mib[4];	
        size_t len = 4;
        sysctlnametomib("kern.proc.pid", mib, &len);	
        struct kinfo_proc kp;		
        len = sizeof(kp);
        mib[3] = pid;
        if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1) {
            perror("sysctl");
        } else if (len > 0) {
            retval = time(NULL) - kp.kp_proc.p_un.__p_starttime.tv_sec;
        }
    
    #elif __linux
        int       field_begin;
        int       stat_fd;
        char      proc_buf[80];
        char      stat_buf[2048];
        long      jiffies_per_second;
        long long boot_time_since_epoch;
        long long process_start_time_since_boot;
        ssize_t   read_result;
        
        jiffies_per_second=sysconf(_SC_CLK_TCK);
        
        sprintf(proc_buf,"/proc/%d/stat", pid);
        
        stat_fd=open(proc_buf,O_RDONLY);
        if(stat_fd<0) {
            fprintf(stderr,"open() fail\n");
            exit(1);
        }
        read_result=read(stat_fd,stat_buf,sizeof(stat_buf));
        if(read_result<0) {
            fprintf(stderr,"read() fail\n");
            exit(1);
        }
        if(read_result>=sizeof(stat_buf)) {
            fprintf(stderr,"stat_buf is too small\n");
            exit(1);
        }
        field_begin=find_nth_space(stat_buf,21)+1;
        stat_buf[find_nth_space(stat_buf,22)]=0;
        sscanf(stat_buf+field_begin,"%llu",&process_start_time_since_boot);
        close(stat_fd);
        
        stat_fd=open("/proc/stat",O_RDONLY);
        if(stat_fd<0) {
            fprintf(stderr,"open() fail\n");
            exit(1);
        }
        read_result=read(stat_fd,stat_buf,sizeof(stat_buf));
        if(read_result<0) {
            fprintf(stderr,"read() fail\n");
            exit(1);
        }
        if(read_result>=sizeof(stat_buf)) {
            fprintf(stderr,"stat_buf is too small\n");
            exit(1);
        }
        close(stat_fd);
        
        field_begin=strstr(stat_buf,"btime ")-stat_buf+6;
        sscanf(stat_buf+field_begin,"%llu",&boot_time_since_epoch);
        retval = time(NULL)-(boot_time_since_epoch+process_start_time_since_boot/jiffies_per_second);
   	#endif
   	
   	return retval;
}

double GetSystemUptime ()
{
    double retval = 0;	
    #ifdef __linux
        FILE *in=fopen("/proc/uptime", "r");
        char tmp[256]={0x0};
        if(in!=NULL) {
            fgets(tmp, sizeof(tmp), in);
            retval=atof(tmp);
            fclose(in);
        }
    #elif defined(BSD)
        struct timeval boottime;
        size_t size = sizeof(boottime);
        if (sysctlbyname("kern.boottime", &boottime, &size, NULL, 0) == -1) {
            boottime.tv_sec = 0;
        }
        retval = time(NULL) - boottime.tv_sec;
    #endif
    return retval;
}

int main (int argc, char *argv[])
{
    int pid;
    double retval;
    
    if(argc < 2 || !isalpha(argv[1][0])) {
        retval = GetSystemUptime();
    } else if (isNumber(argv[1])) {
        pid = strtol(argv[1], NULL, 0);
    } else {
        pid = GetPIDByName(argv[1]);        
    }
    
    retval = GetRuntimeByPID(pid);        
    if (retval > 0) {
        printf("%d Days, %d Hours, %d Minutes, %d Seconds\n", (int)retval/86400, (int)retval%86400/3600, (int)retval%3600/60, (int)retval%60);
    }
    
    return 0;
}
