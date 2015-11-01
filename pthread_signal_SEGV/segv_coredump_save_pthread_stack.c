/*
当进程有段错误时（signal segv)，会保存coredump.
那么进程的其中一个子线程引发了corddump，那应该保存哪一个线程的栈呢？


*/

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h> /* gettid */
#include <sys/syscall.h>
#include <sys/prctl.h>



/* 
function: get_pthread_pid
desc:	  get the pthread's process id. 
param:	  void
return:		return current pthread's processid in linux kernel.
*/
int pthread_get_pid()
{
#if 0	
	return gettid();
#else
	return  syscall(SYS_gettid);
#endif	
}
/* 
function: pthread_set_name
desc:	  set pthead's name, this name is showed at ps -eLf.
		  
param:	  name,
return:	  void
*/
void pthread_set_name(char* name)
{
	prctl(PR_SET_NAME,name,0,0,0);
}


void sig_handler(int sig)
{
   printf("%d Deal  %d\n",pthread_get_pid(),sig);  //SIGINT信号处理函数
}

int sig_init_act()
{
	struct sigaction act;
   	act.sa_handler=sig_handler;
   	sigemptyset(&act.sa_mask);
   	act.sa_flags=0;
   	sigaction(SIGSEGV,&act,0);//设置信号SIGUSR1的处理方式忽略
}
void *threadfunc1(void *pvoid)
{ 
	int signum;
	sigset_t sig;
	
	//sig_init_act();
	sigemptyset(&sig);
	sigaddset(&sig,SIGUSR1);
	pthread_sigmask(SIG_BLOCK,&sig,NULL);//设置该线程的信号屏蔽字为SIGUSR1
	while(1)
	{
		sigwait(&sig,&signum);//睡眠等待SIGUSR1信号的到来

		printf("threadfunc1 waiting is over!\n");
	}
}

int bomb_signal_segv()
{
	int* a=0;
	*a= 5;
}

void *threadfunc2(void *pvoid)
{ 	
	int signum;
	sigset_t sig;
	
	sigemptyset(&sig);
	sigaddset(&sig,SIGUSR1);
	pthread_sigmask(SIG_BLOCK,&sig,NULL);//设置该线程的信号屏蔽字为SIGUSR1
	while(1)
	{
		sigwait(&sig,&signum);//睡眠等待SIGUSR1信号的到来
		printf("threadfunc2 waiting is over!\n");
		bomb_signal_segv();
	}
}


void main()
{
		int i;
		pthread_t thread1,thread2;
		
		pthread_create(&thread1,NULL,threadfunc1,(void *)NULL);
    pthread_create(&thread2,NULL,threadfunc2,(void *)NULL);
  
    pthread_detach(thread1);
    pthread_detach(thread2);
  
       struct sigaction act;
       act.sa_handler=SIG_IGN;
       sigemptyset(&act.sa_mask);
       act.sa_flags=0;
       sigaction(SIGUSR1,&act,0);//设置信号SIGUSR1的处理方式忽略

     

  while(1)
  {
  	printf("please input select a number in (1,2)!\n");
  	scanf("%d",&i);
  	if(i==1)
  	  pthread_kill(thread1,SIGUSR1);

        if(i==2)
          pthread_kill(thread2,SIGUSR1);
  }
}