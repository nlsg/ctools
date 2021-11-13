#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nls.h>

#define TERM "urxvt -tr -sh 60"
#define NOTIFY "notify-send"

#define OUT_BUFFER 4096
int main(int argc, char** argv)
{	if(argc == 1 || check_opt('h'))
	{	usage_and_exit:
		printf(_b"usage:"_n" %s [option] [cmd1] -a [cmd2] ... -a cmd[8]\n"
			_b"options:"_n
			"\n\t-a add another command"
			"\n\t-q quiet mode -> stdout as notification instead of opening a terminal"
			"\n"
			,argv[0]);
		return 0;
	}
	char cmd[8][256] = {"\0","\0","\0","\0"};
	short cmd_it = 0;
	for (int i = 1 + check_opt('q'); i < argc;++i)
		{	if(argv[i][0] == '-' && argv[i][1] == 'a')
			{	cmd_it++;
				continue;
			}
			if(cmd_it == 8-1)
				break;
			strncat(cmd[cmd_it],argv[i],sizeof(cmd[0]));
			strncat(cmd[cmd_it]," ",1);
		}
	if(check_opt('q'))
	{	if(argc <= 2)
			goto usage_and_exit;
		char out[OUT_BUFFER] ="", out_[OUT_BUFFER] ="", buff[256] ="";	
		for(short i = 0; i < (sizeof(cmd)/sizeof(cmd[0]));i++)
		{	if(cmd[i][0] == '\0')
				break;
			FILE * fp = popen(cmd[i],"r");
			while (fgets(buff, sizeof(buff),fp) != NULL)
				strncat(out,buff,sizeof(out));
			sprintf(out_,NOTIFY" \"%s - $?\" \"%s\"",cmd[i],out);
			printf("\nout (%c,%c):\n%s\n", out_[strlen(out_)], out_[strlen(out_)-1], out_);
			system(out_);
			bzero(out,sizeof(out));
			bzero(out_,sizeof(out_));
			pclose(fp);
		}
	}else
		system("cp ~/.bashrc /tmp/bashrc.tmp");
		FILE * fp = fopen("/tmp/bashrc.tmp","a");
		for(short i = 0; i < (sizeof(cmd)/sizeof(cmd[0]));i++)
			fprintf(fp,"%s\n",cmd[i]);	
		fclose(fp);
		system(TERM" -e bash -rcfile /tmp/bashrc.tmp");
	}
	return 0;
}
