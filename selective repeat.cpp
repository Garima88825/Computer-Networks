#include<iostream>
#include<string.h>
#include<time.h>
#include<math.h>
#include<windows.h>
#include<vector>
using namespace std;

//P=physical layer, D=data link layer, N=network layer
int n;
int size; //size of sliding window size
vector<int> frame_number;
vector<string> sent;	//data sent
vector<string> received;	//data received
int ACK;	//ACK sent
int s;	//how many elements to transmit
int data_size;	//how many total elements are to be transmitted
int pos1=0,pos2=0;	//keep track of how much data sent and received respectively
int ran;	//for error
vector<int> NAK;	//for storing which frame's data is damaged or lost

struct package{
	string info;
}sending_p,receiving_p;

struct frame{
	string data;
	int seqNo;
}sending_f,receiving_f;

//sender
void N_to_D(int j)
{
	sending_p.info=sent[j];
}

void D_to_P(int j)
{
		sending_f.data=sending_p.info;
		sending_f.seqNo=frame_number[j];
		cout<<"\n\nTansmitting\n";
		for(int k=0;k<78;k++)
		{
			cout<<"_";
			Sleep(10);		
		}
		cout<<"\n>Frame Sent : "<<sending_f.data<<"-"<<sending_f.seqNo;
}

void send()
{
	cout<<"\n\n--SENDER--";	
	for(int i=0,j=pos1;i<size && j<sent.size();i++,j++)
	{
		N_to_D(j);
		D_to_P(j);
	}
}

void send(int j)	//for NAK
{
	cout<<"\n\n--SENDER--";	
	N_to_D(j);
	D_to_P(j);
}

//receiver
void D_to_N(int j)
{
	receiving_p.info=receiving_f.data;
	cout<<"\n\nData received - "<<receiving_p.info;
}

void P_to_D(int j)
{
	receiving_f.data=sent[j];
	receiving_f.seqNo=frame_number[j];
}

void receive()
{
	cout<<"\n\n--RECEIVER--";
	int flag=0;	//for ACK lost
	srand(time(NULL));
	Sleep(1000);
	for(int i=0,j=pos1;i<size && j<sent.size();i++,j++)
	{
		//error generation
		ran=rand()%8;
		if(ran==0)
		{
			NAK.push_back(j);
			cout<<"\n\n**Frame Damaged**";
		}
		else if(ran==1)
		{
			NAK.push_back(j);
			cout<<"\n\n**Frame Damaged**";
		}
		else if(ran==2)
		{
			flag=1;
		}
		
		if(ran!=0 && ran!=1)
		{			
			P_to_D(j);
			D_to_N(j);
		}
	}
	while(!NAK.empty())
	{
		cout<<"\n|NAK sent : "<<NAK.front()<<"|";
		Sleep(1000);
		send(NAK.front());
		Sleep(1000);
		cout<<"\n\n--RECEIVER--";
		Sleep(1000);
		P_to_D(NAK.front());
		D_to_N(NAK.front());
		NAK.erase(NAK.begin());
	}
	pos2=pos1;	//for ACK lost
	A:
	if(pos1+size>=frame_number.size())		//if all the user's data is received
	{
		pos1=frame_number.size();
		ACK=frame_number[pos1-1];
		if(ACK==pow(2,n))
		ACK=0;
	}
	else
	{
		pos1=pos1+size;
		ACK=frame_number[pos1];
	}
	cout<<"\n\n|ACK sent : ACK-"<<ACK<<"|";
	if(flag==1)
	{
		Sleep(1500);
		cout<<"\n\n**ACK Lost**";
		pos1=pos2;
		send();
		cout<<"\n\nRECEIVER";
		for(int i=0,j=pos1;i<size && j<sent.size();i++,j++)
		{			
			P_to_D(j);
			D_to_N(j);
			cout<<"\nDISCARDED";
		}
		flag=0;
		goto A;
	}
}

//main
int main()
{
	char ch;
	int j=0;
	cout<<"Sliding window size = 2^(n-1)\n\nEnter value of n : ";
	cin>>n;
	size=pow(2,n-1);
	cout<<"\nSliding window size = "<<size;
	do{
		cout<<"\n\nHow much data do you want to transmit : ";
		cin>>data_size;
		for(int i=0,k=j;i<data_size;i++,k++)
		{
			if(k==pow(2,n))
			k=0;
			frame_number.push_back(k);
		}
		j=frame_number.back()+1;
		
		for(int i=0;i<data_size;i++)
		{
			string a;
			cout<<"\nEnter data : ";
			cin>>a;
			sent.push_back(a);
		}
		
		do{
			send();
			receive();
		}while(pos1!=sent.size());
		
		cout<<"\n\nDo you want to continue?(Y/N) ";
		cin>>ch;
	}while(ch=='y' || ch=='Y');
}
