#include<iostream>
#include<math.h>
#include<stdlib.h>

using namespace std;
void bin(int n,int **ar);

void indw(int dw[],int m)
{
    cout<<endl<<"Enter the dataword :";
    for(int i=m-1;i>=0;i--)
    cin>>dw[i];	
}

int calc_r(int m)
{
    int r;
    for(int i=1;;)
    {
        if(pow(2,i)>=m+i+1)
        {
            r=i;
            break;
        }
        else
        {
            i++;
        }
    }
    return r;
}

void outdw(int dw[],int m)
{
    cout<<endl<<"The entered dataword is : ";
    for(int i=m-1;i>=0;i--)
    cout<<dw[i];
}

void create_hc(int m,int r,int dw[],int hc[],int rb[])
{
    for(int i=0;i<r;i++)
    {
        rb[i]=7;
    }
    int k,j=0;

	for(int i=0;i<r;i++)
    {
        k=pow(2,i);
        hc[k]=rb[i];
    }

	for(int i=1;i<=m+r;i++)
    {
        if(hc[i]!=7)
        {
            hc[i]=dw[j];
            j++;
        }
    }

/*	cout<<endl<<"The format of hamming code is : ";
    for(int i=m+r;i>0;i--)
    {
        
        cout<<hc[i];
    }
*/
}

void func(int m,int r,int dw[],int hc[],int rb[])
{
    int **ar;
    ar=new int*[m+r];
    for(int i=1;i<=m+r;i++)
    {
        ar[i]=new int[r];
    }

	for(int i=1;i<=m+r;i++)
		for(int j=0;j<r;j++)
		{
			ar[i][j]=0;
		}

	for( int i=1;i<=m+r;i++)
    {
        bin(i,ar);
	}

	int i,k,ctr=0;

    for(int j=0;j<r;j++)
    {
        ctr=0;		
		for(i=1;i<=m+r;i++)
		{
			if(ar[i][j]==1)
			{
				if(hc[i]==1)
				ctr++;
			}
		}

		if(ctr%2==0)
		{
			rb[j]=0;
		}
		else rb[j] = 1;
	}

/*	cout<<endl<<"The value of redundant bits are : \n";
    for(int i=0;i<r;i++)
    {
        cout<<"r["<<pow(2,i)<<"]="<<rb[i]<<endl;
    }
*/
    for(int i=0;i<r;i++)
    {
        k=pow(2,i);
        hc[k]=rb[i];
    }

}
    
void outhc(int s,int hc[])
{
    
    for(int i=s;i>0;i--)
    {
	    cout<<hc[i];
    }
}

void bin(int n,int **ar)
{
    int h,k=0;
    h=n;
    while(n>0)
    {
        ar[h][k]=n%2;
        n=n/2;
        k++;
    }
}

int dec(int r,int rb[])
{
    int s=0;
    for(int i=0;i<r;i++)
    {
        s=s+(rb[i]*pow(2,i));
	} 
	return s;
}

int main()
{
    cout<<"SENDER-END"<<endl;
    int m,s,r,ch,*dw,*hc,*rb,*rb1,n,k;
    cout<<"Enter the size of dataword : ";
    cin>>m;
    dw=new int[m];
    indw(dw,m);
    outdw(dw,m);
    r=calc_r(m);
    
    cout<<endl<<"The number of redundant bits are : "<<r;
    hc=new int[m+r];
    rb=new int[r];
    rb1=new int[r];
    create_hc(m,r,dw,hc,rb);
    func(m,r,dw,hc,rb);
    cout<<"\nThe codeword generated is : ";
    outhc(m+r,hc);
    cout<<"\n_______________________________________\n";
    cout<<endl<<"RECEIVER-END"<<endl;
    cout<<endl<<"1.Noise-less or 2.Noisy ?"<<endl;
    cin>>ch;
    
    if(ch==1)
    {
        cout<<"The Recieved codeword : ";
        for(int i=m+r;i>0;i--)
	    {
	        cout<<hc[i];
    	}
        cout<<endl<<"The received codeword is CORRECT !!"<<endl;	
    }
    else
    {
        cout<<"The received codeword : ";
        
        n=rand()%(m+r);
        if(n==0)
        {
            outhc(m+r,hc);
            cout<<endl<<"The received codeword is correct";
        }
        else
        {
			hc[n]=hc[n]^1;
			outhc(m+r,hc);
			cout<<endl<<"The received codeword is incorrect"<<endl;
			for(int i=0;i<r;i++)
			{
				rb1[i]=rb[i];
			}
        
			func(m,r,dw,hc,rb1);
		
			s=dec(r,rb1);
			cout<<"There is a ERROR at "<<s<<" position"<<endl;
			
			hc[s]=hc[s]^1;
			for(int i=0;i<r;i++)
		    {
				k=pow(2,i);
				hc[k]=rb[i];
			}

			cout<<endl<<"The codeword after correction : ";
	        outhc(m+r,hc);
        }
	}
    return 0;
}


 


 


 

