
#include <memory.h>
#include <stdio.h>
#include <sys/queue.h>

#include <stdio.h>
#include <stdlib.h>

// �¼�����
typedef struct event_t{
 	int  iItem;
 TAILQ_ENTRY(event_t)   ev_next; /* TAILQ_ENTRY �б�����struct XXXX */
 
}event;

// ������һ���¼��ṹ˫������ event_list(first, last).


typedef TAILQ_HEAD(event_list_t, event_t) event_list;  /* TAILQ_HEAD�ڶ����� �б�����struct XXXX ,��һ������head�Ķ������� */


/*
 * main����
 */
int main(int argc, char* argv[])
{
 // ��ʼ��
 event_list evlist;
 TAILQ_INIT(&evlist);
 
 
 struct event_t* pEvent;
 
 // ����ͷ�� 
 struct event_t* event0 =  malloc(sizeof(struct event_t));
 event0->iItem = 0;
 TAILQ_INSERT_HEAD(&evlist, event0, ev_next); //�Ҳ���ʹ��TAILQ_INSERT_HEAD
// TAILQ_INSERT_TAIL(&evlist, event0, ev_next);

#if 1
 //
 struct event_t event1;
 event1.iItem = 1;
 TAILQ_INSERT_TAIL(&evlist, &event1, ev_next);

 //
 struct event_t event2;
 event2.iItem = 2;
 TAILQ_INSERT_TAIL(&evlist, &event2, ev_next);

 //
 struct event_t event3;
 event3.iItem = 3;
 TAILQ_INSERT_TAIL(&evlist, &event3, ev_next);
 
 //
 struct event_t event4;
 event4.iItem = 4;
 TAILQ_INSERT_TAIL(&evlist, &event4, ev_next);
 
 //
 struct event_t event5;
 event5.iItem = 5;
 TAILQ_INSERT_TAIL(&evlist, &event5, ev_next);

 printf("show after init\n");
 TAILQ_FOREACH(pEvent, &evlist, ev_next) {
  printf("item:%d\n", pEvent->iItem);
 }
 printf("\n");
 TAILQ_FOREACH(pEvent, &evlist, ev_next) {
  if(pEvent->iItem == 2)
  	{
  		TAILQ_REMOVE(&evlist, pEvent, ev_next);
  	}
 }

 
 printf("show after delete 2\n");
 TAILQ_FOREACH(pEvent, &evlist, ev_next) {
  printf("item:%d\n", pEvent->iItem);
 }
#endif
 getchar();
 return 0;
}

