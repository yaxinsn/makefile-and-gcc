

#########################################
#
#target : all,lib env,install
#
##########################################
CXX = gcc
CXXFLAGS += -Wall
#CXXLDFLAGS=;

src = $(wildcard *.c)
obj = $(src:.c=.o)
progam = backtrace 

all: t $(progam) backtrace_sym

t:
	@echo $(src)
	@echo $(obj)



$(src:.c=.o): %.o : %.c
	$(CXX) $(CXXFLAGS) $^ -c -o $@

$(progam): $(obj)
	$(CXX) $(CXXFLAGS) $^ -o $@


backtrace_sym: $(obj)
	$(CXX) $(CXXFLAGS) -rdynamic $^ -o $@

clean:
	@rm $(progam) *.o -f
