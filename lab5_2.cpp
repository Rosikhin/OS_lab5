// 9893, Росихин Александр, 
// Дисциплина ОС,
// Лабораторная работа №5.

/*
 № 1
*/

#include <iostream>
//#include <pthread.h>
#include <unistd.h> // для sleep()
#include <semaphore.h>
#include <fcntl.h> // для O_CREAT
//#include <stdio.h>

int flag = 0;
sem_t* sem;
FILE *  fl;

#define SEM_NAME "/rosikhin"

void* thread(void* flag)
{
 char ch[1] = {'2'};

 while (*((int*)flag) == 0)
 {
 sem_wait(sem);
  
  for (int i=0; i<10; i++ )
  {
   fputs(ch, stdout);
   fputs(ch, fl); 
   usleep(50000);
  }
  
  
 sem_post(sem);
  usleep(50000);
 }

 return 0;
}

int main()
{
 sem = sem_open(SEM_NAME, O_CREAT, 0644, 100);
 fl = fopen("test.txt", "a+");
 
 pthread_t id;
 pthread_create(&id, NULL, thread, &flag); 
 
 std::cout << "\nНажмите клавишу.\n";
 getchar();
 
 flag = 1;

 pthread_join(id, NULL); 
 
 std::cout << "\nЗавершение работы программы.\n";
 
 
 fclose(fl);
 sem_close(sem);
 sem_unlink(SEM_NAME);
 
 return 0;
}
