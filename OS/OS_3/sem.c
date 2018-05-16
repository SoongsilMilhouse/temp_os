/*
 * OS Assignment #3
 *
 * @file sem.c
 */

#include "sem.h"
#include <stdlib.h>

struct test_semaphore		//세마포어 객체 자료 구조
{
  int             value;
  pthread_mutex_t mutex;
  pthread_cond_t  cond;
};							//typedef struct test_semaphore tsem_t;

tsem_t *
tsem_new (int value)		//세마포어 객체 생성
							//value값으로 초기화된 세마포어 객체를 만들어서 반환한다. 메모리 할당은 실패하지 않는다고 가정한다.
{
  tsem_t *sem;

  sem = malloc (sizeof (tsem_t));
  if (!sem)
    return NULL;

  sem->value = value;
  pthread_mutex_init (&sem->mutex, NULL);
  pthread_cond_init (&sem->cond, NULL);

  return sem;
}

void
tsem_free (tsem_t *sem)		//세마포어 객체 해제
							//sem이 가리키는 세마포어 객체를 해제합니다
{
  if (!sem)
    return;

  pthread_cond_destroy (&sem->cond);
  pthread_mutex_destroy (&sem->mutex);
  free (sem);
}

void
tsem_wait (tsem_t *sem)		//세마포어 연산 P실행 
							//세마포어 값을 1 감소하고 0보다 작을 경우 해당 쓰레드 실행을 지연한다.
{
  if (!sem)
    return;

  pthread_mutex_lock (&sem->mutex);
  sem->value--;
  if (sem->value < 0)
    pthread_cond_wait (&sem->cond, &sem->mutex);
  pthread_mutex_unlock (&sem->mutex);
}

int
tsem_try_wait (tsem_t *sem)		//세마포어 연산 P실행 또는 가능 여부 확인
								//세마포어 값이 1 이상일 경우 1을 감소하고 0을 돌려주지만, 세마포어 값이 0 이하일 경우 해당 쓰레드를 지연하지 않고 1을 돌려준다.
{
	pthread_mutex_lock(&sem->mutex);
	if(sem->value >= 1){
		sem->value--;
		pthread_mutex_unlock((&sem->mutex);
		return 0;
	}
	else if(sem->value <= 0){
		pthread_mutex_unlock((&sem->mutex);
		return 1;
	}
}

void tsem_signal (tsem_t *sem)	//세마포어 연산 V실행
								//세마포어 값을 1 증가하고 0 이하 일 경우 대기중인 쓰레드 중 하나의 실행을 재개합니다.
{
  if (!sem)
    return;

  pthread_mutex_lock (&sem->mutex);
  sem->value++;
  if (sem->value <= 0)
    pthread_cond_signal (&sem->cond);
  pthread_mutex_unlock (&sem->mutex);  
}
