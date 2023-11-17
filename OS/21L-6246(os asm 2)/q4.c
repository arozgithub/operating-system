// C program for Merge Sort
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // Add this line for 'wait'
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	int L[n1], R[n2];

	// Copy data to temp arrays
	// L[] and R[]
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back
	// into arr[l..r]
	// Initial index of first subarray
	i = 0;

	// Initial index of second subarray
	j = 0;

	// Initial index of merged subarray
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements
	// of L[], if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
pid_t pid1, pid2;
pid1 = fork();
pid2 = fork();

	if (l < r) {
		// Same as (l+r)/2, but avoids
		
		// overflow for large l and h
		int m = l + (r - l) / 2;
        if (pid1 == -1) {
            perror("Fork failed.");
            exit(EXIT_FAILURE);
        } else if (pid1 == 0) {
            mergeSort(arr, l, m); // Child 1 sorts the first half
            exit(0);
        } else {
            
            if (pid2 == -1) {
                perror("Fork failed.");
                exit(EXIT_FAILURE);
            } else if (pid2 == 0) {
                mergeSort(arr, m + 1, r); // Child 2 sorts the second half
                exit(0);
            } else {
                wait(NULL);
                wait(NULL);
                merge(arr, l, m, r); // Parent merges the two sorted halves
            }
        }
}
}
// UTILITY FUNCTIONS
// Function to print an array
void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

// Driver code
int main()
{
	int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

	printf("Given array is \n");
	printArray(arr, n);

	mergeSort(arr, 0, n - 1);

	printf("\nSorted array is \n");
	printArray(arr, n);
	return 0;
}

