#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		printf("no process entered");
		//cout<<"No process entered";
	}
	else if(pid==0)
	{
		execlp("/bin/ls","ls",NULL);
		printf("child process");
		//cout<<"child process";
	}
	else
	{
		printf("parent process");
		//cout<<"parent process";
	}
	return 0;
}
