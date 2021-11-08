/*
	Name: Garima Pandey
	Description: To generate crc bits and detect the error
*/

#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;

void check(int degree,int &c,int temp[],int ndw[],int bin[])
{
        for(int i=0;i<degree;i++)
        temp[i]=temp[i+1];
        temp[degree]=ndw[c++];
        for(int i=0;i<degree;i++)
        temp[i]=temp[i+1];
        temp[degree]=ndw[c++];
}

void check2(int degree,int &c,int temp[],int ndw[],int bin[])
{
    for(int i=0;i<degree;i++)
        temp[i]=temp[i+1];
        temp[degree]=ndw[c++];
}

// FUNCTION TO TAKE POLYNOMIAL AS INPUT

void inpoly(int degree,int pol[])
{
    for(int i=0;i<=degree;i++)
    {
            cout<<"Enter the coefficent of x^"<<(degree-i)<<" :";
            cin>>pol[i];
    }
}

// FUNCTION TO PRINT THE POLYNOMIAL 

void outpoly(int degree,int pol[])
{
    cout<<"\nThe entered polynomial is :";
    for(int i=degree;i>=0;i--)
    {
        if(i==0)
        cout<<pol[degree-i];
        else
        cout<<pol[degree-i]<<"x^"<<i<<" + ";
    }
}

// FUNCTION TO PRINT POLYNOMIAL IN BINARY FORM

void binpoly(int degree,int pol[],int bin[])
{	
    for(int i=0;i<=degree;i++)
    {
        if(pol[i]>0)
        {
            bin[i]=1;
        }
        else
            bin[i]=0;
    }
    cout<<endl<<"\nThe polynomial in binary(divisor) :";
    for(int i=0;i<=degree;i++)
    {
        cout<<bin[i];
    }
}

// FUNCTION TO TAKE DATAWORD AS INPUT

void indw(int dw[],int s)
{
    cout<<endl<<"\nEnter the dataword in binary :";
    for(int i=0;i<s;i++)
    cin>>dw[i];	
}

// FUNCTION TO PRINT THE DATAWORD

void outdw(int dw[],int s)
{
    cout<<endl<<"The entered dataword :";
    for(int i=0;i<s;i++)
    cout<<dw[i];
}

// FUNCTION TO COMPUTE THE DIVIDEND BY APPENDING THE DATAWORD

void outndw(int s,int degree,int s1,int ndw[],int dw[])
{
    for(int i=0;i<s;i++)
    {
        ndw[i]=dw[i];
    }
    for(int i=0;i<degree;i++)
    {
        ndw[i+s]=0;
    }
    cout<<endl<<"\nThe appended dataword(dividend) : ";
    for(int i=0;i<s1;i++)
    cout<<ndw[i];
}

// FUNCTION TO COMPUTE THE CRC BITS AND GENERATE THE CODEWORD

void div(int degree,int s1,int cd[],int bin[],int ndw[],int temp[])
{
    int i,k=0,c=0;
    for(int i=0;i<=degree;i++)
    {
        temp[i]=bin[i]^ndw[i];
        c++;
	}
    while(c<s1)
    {
		if(temp[1]==0)
		check(degree,c,temp,ndw,bin);
		else
		check2(degree,c,temp,ndw,bin);

		for(int i=0;i<=degree;i++)
		{
			temp[i]=bin[i]^temp[i];
		}	
	}
	cout<<endl<<"\nThe CRC bits : ";

		for(int i=1;i<=degree;i++)
	{
			cout<<temp[i];	
	}

	for(int i=0;i<(s1-degree);i++)
	{
		cd[k]=ndw[i];
		k++;
	}

	for(int i=1;i<=degree;i++)
	{
		cd[k++]=temp[i];
	}

	cout<<endl<<"\nThe codeword : ";
	for(int i=0;i<s1;i++)
	{
		cout<<cd[i];
	}
}



void func(int s1,int r,int cd[],int ndw1[])
{
    if(r==0)
    {
        return;
    }
    else
	    ndw1[r-1]=cd[r-1]^1;
}

// FUNCTION TO PRINT THE CODEWORD RECEIVED

void routdw(int s1,int ndw1[])
{
    cout<<endl<<"\nThe received codeword : ";
    for(int i=0;i<s1;i++)
    cout<<ndw1[i];
}

/* 
   FUNCTION TO COMPUTE THE CRC BITS AND GENERATE THE CODEWORD AT THE RECEIVER END AND 
   CHECK IF THE CODEWORD HAS AN ERROR
*/

void div2(int degree,int s1,int bin[],int ndw1[],int temp[])
{
    int i,k=0,c=0;
    for(int i=0;i<=degree;i++)
    {
        temp[i]=bin[i]^ndw1[i];
        c++;
	}
    while(c<s1-1)
    {
		if(temp[1]==0)
		check(degree,c,temp,ndw1,bin);
		else
		check2(degree,c,temp,ndw1,bin);

		for(int i=0;i<=degree;i++)
		{
			temp[i]=bin[i]^temp[i];
		}
	}
    while(c<s1)
    {
		check(degree,c,temp,ndw1,bin);	
		for(int i=0;i<=degree;i++)
		{
			temp[i]=bin[i]^temp[i];
		}
    }
    
/*	cout<<endl<<"\nThe CRC bit : ";

    for(int i=0;i<=degree;i++)
	{
        cout<<temp[i];	
	}
*/
	int flag=1;
	for(int i=0;i<=degree;i++)
	{
		if(temp[i]!=0)
		{
			
			flag=0;
			break;
		}
	}

	if(flag==0)
	cout<<endl<<"There is an error in the received codeword !"<<endl;
	else
	cout<<endl<<"The received codeword is correct !"<<endl;
}

// MAIN FUNCTION

int main()
{
    int degree,s,s1,n;
    int *pol,*bin,*dw,*ndw,*ndw1,*temp,*cd;
    cout<<"SENDER END :"<<endl;
    cout<<"Enter the polynomial degree : "<<endl;
    cin>>degree;
    pol=new int[degree+1];
    bin=new int[degree+1];
    
    inpoly(degree,pol);
    outpoly(degree,pol);
    binpoly(degree,pol,bin);
    cout<<endl<<"Enter the size of dataword : "<<endl;
    cin>>s;
    dw=new int[s];
    indw(dw,s);
    outdw(dw,s);
    s1=degree+s;
    ndw=new int[s1];
    outndw(s,degree,s1,ndw,dw);
    temp=new int[degree+1];
    cd=new int[s1];
    div(degree,s1,cd,bin,ndw,temp);
    
    ndw1=new int[s1];
    ndw1=cd;
    cout<<endl;
    cout<<endl<<"\nRECEIVER END :"<<endl;
    n=rand()%s1;
    func(s1,n,cd,ndw1);
    routdw(s1,ndw1);
    div2(degree,s1,bin,ndw1,temp);
    return 0;
}
