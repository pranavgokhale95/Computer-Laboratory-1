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
/*
#include <iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>
using namespace std;

class kMeans{
	//for the dataset
	int noOfPoints;
	float *xCord;
	float *yCord;
	//for the random cluster centres
	float *centroidX;
	float *centroidY;
	//for holding the cluster numbers of points
	int *prevCluster;
	int *currentCluster;
	int noOfClusters;

public:
	kMeans(int noPoints,int noClusters)
	{
		noOfPoints=noPoints;
		xCord=new float(noOfPoints);
		yCord=new float(noOfPoints);
		noOfClusters=noClusters;
		centroidX=new float(noOfClusters);
		centroidY=new float(noOfClusters);
		prevCluster=new int(noOfPoints);
		currentCluster=new int(noOfPoints);

	}

	void acceptInput();
	void generateCentorids();
	void calculateDistance(int);
	void copyArray();
	void apriori();
	int checkArray();
	void generateMeanCentroids();
};

void kMeans::acceptInput()
{
	cout<<"Enter the  points ( x and y)"<<endl;
	for(int i=0;i<noOfPoints;i++)
	{
		cin>>xCord[i]>>yCord[i];//accept the points
	}

}
void kMeans::generateCentorids()
{
	int randIndex;
	cout<<"Centroids for Pass 1\n";//generate rhe random centroids for first pass
	for (int i=0;i<noOfClusters;i++)
		{
			randIndex=1+rand()%(noOfPoints-i-1);//rand() gives a random value between 1 and (noOfPoints-i-1)
			centroidX[i]=xCord[randIndex];
			centroidY[i]=yCord[randIndex];
			cout<<i<<") ("<<centroidX[i]<<","<<centroidY[i]<<")\n";
		}

}
void kMeans::generateMeanCentroids()
{
	float sumX[noOfPoints],sumY[noOfPoints];//for all the points add the coordinates of the points to the cluster it belongs
	int count[noOfClusters];
	for(int i=0;i<noOfPoints;i++)
	{
		sumX[i]=0;
		sumY[i]=0;
	}
	for(int i=0;i<noOfClusters;i++)
	{
		count[i]=0;
	}

	for(int i=0;i<noOfClusters;i++)
	{
		for(int j=0;j<noOfPoints;j++)
		{
			if(currentCluster[j]==i)//if the point belongs to the cluster
			{
				count[i]=count[i]+1;
				sumX[i]=sumX[i]+xCord[j];
				sumY[i]=sumY[i]+yCord[j];
			}
		}
	}
	for(int i=0;i<noOfClusters;i++)
	{
		centroidX[i]=sumX[i]/count[i];
		centroidY[i]=sumY[i]/count[i];
		cout<<i<<") ("<<centroidX[i]<<","<<centroidY[i]<<")\n";
	}
}
void kMeans::calculateDistance(int point)
{
	float sum[noOfClusters];
	for(int i=0;i<noOfClusters;i++)
	{
		sum[i]=0;
	}
	float x1,x2;
	for(int i=0;i<noOfClusters;i++)
	{
		sum[i]=(fabs(centroidX[i]-xCord[point]))+(fabs(centroidY[i]-yCord[point]));//find distance from all the clusters
	}
	float min=sum[0];
	for(int i=1;i<noOfClusters;i++)
	{
		if(sum[i]<min)
		{
			min=sum[i];
		}
	}
	int index;
	for(int i=0;i<noOfClusters;i++)
		{
			if(sum[i]==min)
			{
				index=i;//find the index of the cluster
			}
		}
	currentCluster[point]=index;

}

void kMeans::copyArray()//copy the array
{
	for(int i=0;i<noOfPoints;i++)
	{
		prevCluster[i]=currentCluster[i];
	}
}
int kMeans::checkArray()
{
	for(int i=0;i<noOfPoints;i++)
	{
		if(prevCluster[i]!=currentCluster[i])//check if the clusters have changed,if they havent the algorithm stops
			return -1;

	}
	return 0;

}
void kMeans::apriori()//the main function
{

	int flag=0;
	int count=1;
	while(flag!=1)
	{

		if(count==1){
		generateCentorids();}//initially generate random centroids
		else
		{
			cout<<"Centroids for Pass "<<count<<endl;
			generateMeanCentroids();//for every other pass generate mean centroids
		}
		for(int i=0;i<noOfPoints;i++)
		{
			calculateDistance(i);//calculate the distance and determine the cluster to which the point belongs
		}

		if(checkArray()==0){//check if to stop

			flag=1;}
		copyArray();//if not copy the array for a new pass
		count=count+1;
		cout<<"==================================\n";
	cout<<"POINT \t\t CLUSTER NUMBER\n";
	cout<<"==================================\n";
	for(int i=0;i<noOfPoints;i++)
	{
		cout<<"Point "<<i<<" ("<<xCord[i]<<","<<yCord[i]<<")\t\t"<<currentCluster[i]<<endl;
	}

	}
	
}

int main() {
	int noPoints,noClusters;
	cout<<"Enter number of points:\t";
	cin>>noPoints;
	cout<<"Enter number of clusters: ";
	cin>>noClusters;
	kMeans kmeans(noPoints,noClusters);//create an object of class kMeans
	kmeans.acceptInput();//accept the input
	kmeans.apriori();
	return 0;
}
*/
