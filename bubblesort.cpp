#include <iostream>
#include <chrono>
#include <omp.h>
#include<cstdlib>
using namespace std;

void sequentialBubbleSort(int arr[],int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

void parallelBubbleSort(int arr[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++) 
        {
            #pragma omp critical
            if (arr[j] > arr[j + 1]) 
            {
                {
                    //swap(arr[j], arr[j + 1]);
                    int temp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int* arr=new int[n];
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        //arr[i]=rand() % 100;
    }
    
    int* arr1=new int[n];
    for(int i=0;i<n;i++)
    {
	    arr1[i]=arr[i];
    }
    
    // Measure the performance of sequential bubble sort
    double startSeq = omp_get_wtime();
    sequentialBubbleSort(arr,n);
    double endSeq = omp_get_wtime();
    double seqDuration = endSeq - startSeq;


    cout << "Sorted array(sequential): ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;	
	
    // Measure the performance of parallel bubble sort
    double startParallel = omp_get_wtime();
    parallelBubbleSort(arr1,n);
    double endParallel = omp_get_wtime();
    double parallelDuration = endParallel - startParallel;

    cout << "Sorted array(parallel): ";
    for (int i = 0; i < n; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;

    cout << "Sequential Bubble Sort Time: " << seqDuration << " seconds" << endl;
    cout << "Parallel Bubble Sort Time: " << parallelDuration << " seconds" << endl;

    return 0;
}
