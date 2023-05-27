#include<iostream>
#include<omp.h>
#include<chrono>
#include<cstdlib>
using namespace std;
void merge(int num[],int low,int mid,int up)
{
	int i=low,j=mid+1,k=0;
	int* temp=new int[up+1];
	while(i<=mid && j<=up)
	{
		if(num[i]<=num[j])
		{
			temp[k]=num[i];
			i++,k++;
		}
		if(num[i]>num[j])
		{
			temp[k]=num[j];
			j++,k++;
		}	
	}
	while(i<=mid)
	{
		temp[k]=num[i];
		i++,k++;
	}
	while(j<=up)
	{
		temp[k]=num[j];
		j++,k++;
	}
	for (i = 0; i < up - low + 1; i++) 
	{
    		num[i + low] = temp[i];
	}
}
void sequentialMergeSort(int num[],int low,int up)
{
	if(low<up)
	{
		int k=(low+up)/2;
		sequentialMergeSort(num,low,k);
		sequentialMergeSort(num,k+1,up);
		merge(num,low,k,up);
	}
}

void parallelMergeSort(int num[],int low,int up) 
{
    if (low < up) {
        int k = (low+up) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(num, low, k);
            }

            #pragma omp section
            {
                parallelMergeSort(num, k + 1, up);
            }
        }
        merge(num, low, k, up);
    }
}

int main()
{
	int i,n;
	cout<<"Enter total number of elements: ";
	cin>>n;
	int* num=new int[n];
	cout<<"Enter the elements: \n";
	for(i=0;i<n;i++)
	{
		//cin>>num[i]; //user input
		num[i]=rand() % 100; //random number
	}
	cout<<"\nUnSorted Array:  ";
	for(i=0;i<n;i++)
	{
		cout<<num[i]<<" ";
	}
	
	int* num1;
	num1=num;
	
	// Measure the performance of sequential merge sort
    	double startTime = omp_get_wtime();
    	sequentialMergeSort(num,0,n-1);
    	double endTime = omp_get_wtime();
    	double sequentialTime = endTime - startTime;
	
	
	// Measure the performance of parallel merge sort
    	startTime = omp_get_wtime();
    	parallelMergeSort(num1,0,n-1);
    	endTime = omp_get_wtime();
    	double parallelTime = endTime - startTime;
	
	
	cout<<"\n\nSequential Merge Sort Result:  ";
	for(i=0;i<n;i++)
	{
		cout<<num[i]<<" ";
	}
	cout<<endl;
	
	cout << "Parallel Merge Sort Result: ";
	for(i=0;i<n;i++)
	{
		cout<<num1[i]<<" ";
	}
	cout<<endl;
	
	// Output the performance results
    	cout << "\nSequential Merge Sort Time: " << sequentialTime << " seconds" << endl;
    	cout << "Parallel Merge Sort Time: " << parallelTime << " seconds" << endl;
	
	return 0;
}
