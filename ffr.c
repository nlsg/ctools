#include <stdio.h>

int main(int argc, char ** argv)
{	if (argc != 1)
		printf("usage: %s\n\tthis program refreshes firefox.\n\tffr -> FireFoxRefrash\n",argv[0]);
	system("kill $(pidof firefox) && firefox");
	return 0;
}

