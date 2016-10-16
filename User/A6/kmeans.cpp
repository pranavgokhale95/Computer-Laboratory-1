#include<iostream>
#include<math.h>

using namespace std;

#define MAX 15

int main()
{
  int k,n,i,j,l=0,count=0,min=999,xcount=0;
  float x[MAX],y[MAX],cenx[MAX],ceny[MAX],kc[MAX],kc1[MAX];
  double eucd[MAX][MAX],d[MAX];

  cout<<"Enter number of elements";
  cin>>n;
  cout<<"Enter number of clusters";
  cin>>k;

  	for(i=0;i<n;i++)
	{
		cout<<"Enter x coordinate";
		cin>>x[i];
		cout<<"Enter y coordinate";
		cin>>y[i];
		cenx[i]=x[i];
		ceny[i]=y[i];
		kc[i]=kc1[i]=0;
	}
    do
    {	
	for(i=0;i<k;i++)
	{
		for(j=0;j<n;j++)
		{
			d[j]=((cenx[i]-x[j])*(cenx[i]-x[j]))+ ((ceny[i]-y[j])*(ceny[i]-y[j]));
			eucd[i][j]=sqrt(d[j]);
		}
	}
	
	l=0;
	for(i=0;i<n;i++)
	{
		
		if(kc1[i]==kc[i])
		{
			l++;
		}
	}
	if(l==n)
	{	
		count++;
		if(count==2)
		goto L1;
	}
	else
	{
		for(i=0;i<n;i++)
		{
			kc1[i]=kc[i];
		}
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<k;j++)
		{
			if(eucd[j][i]<min)
			{
				min=eucd[j][i];
				kc[i]=j;
			}
		}
		min=999;
		cenx[i]=ceny[i]=0;	
	}

	for(i=0;i<k;i++)
	{
		xcount=0;
		for(j=0;j<n;j++)
		{
			if(kc[j]==i)
			{
				cenx[i]=x[j]+cenx[i];
				ceny[i]=y[j]+ceny[i];
				xcount++;	
			}
		}
		cenx[i]=cenx[i]/xcount;
		ceny[i]=ceny[i]/xcount;
	}


	for(i=0;i<k;i++)
   	{
		cout<<"Centre for cluster Number"<<i+1<<"is: ("<<cenx[i]<<","<<ceny[i]<<")";
		cout<<"Points are:\n";
		for(j=0;j<n;j++)
		{
			if(kc[j]==i)
			{
				cout<<"("<<x[j]<<","<<y[j]<<")"<<endl;
			}
		}
	}

   }while(count<2);

   L1:  for(i=0;i<k;i++)
   	{
		cout<<"Centre for cluster Number"<<i+1<<"is: ("<<cenx[i]<<","<<ceny[i]<<")";
		cout<<"Points are:\n";
		for(j=0;j<n;j++)
		{
			if(kc[j]==i)
			{
				cout<<"("<<x[j]<<","<<y[j]<<")"<<endl;
			}
		}
	}
		

 return 0;
}
