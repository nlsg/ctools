#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{	char cmd[1048] = "links https://duckduckgo.com/?q=";
	for (int i = 1; i < argc;++i)
		{	strcat(cmd,argv[i]);
			strcat(cmd,"+");
		}
	system(cmd);
	return 0;
}
