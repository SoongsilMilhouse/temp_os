/*
 * OS Assignment #3
 *
 * @file dininig.c
 */

#include "sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct test_semaphore
{
	int value;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

static tsem_t *chopstick[5];
static tsem_t *updating;

	static int
update_status (int i,
		int eating)
{
	static int status[5] = { 0, };
	static int duplicated;
	int idx;
	int sum;

	tsem_wait (updating);

	status[i] = eating;

	/* Check invalid state. */
	duplicated = 0;
	sum = 0;
	for (idx = 0; idx < 5; idx++)
	{
		sum += status[idx];
		if (status[idx] && status[(idx + 1) % 5])
			duplicated++;
	}

	/* Avoid printing empty table. */
	if (sum == 0)
	{
		tsem_signal (updating);
		return 0;
	}

	for (idx = 0; idx < 5; idx++)
		fprintf (stdout, "%3s     ", status[idx] ? "EAT" : "...");

	/* Stop on invalid state. */
	if (sum > 2 || duplicated > 0)
	{
		fprintf (stdout, "invalid %d (duplicated:%d)!\n", sum, duplicated);
		exit (1);
	}
	else
		fprintf (stdout, "\n");

	tsem_signal (updating);

	return 0;
}

	void *
thread_func (void *arg)
{
	int i = (int) (long) arg;
	int k = (i + 1) % 5;
	static int num = 0;					//static 변수로 선언하여 현재 몇 명이 2개의 젓가락을 들고 있는지 기억한다.
	int count, count_i, count_k;
	do
	{
		if(num< 2){						//만일 2개의 젓가락을 들고 있는 사람이 2명 이하일 경우에만 음식을 먹을 수 있다.
			count_i = tsem_try_wait(chopstick[i]);
			count_k = tsem_try_wait(chopstick[k]);
			count  = count_i + count_k;
			if(count == 0){				//젓가락 2개 들 수 있는 경우
				num++;
				update_status (i, 1);
				update_status (i, 0);
				tsem_signal (chopstick[i]);
				tsem_signal (chopstick[k]);
				num--;
			}
			else{						//젓가락 하나만 든 경우 value값을 0에서 1로 다시 수정한다.(tsem_try_wait에서 1개의 젓가락만 사용할 경우 tsem_wait(sem)이 실행되고 그 안에서 sem_value--; 가 실행되기 때문에)
				if(count == 2)
					;
				else {
					if(count_i == 1){	
						chopstick[k]->value += 1;
						tsem_signal(chopstick[k]);
					}
					else if(count_k == 1){
						chopstick[i]->value += 1;
						tsem_signal(chopstick[i]);
					}
				}

			}
		}
	}while(1);

	return NULL;
}

	int
main (int    argc,
		char **argv)
{
	int i;

	for (i = 0; i < 5; i++)
		chopstick[i] = tsem_new (1);
	updating = tsem_new (1);

	for (i = 0; i < 5; i++)
	{
		pthread_t tid;

		pthread_create (&tid, NULL, thread_func, (void *) (long) i);
	}

	/* endless thinking and eating... */
	while (1)
		usleep (10000000);

	return 0;
}
