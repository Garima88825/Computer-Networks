#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*
Class A: 0 - 127
Class B: 128 - 191
Class C: 192 - 223
Class D: 224 - 239
Class E: 240 - 255 
*/
// check if given string is a numeric string or not
bool isNumber(const string& str)
{
	// std::find_first_not_of searches the string for the first character
	// that does not match any of the characters specified in its arguments
	return !str.empty() &&
		(str.find_first_not_of("[0123456789]") == std::string::npos);
}

// Function to split string str using given delimiter
vector<string> split(const string& str, char delim)
{
	auto i = 0;
	vector<string> list;

	auto pos = str.find(delim);

	while (pos != string::npos)
	{
		list.push_back(str.substr(i, pos - i));
		i = ++pos;
		pos = str.find(delim, pos);
	}

	list.push_back(str.substr(i, str.length()));

	return list;
}

// Function to validate an IP address
bool validateIP(string ip)
{
	// split the string into tokens
	vector<string> list = split(ip, '.');

	// if token size is not equal to four
	if (list.size() != 4)
		return false;

	// validate each token
	for (string str : list)
	{
		// verify that string is number or not and the numbers
		// are in the valid range
		if (!isNumber(str) || stoi(str) > 255 || stoi(str) < 0)
			return false;
	}

	return true;
}
void detClass(string ip){
	// split the string into tokens
	vector<string> list = split(ip, '.'); 
	auto i = list.begin();
	auto j = list.end();
	if (stoi(*i)>=0 && stoi(*i)<=127){
		cout<<"\nClass A\n";
		cout<<"The Network address is: ";
		cout<<*i;
		for (auto i = list.begin()+1; i != list.end(); ++i){
			cout<<".";
			cout<<"0";
    	}
    	cout<<"\n";
    	cout<<"\nThe Broadcast address is: ";
    	cout<<*i;
		for (auto i = list.begin()+1; i != list.end(); ++i){
        	cout << "."<<"255";
    	}
    }
	else if (stoi(*i)>=128 && stoi(*i)<=191){
		cout<<"\nClass B\n";
		cout<<"The Network address is: ";
		auto k=list.begin() + 1;
    	cout<<*i<<"."<<*k;
		for (auto i = list.begin()+2; i != list.end(); ++i){
			cout << "."<<"0";
    	}
    	cout<<"\n";
    	cout<<"\nThe Broadcast address is: ";
    	cout<<*i<<"."<<*k;
		for (auto i = list.begin()+2; i != list.end(); ++i){
        	cout << "."<<"255";
    	}
	}
	else if (stoi(*i)>=192 && stoi(*i)<=223){
		cout<<"\nClass C\n";
		cout<<"The Network address is: ";
		for (auto i = list.begin(); i != list.end(); ++i){
			if(i == list.end()-1){
				cout<<"0";
				break;
			}
        	cout << *i << ".";
    	}
    	cout<<"\nThe Broadcast address is: ";
		for (auto i = list.begin(); i != list.end(); ++i){
			if(i == list.end()-1){
				cout<<"255";
				break;
			}
        	cout << *i << ".";
    	}
        
}
	else if (stoi(*i)>=224 && stoi(*i)<=239){
		cout<<"\nClass D\n";
		cout<<"Can Neither Define Network Address Nor Broadcast Address !!!";
}
	else if (stoi(*i)>=240 && stoi(*i)<=255){

		cout<<"\nClass E\n";
		cout<<"Can Neither Define Network Address Nor Broadcast Address !!!";
}
}
int main(){
	string ip;
	char ch='y';
	do{
	cout<<"Enter the IP address in dotted decimal format: ";
	cin>>ip;
	bool flag=validateIP(ip);
	if(flag){
		cout<< "The IP address "<<ip<<" is valid";
	}else{
		cout<< "The IP address "<<ip<<" is invalid";
		break;
	}
	detClass(ip);
	cout<<"\nDo you wish to continue?[Y/N]: ";
	cin>>ch;
}while(ch=='y' || ch=='Y');
	return 0;
}
