

all=acsmx

$(all):acsmx.o
	gcc -o $@ $^

CFLAGS+= -D__CASE__

#*.o:*.c
#	gcc -D__CASE__ $^


clean:
	rm $(all) *.o -rf
