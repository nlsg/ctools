#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define PLAYER "mpv" //define player here (note that -v option needs to be adapted)
#define dmenu //delete or comment this line if u want to use fzf instead of dmenu

#define devour_flg 0b1
#define video_flg  0b10

#define _b "\033[1m" //macro to set text bold 
#define _n "\033[0m" //macro to reset bold (n -> normal) 

int main(int argc, char ** argv)
{
	char str_[128],cmd[512];
	int c;
	uint8_t flags = 0; // 0b...vd
	while((c = getopt(argc, argv, "hdv")) != -1)
		switch(c)
		{	case 'h':
			printf(_b"usage:"_n" %s [options]\n\t-h -> print this help"
					"\n\t-d -> 'devour' used to play in background, process may needs to be killed manualy"
					"\n\t-v -> uses mpv's --no-video option"
					"\n\t-a -> add a channel (NAME:LINK)"
					"\n"_b"add a station:"_n" echo -e  \"[NAME]\\t\\t| [LINK]\" >> ~/.config/stations"
					"\n"_b"dependencies:"_n
					"\n\tmpv\n\tdmenu or fzf(needs to be defined in source, default is dmenu)"
					"\n\tdevour(not necessary)\n"
					,argv[0]);
			return 0;
			case 'd':
			flags |= 0b1;
			break;
			case 'v':
			flags |= 0b10;
			break;
		}
#ifdef dmenu
	FILE * fp = popen("cat $HOME/.config/stations | dmenu -l 30", "r");
#else
	FILE * fp = popen("cat $HOME/.config/stations | fzf", "r");
#endif
	fgets(str_,sizeof(str_),fp);
	strtok(str_,"|");
	strcpy(str_, strtok(NULL," "));
	pclose(fp);

	sprintf(cmd,"%s "PLAYER" %s %s"
			,(flags & devour_flg ? "devour":"")
			,(flags & video_flg  ? "--no-video":"")
			,str_
		   );
	system(cmd);
	return 0;
}
