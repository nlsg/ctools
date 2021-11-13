#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{	if((!(argc == 2)) || (argv[1][1] == 'h'))
	{	printf("usage: %s [-e / -d]\n\t-e enable touchpad\n\t-d disable touchpad\n",argv[0]);
		return 0;
	}

	if (argv[1][0] == '-')
	{
		if (argv[1][1] == 'e')
			system("xinput set-prop 14 \"Device Enabled\" 1");	
		else if (argv[1][1] == 'd')
			system("xinput set-prop 14 \"Device Enabled\" 0");
	}
	return 0;
}
