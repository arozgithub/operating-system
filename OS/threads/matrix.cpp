#include <stdio.h>
#include <pthread.h>

#define ROWS 3
#define COLS 3
#define size COLS
int min=12345;
int max=0;

void *Max (void *args)
{
 int* arr= ((int *)args);

  for (int i = 0; i <size ; ++i)
    {
      if (arr[i] > max)
	{
	  max = arr[i];
	}
    }
  pthread_exit (NULL);
}

void *Min (void *args)
{
 int*arr2= ((int *)args);

  for (int i = 0; i <size ; ++i)
    {
      if (arr2[i]<min)
	{
	  min = arr2[i];
	}
    }
  pthread_exit (NULL);
}

int main ()
{
  //size=COLS;
  int matrix[ROWS][COLS] ={{1, 2, 3}, {4, 7, 5}, {4, 3, 89}};
  for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    int t=ROWS;
  pthread_t threads[t];
  for (int i = 0; i < ROWS; i++){

// Create the child thread
      pthread_create (&threads[i], NULL, Max, &matrix[i]);
      
      }
      for (int i = 0; i < ROWS; i++){

      pthread_create (&threads[i], NULL, Min, &matrix[i]);
}


      // Wait for the child thread to complete
       for (int i = 0; i < ROWS; ++i) {
        pthread_join(threads[i], NULL);
    }
      printf("max is: %d ",max);
      printf("\n");
      printf("min is: %d ",min);
      printf("\n");

      return 0;
    }

