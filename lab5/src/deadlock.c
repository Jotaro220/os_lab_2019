#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int common = 0; /* A shared variable for two threads */
pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;

int x = 2;
int y = 3;

void XY(){
    int X = x;
    pthread_mutex_lock(&mut1);
    printf("X = %d in 1 pth\n",X);
    sleep(10);
    pthread_mutex_lock(&mut2);
    int Y = y;
	printf("Y = %d in 1 pth\n", y);
	printf("X*Y = %d in 1 pth\n", X * Y);
	pthread_mutex_unlock(&mut1);
	pthread_mutex_unlock(&mut2);
}

void YX(){
    int Y = y;
    pthread_mutex_lock(&mut2);
    printf("Y = %d in 2 pth\n",Y);
    sleep(10);
    pthread_mutex_lock(&mut1);
    int X = x;
	printf("X = %d in 2 pth\n", X);
	printf("Y*X = %d in 2 pth\n", Y * X);
	pthread_mutex_unlock(&mut2);
	pthread_mutex_unlock(&mut1);
}

int main() {
  pthread_t thread1, thread2;

  if (pthread_create(&thread1, NULL, (void *)XY, NULL) != 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_create(&thread2, NULL, (void *)YX,NULL) != 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_join(thread1, NULL) != 0) {
    perror("pthread_join");
    exit(1);
  }

  if (pthread_join(thread2, NULL) != 0) {
    perror("pthread_join");
    exit(1);
  }

  return 0;
}

