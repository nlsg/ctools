#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char ** argv)
{	char cmd[64]
		,prg[32] 
		,fp_buff[64]
		,sys_cmd[64]
		;
	short i;
	sprintf(prg,"%s",argc ==2 ? argv[1]:"a.out");

	sprintf(sys_cmd,"cat %s.ts",prg);
	printf("sys_cmd: %s\n", sys_cmd);
	/*
	FILE * fp = popen(sys_cmd,"r");
	printf("exec_cmd:\n");
	if (fp == NULL)
		printf("cmd_exec faild!\n");
	else
		while(fgets(fp_buff,sizeof(fp_buff),fp) != NULL)
			printf("line: %u\n%s\n\n", ++i,fp_buff);
	*/
	system(cmd);
	sprintf(cmd,"%s -k word -def wo3 fo -d",prg);
	printf("-->%s\n",cmd);
	system(cmd);
	sprintf(cmd,"%s -d word -f word",prg);
	printf("-->%s\n",cmd);
	system(cmd);
	printf("-->%s\n",prg);
	system(prg);
	return 0;
}
