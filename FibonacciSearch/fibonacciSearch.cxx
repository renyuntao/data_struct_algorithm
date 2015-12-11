#include<iostream>
using namespace std;

inline int min(int x,int y) {return (x <= y)? x : y;}

int fibonacciSearch(int arr[],int len,int x)
{
	int fib2 = 0;
	int fib1 = 1;
	int fibm = 1;

	while(fibm < len)
	{
		fib2 = fib1;
		fib1 = fibm;
		fibm = fib2 + fib1;
	}

	int offset = -1;

	while(fibm > 1)
	{
		int i = min(offset+fib2,len-1);

		if(arr[i] < x)
		{
			fibm = fib1;
			fib1 = fib2;
			fib2 = fibm - fib1;
			offset = i;
		}
		else if(arr[i] > x)
		{
			fibm = fib2;
			fib1 = fib1 - fib2;
			fib2 = fibm - fib1;
		}
		else
			return i;
	}

	if(fib1 && arr[offset+1] == x) return offset+1;

	return -1;
}

int main(void)
{
	int arr[] = {10,22,35,40,45,50,80,82,85,90,100};
	int n = sizeof(arr) / sizeof(arr[0]);

	int x = 85;

	cout<<"Found at index:"<<fibonacciSearch(arr,n,x)<<endl;
	
	return 0;
}
