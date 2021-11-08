#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define RAISE(i) pow(2,i)
using namespace std; 
class HammingCode{
	int *data;
	int *rdbits;
	int dsize;
	int *codeWord, *wordRcvd;
	int cws,i,j,rdb;
	int randomBit(int size)
{
	srand(time(0));
	int bit = rand()%(size + 1 );
	return bit;
}

	public:
		HammingCode(int s)
		{
			dsize = s;
			data = new int[dsize];
			rdbits = 0;
			codeWord = 0;
			wordRcvd = 0;
			cws = 0;
			rdb = 0;
			i=j=0;
		}
		~HammingCode()
		{
			delete[] data;
			delete[] codeWord;
			delete[] rdbits;
			delete[] wordRcvd;
 			
		}
	void copyWord()
	{
	wordRcvd = new int[cws];
	for(i=0;i<cws;i++)
		wordRcvd[i] = codeWord[i];
	int bit = randomBit(cws-1);	
	cout<<"\nChanging at pos "<<bit+1<<endl;
	wordRcvd[bit] = !(wordRcvd[bit]);
	}
	
	
		void calcRDB()
	{
		int temp = dsize + 1;
		while( RAISE(rdb) < rdb+temp)
		{
			rdb++;
		}
		cws = rdb + dsize;
		//cout<<"\n RDBITS: "<<rdb;
		}
	void getData()
	{
		cout<<"\nEnter the data bitwise: \n";
		for(i=dsize-1;i>=0;i--)
			{
			cout<<": ";
			cin>>data[i];
			}
			}
	
	void displayData()
	{
		cout<<"\nEntered data is: ";
		for(i=dsize-1;i>=0;i--)
				cout<<data[i]<<" ";
	}
	void formCodeWord()
	{
		int j=0,k=0;
		//cout<<"CWS: "<<cws<<endl;
		codeWord = new int[cws];
	i=0;
		while(i<cws){
		
			if(i==(RAISE(j)-1))					
				{
					//cout<<"\ni: "<<i;
				codeWord[i++] = 0;
				j++;}
			else
				{
					//cout<<"\nj: "<<j;
				codeWord[i++] = data[k++]; 
			}
			
			
}
	checkParities(codeWord);
	assignRDB(codeWord);
	}

void checkParities(int *WORD)
{
	rdbits = new int[rdb];
	for(i=0;i<rdb;i++)
		rdbits[i]  = 0;
	int tempComp = 0,anchor;
	int sum = 0;
	for(i=0;i<rdb;i++)	// for no of rdbits
	{
		anchor = RAISE(i);
		sum = 0;
		for(j = 0;j<cws;j++)
		{
			tempComp = j+1;
			
				if( tempComp & anchor )
				{
					sum += WORD[tempComp-1];
				}
			}
			if( sum % 2 == 0 )
				rdbits[i] = 0;
			else
				rdbits[i] = 1;
			 
		}
	
//for(i=0;i<rdb;i++)
//		cout<<"\n"<<rdbits[i];
	}
void assignRDB(int *WORD)
{ int k=0;
	i=j=0;
		while(i<cws){
		
			if(i==(RAISE(j)-1))					
				{
					//cout<<"\ni: "<<i;
				WORD[i++] = rdbits[j];
				j++;}
			else
				{
					//cout<<"\nj: "<<j;
				WORD[i++] = data[k++]; 
			}
			
			
}
}
void checkCodeWord()
{
	int decN = 0;
	copyWord();
	cout<<"\nRECIEVED CODE WORD: ";
	displayWord(wordRcvd);
	checkParities(wordRcvd);

		for(i=0,j=0;i<rdb;i++,j++)
		{
			if( rdbits[i]==1 )
				decN += RAISE(j);
		}
cout<<"\nEvaluated redundant bits: ";
for(i=0;i<rdb;i++)
		cout<<" "<<rdbits[i]<<" ";
if(decN)
	cout<<"\nERROR IN TRANSMISSION ( Error at pos "<<decN<<" ) ";
else
	cout<<"No error found";
		}

void displayCW()
{
	cout<<"\n\nCODE WORD: ";
	displayWord(codeWord);
}
	
void displayWord(int *WORD)
{
		
		for(i=cws-1;i>=0;i--)
				cout<<WORD[i]<<" ";
		cout<<endl;
}
};
int main()
{
	int s;
	cout<<"Enter the size of dataword: ";
	cin>>s;
	HammingCode object(s);
	object.calcRDB();
	object.getData();
	object.displayData();
	object.formCodeWord();
	//sender.displayCW();
	//sender.checkParities();
	object.displayCW();
	object.checkCodeWord();
	
	return 0;
}
