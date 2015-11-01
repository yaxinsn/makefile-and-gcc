

#include <stdio.h>
#include <pthread.h>
#include <signal.h>


void *threadfunc1(void *pvoid)
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
	sigaddset(&sig,SIGUSR1);
	pthread_sigmask(SIG_BLOCK,&sig,NULL);//设置该线程的信号屏蔽字为SIGUSR1
	while(1)
	{
		sigwait(&sig,&signum);//睡眠等待SIGUSR1信号的到来
		printf("threadfunc2 waiting is over!\n");
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