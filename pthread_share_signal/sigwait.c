

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

// SIGABRT 's num is 6;
/*  
	killall -6 pragram,
*/
void sig_handler(int sig)
{
   printf("sig_handler %d Deal  %d\n",pthread_get_pid(),sig);  //SIGINT信号处理函数
}
 void sig_handler22(int sig)
{
   printf("sig_handler22 %d Deal  %d\n",pthread_get_pid(),sig);  //SIGINT信号处理函数
}

int sig_init_act22()
{
	struct sigaction act;
   	act.sa_handler=sig_handler22;
   	sigemptyset(&act.sa_mask);
   	act.sa_flags=0;
   	sigaction(SIGABRT,&act,0);//设置信号SIGUSR1的处理方式忽略
}
int sig_init_act()
{
	struct sigaction act;
   	act.sa_handler=sig_handler;
   	sigemptyset(&act.sa_mask);
   	act.sa_flags=0;
   	sigaction(SIGABRT,&act,0);//设置信号SIGUSR1的处理方式忽略
}
int sig_init_ign()
{
	struct sigaction act;
   	act.sa_handler=SIG_IGN;
   	sigemptyset(&act.sa_mask);
   	act.sa_flags=0;
   	sigaction(SIGABRT,&act,0);//设置信号SIGUSR1的处理方式忽略
}

void *threadfunc1(void *pvoid)
{ 

	pthread_set_name("prag111");
	printf("%s: pid %d enter\n",__func__,pthread_get_pid());
	sig_init_act();
	sleep(20);
	printf("%s: pid %d act abrt and goto sleep  \n",__func__,pthread_get_pid());

	while(1)
	{
		sleep(10);
	}
}

void *threadfunc2(void *pvoid)
{ 
	printf("%s: pid %d enter\n",__func__,pthread_get_pid());
	sig_init_act22();
	sleep(20);
	printf("%s: pid %d act abrt and goto sleep \n",__func__,pthread_get_pid());
	while(1)
	{
		sleep(10);
	}
}


void main()
{
	int i;
	pthread_t thread1,thread2;
	//sig_init_ign();
	
    sleep(10);
    printf("create thread1\n");
    pthread_create(&thread1,NULL,threadfunc1,(void *)NULL);
    sleep(10);/* 一旦有信号发给进程时，sleep会被打断， */
    printf("create thread2:\n");
    pthread_create(&thread2,NULL,threadfunc2,(void *)NULL);
  
    pthread_detach(thread1);
  //  pthread_detach(thread2);

     

  while(1)
  {
  	//printf("please input select a number in (1,2)!\n");
  	//scanf("%d",&i);
    sleep(10);
  }
}


#if 0
void *threadfunc3(void *pvoid)
{ 
	int signum;
	sigset_t sig;
	
	sigemptyset(&sig);
	sigaddset(&sig,SIGUSR1);
	pthread_sigmask(SIG_BLOCK,&sig,NULL);//设置该线程的信号屏蔽字为SIGUSR1
	while(1)
	{
		sigwait(&sig,&signum);//睡眠等待SIGUSR1信号的到来

		printf("threadfunc1 waiting is over!\n");
	}
}

void *threadfunc2(void *pvoid)
{ 	
	int signum;
	sigset_t sig;
	
	sigemptyset(&sig);
	sigaddset(&sig,SIGABRT);
	pthread_sigmask(SIG_BLOCK,&sig,NULL);//设置该线程的信号屏蔽字为SIGUSR1
	while(1)
	{
		sigwait(&sig,&signum);//睡眠等待SIGUSR1信号的到来
		printf("threadfunc2 waiting is over!\n");
	}
}
#endif