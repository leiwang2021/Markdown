#include "apue.h"
#include<sys/wait.h>

int main()
{
    pid_t pid;
    if((pid=fork())<0)
        err_sys("fork error");
    else if(pid==0)
    {
        if((pid=fork())<0)
            err_sys("fork error");
        else if(pid>0)
        {    printf("the first child\n");
             exit(0);
         }

        sleep(2);
        printf("second child,parent child pid=%ld\n",(long)getppid());
        exit(0);
    }
    printf("Parent pid\n");
    //sleep(5);
    exit(0);
}
