#include <iostream>
#include <omp.h>

using namespace std;

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
int sum_val(int a1[], int n)
{
	int sum=0;
	for (int i = 0; i < n; i++) 
	{
		#pragma omp critical
		{
			sum += a1[i];
		}
	}
	return sum;
	
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
        cin >> arr[i];
    }
    cout<<"Maximum value: "<<max_val(arr,n)<<endl;
    cout<<"Minimum value: "<<min_val(arr,n)<<endl;
    cout<<"Sum: "<<sum_val(arr,n)<<endl;
    cout<<"Average value: "<<avg_val(arr,n)<<endl;

    return 0;
}

