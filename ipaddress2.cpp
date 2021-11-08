#include <bits/stdc++.h>
using namespace std;
void network(string);
int main()
{
string ip;
char ch='t';
while(ch=='t'||ch=='T')
{
cout<<"\t\tEnter the IP address in decimal form : ";
cin>>ip;
network(ip);
cout<<"\n\n\t\tPress t to continue  ";
cin>>ch;
}
}
bool valid(string s)
{
int n;
string str;
int c1=0, c2=0, c3=0;
s=s+'.';
int len=s.length();
for(int i=0;i<len;i++)
{
if(s.at(i)=='.')
{
if(i+1!=len && s.at(i+1)=='.')
c3++;
stringstream ss(str);
ss>>n;
c1++;
if(n<0 || n>255)
c2++;
str="";
}
else
{
str=str+s.at(i);
}
}
if(c1!=4 || c2!=0 || c3!=0)
return false;
else
return true;
}
void network(string ip)
{
if(valid(ip))
{
string st,st1,typeAddress,s=" ";
int r,a,t,countN=0,countB=0,count=0,n=ip.length();
for(a=0;a<n;a++)
{
if(ip[a]=='.')
{

st=ip.substr(0,a);
stringstream ss(st);
ss>>r;
break;
}
}
if(r>=0 && r<=127)
st1=ip.substr(a,n);
else if(r>=128 && r<=191)
{
for(int j=a+1;j<n;j++)
{
if(ip[j]=='.')
{
st1=ip.substr(j,n);
break;
}
}
}

else if(r>=192 && r<=223)
{
for(int j=n-1;j>=0;j--)
{
if(ip[j]=='.')
{
st1=ip.substr(j,n);
break;
}
}
}

int i=0,b=0;
int l=st1.length();
for(int i=0;i<l;i++)
{
s=" ";
while(st1[i]!='.'&&(i<l))
{
s=s+st1[i];
i++;
}
if(s==" 0")
++countN;
else if(s==" 255")
++countB;

if(st1[i]=='.')
++b;
}
if(countN==b)
typeAddress="\n\t\t\t\t Network Address";
else if(countB==b)
typeAddress="\n\t\t\t Broadcast Address";
else
typeAddress="\n\t\t\tNormal Address";

if(r>=0 && r<=127)
cout<<"\n\t\t\tClass A"<<typeAddress<<endl;

else if(r>=128 && r<=191)
cout<<"\n\t\t\tClass B"<<typeAddress<<endl;

else if(r>=192 && r<=223)
cout<<"\n\t\t\tClass C"<<typeAddress<<endl;

else if(r>=224 && r<=239)
cout<<"\n\t\t\tClass D"<<endl;

else if(r>=240 && r<=255)
cout<<"\n\t\t\tClass E"<<endl;
}
else
cout<<"\n\t\t\t\t\t Invalid IP Address."<<endl;

}
