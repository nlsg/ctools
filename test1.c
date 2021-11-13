#include <stdio.h>
#include <stdlib.h>

int main()
{
	system("echo first line >> test1_");
	system("cat test1_");
	FILE * fp = fopen("$HOME/cpp/test1_","a");
	fprintf(fp,"%s\n","appending");
	fclose(fp);
	printf("------")
	system("cat test1_");
	return 0;
}
