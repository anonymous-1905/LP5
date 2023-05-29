#include <iostream>
#include <omp.h>
#include <cstdlib>
using namespace std;


int max_val_seq(int a1[], int n)
{
    int maximum_val=a1[0];
    for (int i = 0; i < n; i++) 
    {
	if (a1[i] > maximum_val) 
	{
            maximum_val = a1[i];
        }
    }
    return maximum_val;
}


int max_val(int a1[], int n)
{
    int maximum_val=a1[0];
    #pragma omp parallel for reduction(max:maximum_val)
    for (int i = 0; i < n; i++) 
    {
	//cout << "thread_id = " << omp_get_thread_num() << " and i = " << i << "\n";
	#pragma omp critical
	if (a1[i] > maximum_val) 
	{
            maximum_val = a1[i];
        }
    }
    return maximum_val;
}

int min_val_seq(int a1[], int n)
{
    int minimum_val=a1[0];
    for (int i = 0; i < n; i++) 
    {
	if (a1[i] < minimum_val) 
	{
            minimum_val = a1[i];
        }
    }
    return minimum_val;
}

int min_val(int a1[], int n)
{
    int minimum_val=a1[0];
    #pragma omp parallel for reduction(min:minimum_val)
    for (int i = 0; i < n; i++) 
    {
	#pragma omp critical
	if (a1[i] < minimum_val) 
	{
            minimum_val = a1[i];
        }
    }
    return minimum_val;
}

int sum_val_seq(int a1[], int n)
{
	int sum=0;
	for (int i = 0; i < n; i++) 
	{
		{
			sum += a1[i];
		}
	}
	return sum;
	
}

int sum_val(int a1[], int n)
{
	int sum=0;
	#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < n; i++) 
	{
		#pragma omp critical
		{
			sum += a1[i];
		}
	}
	return sum;
	
}

double avg_val_seq(int a1[], int n)
{
	double average=0.0;
	int sum=sum_val_seq(a1,n);
	average=(double)sum/n;
	return average;
}

double avg_val(int a1[], int n)
{
	double average=0.0;
	int sum=sum_val(a1,n);
	average=(double)sum/n;
	return average;
}
int main() {
    int n;
    cout<<"Enter total number: ";
    cin>>n;
    int* arr=new int[n];

    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < n; i++) {
        //cin >> arr[i];
        arr[i]=rand() % 1000;        
    }
    
    cout<<"Array: ";
    for (int i = 0; i < n; i++) {
        cout<<arr[i]<<" ";       
    }
    cout<<endl;
    
    // Measure the performance of sequential
    double startSeq = omp_get_wtime();
    double avg=avg_val_seq(arr,n);
    double endSeq = omp_get_wtime();
    double seqDuration = endSeq - startSeq;

    // Measure the performance of parallel
    double startParallel = omp_get_wtime();
    double avg_par=avg_val(arr,n);
    double endParallel = omp_get_wtime();
    double parallelDuration = endParallel - startParallel;
 
	
    cout<<"Maximum value: "<<max_val(arr,n)<<endl;
    cout<<"Minimum value: "<<min_val(arr,n)<<endl;
    cout<<"Sum: "<<sum_val(arr,n)<<endl;
    cout<<"Average value: "<<avg_val(arr,n)<<endl;
    
    cout << endl;

    cout << "Sequential Time: " << seqDuration << " seconds" << endl;
    cout << "Parallel Time: " << parallelDuration << " seconds" << endl;


    return 0;
}
