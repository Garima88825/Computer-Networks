//Implementation of Priority(Preeemptive) Using C++
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

typedef struct process
{
	int at,bt,ct,ta,wt,btt,pr;
	string pro_id;
	/*
	artime = Arrival time,
	bt = Burst time,
	ct = Completion time,
	ta = Turn around time,
	wt = Waiting time
	*/

}schedule;


bool compare_pr(schedule a,schedule b)
{
	return a.pr>b.pr;
	/* greater the number,higher the priority*/
}

bool compare_at(schedule a,schedule b)
{
	return a.at<b.at;
}

int main()
{
	schedule pro[10];
	int n,i,j,pcom;

	cout<<"\nEnter the number of process::";
	cin>>n;
	
	for(i=0;i<n;i++)
	{
		cout<<"\n\nProcess : "<<i+1;
		cout<<"\nProcess id : ";
		cin>>pro[i].pro_id;
		cout<<"Arrival time : ";
		cin>>pro[i].at;
		cout<<"Burst time : ";
		cin>>pro[i].bt;
		pro[i].btt=pro[i].bt;
		cout<<"Priority : ";
		cin>>pro[i].pr;
	}

	sort(pro,pro+n,compare_at);
	/*sort is a predefined funcion  defined in 
	algorithm.h header file, it will sort the 
	schedulees according to their arrival time*/

	i=0;
	pcom=0;
	while(pcom<n)
	{
		for(j=0;j<n;j++)
		{
			if(pro[j].at>i)
			break;
		}
		sort(pro,pro+j,compare_pr);
		if(j>0)
		{
			for(j=0;j<n;j++)
			{
				if(pro[j].bt!=0)
				break;
			}
			if(pro[j].at>i)
			i+=pro[j].at-i;
			pro[j].ct=i+1;
			pro[j].bt--;
		}
		
		i++;
		pcom=0;
		for(j=0;j<n;j++)
		{
			if(pro[j].bt==0)
			pcom++;
		}
	}
	cout<<"Process id"<<"\t"<<"Priority\t"<<"Arrival time"<<"\t"<<"Burst time"<<"\t"<<
	      "Turnaround time"<<"\t\t"<<"Waiting time"<<"\t"<<endl;
	cout<<"_________________________________________________________________________________________________\n\n";
	for(i=0;i<n;i++)
	{
		pro[i].ta=pro[i].ct-pro[i].at;
		pro[i].wt=pro[i].ta-pro[i].btt;
		cout<<"  "<<pro[i].pro_id<<"\t\t  "<<pro[i].pr<<"\t\t  "<<pro[i].at<<"\t\t  "<<pro[i].btt<<"\t\t  "<<
		      pro[i].ta<<"\t\t\t   "<<pro[i].wt;
		cout<<endl;
	}
	cout<<endl;
	int sum_wt=0,sum_ta=0;
	for(i=0;i<n;i++)
	{
		sum_wt+=pro[i].wt;
		sum_ta+=pro[i].ta;
	}
	cout<<"The average waiting time : "<<(float)sum_wt/(float)n<<endl;
	cout<<"The average turn around time : "<<(float)sum_ta/(float)n<<endl;
	return 0;
}

