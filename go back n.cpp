#include<iostream>
#include<string.h>
#include<time.h>
#include<math.h>
#include<windows.h>
using namespace std;

//P=physical layer, D=data link layer, N=network layer

int size;	//sending window size
int frame_number[100];
string sent[100],received[100];	//frames data sent and received
int data_size=0;	//how much of total data will be transmitted
int pos=0,pos1=0;	//keeping track of data transmitted and received
int S;	//how many elements to transmit
int ACK=0;
int ran,ran1=0; //for error

struct package{
	string info;
}*sending_p,receiving_p;

struct frame{
	string data;
	int seqNo;
}*sending_f,receiving_f;

//sender
void N_to_D(int S)
{
	for(int i=0,j=pos;i<S;i++,j++)
	sending_p[i].info=sent[j];
}

void D_to_P(int S)
{
	cout<<"\n\n--SENDER--";
	for(int i=0,j=pos;i<S;i++,j++)
	{
		sending_f[i].data=sending_p[i].info;
		sending_f[i].seqNo=frame_number[j];
		cout<<"\n\nTansmitting\n";
		for(int k=0;k<78;k++)
		{
			cout<<"_";
			Sleep(10);		
		}
		cout<<"\n>Frame Sent : "<<sending_f[i].data<<"-"<<sending_f[i].seqNo;
	}
}

void send()
{
	if(data_size-pos>=size)		//if remaining data is more or equal to sending window size
	S=size;
	else						//if remaining data is less than sending window size
	S=data_size-pos;
	
	N_to_D(S);
	D_to_P(S);
}


//receiver
void D_to_N(string info)
{
	receiving_p.info=info;
	Sleep(1000);
	cout<<"\n\nData received - "<<receiving_p.info;
	if(ACK==receiving_f.seqNo)
	{
		received[pos1++]=receiving_p.info;
		Sleep(500);
		ACK=frame_number[pos1];
		cout<<"\n|ACK sent : ACK-"<<ACK<<"|";
		if(ran!=2)
			pos++;
	}
	else
	{
		cout<<"\nDiscarded.";
		Sleep(500);
		cout<<"\n|ACK sent : ACK-"<<ACK<<"|";
		if(ran!=2)
		pos++;
	}
	Sleep(500);
}

void P_to_D(frame A)
{
	receiving_f.data=A.data;
	receiving_f.seqNo=A.seqNo;
	D_to_N(receiving_f.data);
}

void receive()
{
	cout<<"\n\n--RECEIVER--";
	srand(time(NULL));
	for(int i=0;i<S;i++)
	{
		//error
		ran=rand()%8;
		if(ran==0)
		{
			Sleep(1000);
			cout<<"\n\n**Frame Damaged**";
			return;
		}
		else if(ran==1)
		{
			Sleep(1000);
			cout<<"\n\n**Frame Lost**";
			return;
		}
		else if(ran==2)
		{
			P_to_D(sending_f[i]);
			Sleep(500);
			cout<<"\n**ACK Lost**";
			return;
		}
		P_to_D(sending_f[i]);
	}
}

//main
int main()
{
	int m; char ch;
	cout<<"Sending window size = (2)^m-1\nEnter m : ";
	cin>>m;
	size=pow(2,m)-1;
	cout<<"\nSending window size = "<<size;
	for(int i=0,j=0;i<100;i++,j++)
	{
		if(j==size+1)
		j=0;
		frame_number[i]=j;
	}
	sending_p=new package[size];
	sending_f=new frame[size];
	
	srand(time(NULL));	
	do{
		int d;	//how much more data to be sent
		cout<<"\n\nHow much packets you want to transmit - ";
		cin>>d;
		for(int i=data_size;i<d+data_size;i++)
		{
			cout<<"\nEnter data : ";
			cin>>sent[i];
		}
		data_size+=d;
		
		do{
			send();
			receive();
		}while(pos!=data_size);
		
		cout<<"\n\nDo you want to send more data? (Y/N)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	
	return 0;
}
