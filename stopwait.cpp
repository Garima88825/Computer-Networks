#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
using namespace std;

int x=0;
struct packet
{
    int data;
};

struct frame
{						
    packet pdata;
    int seq;
};

void net_to_data(int data)
{
    cout<<"DATA "<<data<<" IS CONVERTED TO PACKET\n";
}

void net_to_dataA(int data)
{
    cout<<"NOW , THE ACKNOWLEDGEMENT "<<data<<" IS CONVERTED TO PACKET\n";
}

void data_to_phyA(int ack)
{
    cout<<"NOW , PACKET IS CONVERTED TO FRAME(ACK)\n";
	cout<<"SEQUENCE NUMBER : "<<ack<<"\n";
    cout<<"ACKNOWLEDGEMENT SENT TO SENDER"; 
}

void data_to_phy(frame f1)
{
    packet pack=f1.pdata;
    cout<<"NOW , PACKET IS CONVERTED TO FRAME WITH DATA "<<pack.data<<endl;
	cout<<"SEQUENCE NUMBER : "<<f1.seq<<"\n";
    cout<<"FRAME SENT TO RECEIVER"; 
}

void phy_to_data(frame f)
{
    packet p=f.pdata;
    int no=f.seq;
    cout<<"FRAME RECEIVED FROM THE PHYSICAL LAYER OF RECEIVER\n";
    cout<<"DATA :"<<p.data<<"\tSEQUENCE NUMBER : "<<no<<endl;
}

void data_to_net()
{
    cout<<"NOW , THE FRAME IS CONVERTED BACK TO PACKET\n";
}

int receiver_side(frame f,int st)
{
    packet p;
    int  d;
    int s;
    cout<<"\n\n__________ RECEIVER SIDE __________\n\n";

	if(st==5)
        cout<<"FRAME DISCARDED !";
    else
    {		
        phy_to_data(f);
        p=f.pdata;
        s=f.seq;
        d=p.data;
        data_to_net();
    }

	if(s==0)
		s=1;
	else
		s=0;

	cout<<"\nACKNOWLEDGEMENT TRANSMISSION\n";
	net_to_dataA(s);
	data_to_phyA(s);
    return s;
}

int sender_side(int data,int s,int c)
{
    int var=-1;
    int check;
    packet pack;
    pack.data=data;
    cout<<"\n\n__________ SENDER SIDE __________\n\n";
    frame f1;
    f1.pdata=pack;
    f1.seq=s;
    if(x==0){
    net_to_data(data);
    data_to_phy(f1);
	}

	if(c==1||c==2||c==3)
    {
    	x=1;
		for(int i=0;i<500000000;i++);
		cout<<"\nACKNOWLEDGEMENT NOT RECEIVED !";
        return var;
    }
    
    else if(c==5)
    {
        check=receiver_side(f1,5);
        cout<<"\n\n__________ SENDER SIDE __________\n\n";

		if(check>1)
            cout<<"ACKNOWLEDGEMENT FAILED \n";
        else
            cout<<"ACKNOWLEDGEMENT RECEIVED BY THE SENDER TO SEND DATA FRAME OF SEQUENCE NUMBER : "<<check<<endl;		
    }
    else
    {
        check=receiver_side(f1,0);
        cout<<"\n\n__________ SENDER SIDE __________\n\n";

		if(check>1)
            cout<<"ACKNOWLEDGEMENT FAILED \n";
        else
            cout<<"ACKNOWLEDGEMENT RECEIVED BY THE SENDER TO SEND DATA FRAME OF SEQUENCE NUMBER : "<<check<<endl;
    }
    return 0;
}

int main()
{
    int t;
    int n,i;
    cout<<"ENTER THE NUMBER OF DATA YOU WANT TO SEND : ";
    cin>>n;
    int data[n];

	for(i=0;i<n;i++)
    {
        cout<<"ENTER DATA "<<i+1<<": ";
        cin>>data[i];
    }

	cout<<endl;
    for(i=0;i<n;i++)
    {
        int ch;
        //srand(time(NULL));
        t=rand()%4;
        switch(t)
        {
            
			case 1:
            	cout<<"-----------------------------------------------------------------------------------------------------";
				cout<<"\nCASE : FRAME DAMAGED"<<endl;
				ch=sender_side(data[i],(i+1)%2,t);
				if(ch==-1)
				{
					cout<<"\nFRAME SENT AGAIN...\n";
					ch=sender_side(data[i],(i+1)%2,0);
				}
				break;
            case 2:
            	cout<<"-----------------------------------------------------------------------------------------------------";
            	cout<<"\nCASE : FRAME IS LOST"<<endl;
				ch=sender_side(data[i],(i+1)%2,t);
				if(ch==-1)
				{
					cout<<"\nFRAME SENT AGAIN...\n";
					ch=sender_side(data[i],(i+1)%2,0);
				}
				break;
            case 3:
            	cout<<"-----------------------------------------------------------------------------------------------------";
				cout<<"\nCASE : ACKNOWLEDGEMENT IS LOST"<<endl;
				ch=sender_side(data[i],(i+1)%2,t);
				if(ch==-1)
				{
					cout<<"\nFRAME SENT AGAIN...\n";
					ch=sender_side(data[i],(i+1)%2,5);
				}
				break;
            default:
            	cout<<"-----------------------------------------------------------------------------------------------------";
				cout<<"\nCASE : SUCCESSFUL !!"<<endl;
				ch=sender_side(data[i],(i+1)%2,t);
				break;
        }
    }
    //cout<<"\nStop and wait completes ";
    return 0;
}
