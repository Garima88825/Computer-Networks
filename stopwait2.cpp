  
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#define MAX_TIME 5

using namespace std;

int fno=0;
const int FRAME_LOST = 101;
const int DAMAGED_FRAME = 011;
const int ACK_LOST = 100;
const int SUCCESS = 111;

int generateRandom()
{
	srand(time(0));
	int bit = rand()%(4 + 0);
	return bit;
}
struct Packet{
	string data;
};
struct Frame{
	Packet packet;
	int no;
};
struct ACK{
	int n ;
	ACK()
	{
		n = 0;
	}
};
ACK ack;
Packet rcv_data_layer(Frame frm)
{
	sleep(1);
	Packet pkt = frm.packet;
	int no = frm.no;
	return pkt;
}

string rcv_network_layer(Packet pkt)
{
	sleep(1);
	string msg = pkt.data;
	return msg;
}
void rcv(Frame frm)
{
	cout<<"\nSending frame F-"<<frm.no<<" to Data Layer\n";
	Packet pkt = rcv_data_layer(frm);
	sleep(1);
	cout<<"\n Sending packet to Network Layer\n\n";
	string msg = rcv_network_layer(pkt);
	sleep(1);
	cout<<"\nRECIEVED MESSAGE: "<<msg;
}
int generateError(Frame frm)
{
	cout<<"\n\nRECEIVER'S SIDE  \n\n";
	if(ack.n == frm.no){
	
int bit = generateRandom();	
switch(bit)
{
case 0: cout<<"\n DAMAGED FRAME!! \n";
		return DAMAGED_FRAME;
case 1: cout<<"\n FRAME NOT RECIEVED!! \n";
		return FRAME_LOST;
case 2: ack.n = !frm.no;	
		cout<<"\nFRAME F-"<<frm.no<<" RECIEVED, SENDING ACK ack-"<<ack.n;
		return ACK_LOST;
case 3: ack.n = !frm.no;	
		cout<<"\nFRAME F-"<<frm.no<<" RECIEVED, SENDING ACK ack-"<<ack.n;
		return SUCCESS;
}
}
else
{
	cout<<"\n DISCARDING DUPLICATE FRAME, RE-SENDING ACK ack-"<<ack.n;
	return SUCCESS;
}
}

Packet sender_network_layer(string msg)
{
	sleep(1);
	Packet pkt;
	pkt.data = msg;
	return pkt;
}

Frame sender_data_layer(Packet pkt, int no)
{
	sleep(1);
	Frame frm;
	frm.packet = pkt;
	frm.no = no;
	return frm;
}
void Sender(string message)
{
	cout<<"\nSENDER'S' END\n";
	cout<<"\n\nSending Message to Network Layer ";
	Packet pkt = sender_network_layer(message);
	cout<<"\n\nSending Packet to Data Layer ";
	Frame frm = sender_data_layer(pkt, fno);
	resend:
	cout<<"\n\nTransmitting Frame F-"<<fno;
	sleep(1);
	cout<<"\n\nFrame Transmitted, Waiting for ACK\n\n"; 
	int status = generateError(frm);
	switch(status)
	{
		case DAMAGED_FRAME: 
				sleep(3);
				cout<<"\n ACK NOT RECIEVED\n";
				goto resend;
				break;
		case FRAME_LOST: 
						sleep(3); 
						cout<<"\n ACK NOT RECIEVED\n";
						goto resend;
				break;
		case ACK_LOST: 	sleep(3); 
						cout<<"\n ACK NOT RECIEVED\n";
						goto resend;
				break;
		case SUCCESS: 	cout<<"\n\nTRANSMISSION SUCCESSFULL\n\nRECEIVER'S SIDE\n";
							rcv(frm);
							break;
	}
fno = !fno;
}


int main()
{
	string text;
	cout<<"\nEnter your message: ";
	getline(cin, text);
	Sender(text);
	return 0;
}
