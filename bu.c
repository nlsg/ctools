#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define _strfree(A) sizeof((A))-strlen((A))

int main(int argc, char ** argv)
{	clock_t t1 = clock();
	char files[2][128] = {"\n","\n"}
		,optlist[32]
		,cmd[512]
		,date_fmt[] = "$(date '+%d%b_%H%M')"
		,usage[64];
		;
	uint n =1;
	sprintf(usage,"usage: %s [options] [File to Backuo]\n-h -> help\n",argv[0]);
	if (argc < 2)
	{	printf("no file given!\n%s", usage);
		return 0;
	}
	for(int i = 1; i < argc; i++)
	{	if(argv[i][0] == '-')
		{	for(short i_ = 0; i_ < strlen(argv[i]) -1;i_++)
				optlist[(n++)-1] = argv[i][i_+1];
		}else
		{	if (files[0][0] == '\n')
				strncpy(files[0], argv[i], _strfree(files[0]));
			else if (files[1][0] == '\n')
				strncpy(files[1], argv[i], _strfree(files[1]));
			else
			{	printf("to many args!\n%s", usage);
				break;
			}
		}
	}
	if (files[0][0] == '\n')
	{	printf("no file given!\n%s", usage);
		return 0;
	}
	else if (files[1][0] == '\n')
		strcpy(files[1],files[0]);
	
	sprintf(cmd,"cp -r %s %s.bu%s"
			,files[0],files[1],date_fmt);
	system(cmd);
/*
	printf("\nprogram took: %fs",(double)(clock() - t1)/CLOCKS_PER_SEC);
	printf("\noptlist: %s\nsrc: %s\ndest: %s\n"
		,optlist,files[0],files[1]);
*/
	return 0;
}
