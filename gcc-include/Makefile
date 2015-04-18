


##########################mode 1###########################33
CXXFLAGS1 = -I./include-A -I./include-B

##########################mode 2 ###########################33
CXXFLAGS2 = -I./include-A 
CXXFLAGS2 += -I- -I./include-B


##########################mode 3 ###########################33
CXXFLAGS3 = -iquote./include-A 
CXXFLAGS3 +=  -I./include-B



ALL:a1 a2 a3

a1:
	gcc -o $@ main.c $(CXXFLAGS1)

a2:
	gcc -o $@ main.c $(CXXFLAGS2)

a3:
	gcc -o $@ main.c $(CXXFLAGS3)

clean:
	rm -rf *.o a1 a2 a3

