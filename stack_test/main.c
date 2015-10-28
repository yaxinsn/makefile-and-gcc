#include <stdio.h>
#include <unistd.h>
#include <execinfo.h>
/*  backtrace */

char long_str[]="1234567890poiuytrewqasdfghjk";
int func_c(int a)
{
    char str[4];
    strcpy(str,long_str);
    return 0;
}

int f_b(int a)
{


    int j, nptrs;
    #define SIZE 100

    void *buffer[100];

    char **strings;

    printf("%s:%d:: \n",__func__,__LINE__);
    nptrs = backtrace(buffer, SIZE);

    printf("backtrace() returned %d addresses\n", nptrs);


   strings = backtrace_symbols(buffer, nptrs);

    if (strings == NULL) {
          perror("backtrace_symbols");
          exit(-1);

     }

                        

    for (j = 0; j < nptrs; j++)
        printf("%s\n", strings[j]);
    
    free(strings);
    
    func_c(a);
}
int f_a(int a)
{
    f_b(a);
}

void main(void)
{
    f_a(3);
    
}
