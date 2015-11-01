
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

/*
  ����һ���ṹ�壬��ֻ��β���е�һ��Ԫ��
  ���������һ��TAILQ_ENTRY��ָ����һ������һ��Ԫ��
*/
struct tailq_entry {
 int value;
 TAILQ_ENTRY(tailq_entry) entries;
};

//������е�ͷ��
//TAILQ_HEAD(, tailq_entry) my_tailq_head;
typedef TAILQ_HEAD(tailq_list_t, tailq_entry) tailq_list_head;
int main(int argc, char  *argv[])
{
 //����һ���ṹ��ָ��
 struct tailq_entry *item;
 //��������һ��ָ��
 struct tailq_entry *tmp_item;

 //��ʼ������
 TAILQ_INIT(&my_tailq_head);

 int i;
 //�ڶ��������10��Ԫ��
 for(i=0; i<10; i++) {
  //�����ڴ�ռ�
  item = malloc(sizeof(*item));
  if (item == NULL) {
   perror("malloc failed");
   exit(-1);
  }
  //����ֵ
  item->value = i;

  /*
     ��Ԫ�ؼӵ�����β��
     ����1��ָ�����ͷ��ָ��
     ����2��Ҫ��ӵ�Ԫ��
     ����3���ṹ��ı�����
  */
  TAILQ_INSERT_TAIL(&my_tailq_head, item, entries);
 }

 //��������
 printf("Forward traversal: ");
 TAILQ_FOREACH(item, &my_tailq_head, entries) {
  printf("%d ",item->value);
 }
 printf("\n Forward traversal end\n");

 //���һ���µ�Ԫ��
 printf("Adding new item after 5: ");
 TAILQ_FOREACH(item, &my_tailq_head, entries) {
  if (item->value == 5) {
   struct tailq_entry *new_item = malloc(sizeof(*new_item));
   if (new_item == NULL) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
   }
   new_item->value = 10;
   //����һ��Ԫ��
   TAILQ_INSERT_AFTER(&my_tailq_head, item, new_item, entries);
   break;
  }
 }
 TAILQ_FOREACH(item, &my_tailq_head, entries) {
  printf("%d ", item->value);
 }
 printf("\n");
#if 0
 //ɾ��һ��Ԫ��
 printf("Deleting item with value 3: ");
 for(item = TAILQ_FIRST(&my_tailq_head); item != NULL; item = tmp_item) {
  if (item->value == 3) {
   //ɾ��һ��Ԫ��
   TAILQ_REMOVE(&my_tailq_head, item, entries);
   //�ͷŲ���Ҫ���ڴ浥Ԫ
   free(item);
   break;
  }
  tmp_item = TAILQ_NEXT(item, entries);
 }
#else

 printf("Deleting item with value 3: -------------\n");
 TAILQ_FOREACH(item, &my_tailq_head, entries) {
 	if (item->value == 3) {
   //ɾ��һ��Ԫ��
   TAILQ_REMOVE(&my_tailq_head, item, entries);
   //�ͷŲ���Ҫ���ڴ浥Ԫ
   free(item);
   break;
  }
}
#endif
 TAILQ_FOREACH(item, &my_tailq_head, entries) {
  printf("%d ", item->value);
 }
 printf("\n");

 //��ն���
 while (item = TAILQ_FIRST(&my_tailq_head)) {
  TAILQ_REMOVE(&my_tailq_head, item, entries);
  free(item);
 }

 //�鿴�Ƿ�Ϊ��
 if (!TAILQ_EMPTY(&my_tailq_head)) {
  printf("tail queue is  NOT empty!\n");
 }

 return 0;

}