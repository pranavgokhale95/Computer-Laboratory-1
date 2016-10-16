#include <bits/stdc++.h>
#include<pthread.h>
using namespace std;

vector<int> arr;

class Argument
{
	public:
	Argument(){}
	int first,last;
};

class Quicksort
{
	public:
	Quicksort(){}
	~Quicksort(){}
	void print();
	static void* sort(void*);
	private:
	static int partition(int,int);
};

void Quicksort::print()
{
	cout<<"\nSorted array is:\n";
	for(int i=0;i<arr.size();i++)
	{
		cout<<arr[i]<<" ";
	}
}

int Quicksort::partition(int first,int last)
{
	int i=first+1;
	int j=last;
	int key=arr[first];
	int temp;

	cout<<"\nThread id is\t"<< pthread_self() <<"\tfor pivot element\t"<<key;

	while(1)
	{
		while(i<j && key>=arr[i])
		{	
			i++;
		}
		while(i<=j && key<arr[j])
		{
			j--;
		}
		if(i<j)
		{
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}
		else
		{
			temp=arr[first];
			arr[first]=arr[j];
			arr[j]=temp;
			return j;
		}
	}
}

void* Quicksort::sort(void* args)
{
	int fir,las;
	fir=((Argument*)args)->first;
	las=((Argument*)args)->last;

	if(fir>=las)
	{
		return NULL;
	}

	int pos=partition(fir,las);
	pthread_t thread[2];
	Argument* a[2];
	a[0]= new Argument();
 	a[1]= new Argument();

	a[0]->first=fir;
	a[0]->last=pos-1;
	a[1]->first=pos+1;
	a[1]->last=las;
	
	pthread_create(&thread[0],NULL,&Quicksort::sort,(void*)a[0]);
	pthread_create(&thread[1],NULL,&Quicksort::sort,(void*)a[1]);

	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
}

int main()
{
	int count,temp1;

	cout<<"\nEnter the number of elements to be sorted:\n";
	cin>>count;
	cout<<"\nEnter the elements:\n";
	while(count!=0)
	{
		cin>>temp1;	
		arr.push_back(temp1);
		count--;
	}

	Argument *args=new Argument();
	args->first=0;
	args->last=arr.size()-1;

	Quicksort qs;
	qs.sort((void*)args);
	qs.print();
	return 0;
}


