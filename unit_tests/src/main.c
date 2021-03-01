#include <stdio.h>
#include <stdlib.h>
#include "./test.h"

static void *run_test_thread() {
	void *ret = malloc(80);
	pthread_exit(NULL);
	return ret;
}

int main(void) {
	pthread_t *thread = malloc(sizeof(pthread_t) * 100);

	run_test_malloc();
	run_test_realloc();
	run_test_mixed();
	run_test_thread();

	int i = 0;
	while (i < 100) {
		if (pthread_create(thread + i, NULL, run_test_thread, NULL)) {
			printf("Error pthread");
			return EXIT_FAILURE;
		}
		if (pthread_join(thread[i], NULL)) {
			printf("error pthread join");
			return EXIT_FAILURE;
		}
		i++;
	}
	run_test_rlimit(); // Always at the end
}
