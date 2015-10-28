#include <stdio.h>
#include <strings.h>
#include <unistd.h>




#define debug(format, ...) fprintf (stderr, format, __VA_ARGS__)
#define debug2(format, ...) fprintf (stderr, format, ## __VA_ARGS__)

int main(int argc,char* argv[])
{
    debug("%s", "I am debug!\n");
   // debug("I am debug!\n"); /* compile error, */
    debug2("I am debug2!\n");/* compile ok */
    return 0;
}
