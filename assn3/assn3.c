#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

// Subthread method for getting factors of a number
void* factor_thread(void *data) {
  int count = 0;
  int size = 1;
  int factor = 2;
  int number = atoi(data);
  int *results = malloc(sizeof(int));

  for(factor; factor <= sqrt(number); factor++) {
    while (number%factor == 0){
      results[count++] = factor;
      number /= factor;
    }
  }

  if(number > 1) {
    results[count++] = number;
  }

  results = realloc(results, count * sizeof(int));


  if (results == NULL && count > 0) {
    perror("Reallocation failed");
    pthread_exit(NULL);
  }
  return results;
}


/**************************************************
 * MAIN
 **************************************************/
int main(int argc, char *argv[]) {
  // check for "failure to start" errors
  
  // main thread pointer
  pthread_t *threads;
  void *data;
  int rc;

  // input error checking
  if(argc <= 1) {
    printf("Input numbers to begin program\n");
    printf("\"./threads <numbers seperated by spaces>\"\n");
    exit(0);
  }

  // allocate memory for threads
  threads = malloc((argc - 1) * sizeof(pthread_t));

  // loop to read in arguments and create subthread for each
  printf("Creating threads...\n");
  for(int i = 0; i < argc - 1; i++) {
    rc = pthread_create(&threads[i], NULL, factor_thread, argv[i + 1]);
    if(rc != 0) {
      printf("Error: Unable to create thread %d\n, i");
      exit(1);
    }
  }
  
  // pthread_create(&thread_id, NULL, factor_thread, NULL);

  printf("Waiting for thread(s) to complete...\n");
  for(int i = 0; i < argc - 1; i++) {
    rc = pthread_join(threads[i], &data);

    if(rc != 0) {
      printf("Error: Unable to join thread %d\n", i);
      exit(1);
    }

    int *results = (int *)data;
    printf("%s: ", argv[i +1]);
    for (int j = 0; j < 10 && results[j] != 0; j++) {
        printf("%d ", results[j]);
    }
    printf("\n");
    free(results);
  }
  // int *results = (int *)data;

  printf("All threads completed\n");
  exit(0);
}
