#include<iostream>
#include<string>
#include<math.h>
#include<random>
using namespace std;
string binary_add(string, int); // This is a function to calculate the binary addition of the frames
string format_data(string,int); //This function checks for integrity of the data entered.
string add(string a, string b); //final addition
string complement(string s){
	string final="";
	for(int i=0;i<s.length();i++){
		if(s[i]=='0'){
			final+='1';
		}
		else
			final+='0';
	}
	return final;
}
int main()
{
	int ck_size,dw_size; //Storing checksum and dataword sizes
	string data, final_data; //Store dataword
	cout<<" SENDER'S SIDE "<<endl;
	cout<<"\nEnter the length of checksum : ";
	cin>>ck_size;
	cout<<"\nEnter the size of dataword : ";
	cin>>dw_size;
	char ar[dw_size];
	cout<<"\nEnter the dataword : ";
	cin>>data;
	final_data = format_data(data, dw_size);
	cout<<"\nThe dataword is : ";
	for(int i=0; i< final_data.length() ;i++)
	{
		ar[i]=final_data[i];
		if((i % ck_size== 0))
		{
			cout<<" ";
		}
		cout<<final_data[i];

	}
	cout<<endl;
	//for(int i=0;i<final_data.length();i++){
	//	cout<<ar[i];
	//}
	string outcome=binary_add(final_data,ck_size);
	string cksum=complement(outcome);
	cout<<"\nThe checksum bits : "<<cksum;
	string code=final_data+cksum;
	cout<<"\nThe codeword : "<<code;
	int s1=dw_size+ck_size;
	cout<<"\n----------------------------------------";
	cout<<"\nRECEIVER'S' END";
	cout<<"\n----------------------------------------";
	//int n=rand()%s1;
	char choice;
	cout<<"\n\nDo you want a noisy channel or a noiseless channel communication ? Kindly enter your choice.\n";
	cout<<"1.NOISY \n2.NOISELESS\n";
	cin>>choice;
	data=code;
	if(choice=='2'){
		//data=code;
    	cout<<"\nThe received codeword : "<<data;
    	outcome=binary_add(data,ck_size);
    	cksum=complement(outcome);
    	cout<<"\nThe checksum bits : "<<cksum<<"\nNO ERROR\nDATA ACCEPTED!!!";
	}
	else{
	    //data=code;
		int range = data.length();
		//cout<<range;
		int num = rand() % range;
		//cout<<num<<endl;
		if (data[num]=='0'){
			data.at(num)='1';
		}
		else{
			data.at(num)='0';
		}
		//data= data[num]=="0" ? data[num]="1" : data[num]="0";
		cout<<"\nThe received codeword : ";
		for(int i=0;i<data.length();i++){
			cout<<data[i];
		}	
		outcome=binary_add(data,ck_size);
		cksum=complement(outcome);
		cout<<"\nThe checksum bits : "<<cksum<<"\nERROR!!";
	}
		
	return 0;
}
string format_data(string dw,int len)
{
	if(dw.length() < len)
	{
		string appnd = string(len - dw.length(), '0'); //string builder with required zero's to most significant bits
		dw = appnd + dw;
		return dw;
	}
	else
	{
		return dw;
	}
}
string binary_add(string dw, int numbit)
{
	string sum="";
	string temp;
	for(int i=numbit;i<=dw.length();i=i+numbit)
	{
		temp="";
		
		for(int j=i-numbit;j<i;j++)
			temp=temp+dw[j];
		sum=add(sum,temp);		
	}
	if(sum.length()>numbit)
	{
		int x=sum.length()-numbit;
		string y=sum.substr(0,x);
		sum=add(sum.substr(x,sum.length()),y);
	}
	return sum;
}
string add(string a,string b)
{
	string result = ""; // Initialize result 
    int s = 0;          // Initialize digit sum 
  
    // Traverse both strings starting from last 
    // characters 
    int i = a.size() - 1, j = b.size() - 1; 
    while (i >= 0 || j >= 0 || s == 1) 
    { 
        // Comput sum of last digits and carry 
        s += ((i >= 0)? a[i] - '0': 0); 
        s += ((j >= 0)? b[j] - '0': 0); 
  
        // If current digit sum is 1 or 3, add 1 to result 
        result = char(s % 2 + '0') + result; 
  
        // Compute carry 
        s /= 2; 
  
        // Move to next digits 
        i--; j--; 
    } 
    return result; 
}
