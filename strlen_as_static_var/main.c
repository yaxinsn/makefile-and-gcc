#include <stdio.h>
#include <strings.h>
#include <unistd.h>


int str_printf(const char* src)
{
    char _str[strlen(src) +1];
    printf("%s:%d:: sizeof(_str) %d\n",__func__,__LINE__,sizeof(_str));
    memcpy(_str,src,strlen(src)+1);
    printf("--<%s>\n",_str);
    return 0;

}

char str[]="abcd %d dddd";
int main(int argc,char* argv[])
{
#if 0 
    if(argv[1])
        str_printf(argv[1]);
#endif
    char _str[128];
    sprintf(_str,str,123);
    printf("------<%s>\n",_str);
    return 0;
}
