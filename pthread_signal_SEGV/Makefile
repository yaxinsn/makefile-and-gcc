

#########################################
#
#target : all,lib env,install
#
##########################################
CXX = gcc
CXXFLAGS += -Wall -g
CXXLDFLAGS = -lpthread

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
	#$(CXX) $(CXXFLAGS) $(CXXLDFLAGS) $^ -o $@
	$(CXX)  $(CXXLDFLAGS) $^ -o $@

clean:
	@rm $(progam) *.o -f
