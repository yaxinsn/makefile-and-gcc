

#########################################
#
#target : all,lib env,install
#
##########################################
CXX = gcc
CXXFLAGS += -Wall -g
#CXXLDFLAGS=;

src = $(wildcard *.c)
obj = $(src:.c=.o)
progam = program

all: t $(progam)

t:
	@echo $(src)
	@echo $(obj)



$(src:.c=.o): %.o : %.c
	$(CXX) $(CXXFLAGS) $^ -c -o $@

$(progam): $(obj)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	@rm $(progam) *.o -f
