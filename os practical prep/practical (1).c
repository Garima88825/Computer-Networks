#include <stdio.h>
#include <stdlib.h>
int main()
{
    int ch;
    printf("Enter your Choice(1= CPU Type/2= CPU Time/3= Memory):");
    scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			printf("\nCPU type and Model is:\n");
			system("awk \'NR==5{print $5}\' /proc/cpuinfo");
			printf("\nKernel Version is:\n");
			system("cat /proc/sys/kernel/osrelease");
			printf("\nAmount of time the System was last Booted\n");
			system("awk \'NR==1{print $1}\' /proc/uptime\n");break;

		case 2:
			printf("\nTime CPU spent in user mode, in system mode & when idle\n");
			system("awk \'NR==1{print $2 " " $4 " " $5}\' /proc/stat");
			printf("\nNumber of Accesses made to disk odn the System\n");
			system("awk \'NR==7{print $2}\' /proc/stat");
			printf("\nTime at which the System was last Booted\n");
			system("awk \'NR==9{print $2}\' /proc/stat");
			printf("\nNumber of Context Switch Kernel has Performed\n");
			system("awk \'NR==8{print $2}\' /proc/stat");
			printf("\nNumber of Processes Created Since the System was last Booted\n");
			system("awk \'NR==10{print $2}\' /proc/stat");break;

		case 3:
			printf("\nAmount of Memory Configured in System\n");
			system("awk \'NR==4{print $0}\' /proc/meminfo");
			printf("\nMemory Currently in System\n");
			system("awk \'NR==5{print $0}\' /proc/meminfo");break;
	}
    return 0;
}
