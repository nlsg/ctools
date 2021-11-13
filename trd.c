#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <iodef.h>

#define loc_max 4

#define cf_video_on		(conf & 0b00000001)
#define cf_devour_on	(conf & 0b00000010)

#define cf_video  0b00000001
#define cf_devour 0b00000010

int rget()
{	refresh();
	return getch();
}	
void do_exec(short conf)
{}
int main(int argc, char** argv)
{	int x,y,in_c = 0;
	short loc = 1,loc_, pane;
	char cmd[100];
	short conf = cf_devour;
	int arg_c;
	while ((arg_c = getopt(argc, argv, "vdh:")) != -1)
		switch(arg_c)
		{ case 'v':
			conf |= cf_video;
		  case 'd':
			conf &= ~cf_devour;
		}
	initscr();
	//start_ncurses(true,true);
	cbreak();
	noecho();
	curs_set(0);

	WINDOW * main_w 	= newwin(16,20, 5, 2);
	WINDOW * settings_w	= newwin( 8,20, 5,22);
	WINDOW * db_w   	= newwin( 8,20,13,22);
	  short db_y = 1, db_x = 1;

	printw(
		" _         _               _ _"
		"\n| |_ _   _(_)_ __ __ _  __| (_) ___"
		"\n| __| | | | | '__/ _` |/ _` | |/ _ \\"
		"\n| |_| |_| | | | | (_| | (_| | | (_) |"
		"\n \\__|\\__,_|_|_|  \\__,_|\\__,_|_|\\___/"

	);
	box(main_w, 0,0);
	box(db_w, 0,0);
	box(settings_w, 0,0);
	mvwprintw(main_w,0,1,"<stations>");	
	mvwprintw(main_w,1,2,"lofi hiphop");
	mvwprintw(main_w,2,2,"classic hiphop");
	mvwprintw(main_w,3,2," opt3");
	mvwprintw(main_w,4,2," opt4");
	mvwprintw(db_w,0,1,"<debug>");
	mvwprintw(settings_w,0,1,"<setting>");
	mvwprintw(settings_w,1,2,"video - %s", (cf_video_on ? "true" : "false"));
	
	char * buff[1024];
	{	FILE * fp;
		char c_;
		size_t i = 0;
		fp = popen("ls $HOME", "r");
		if (fp != NULL)
		{	while( (c_=fgetc(fp)) != EOF)
			buff[i++] = c_;
		}
		
		mvprintw(8, 60,"i:%u",i);
		mvprintw(10,80,"%s",&buff);
		pclose(fp);
	}
		y = db_y;
	for (bool running = true; running == true;)
	{	db_y = y;	
		refresh();
		wrefresh(main_w);
		wrefresh(db_w);
		wrefresh(settings_w);
		if(in_c == 'q' | in_c == '!')	
		 	running = false;
		else if ((in_c == 'k' | in_c == 'u') & loc > 1)
		{	loc--;
			if (pane == 0)
			{
				mvwprintw(main_w,loc,1,">");	
				mvwprintw(main_w,loc_,1," ");
			}
		}
		else if  ((in_c == 'j' | in_c == 'd') & loc < loc_max)
		{	loc++;
			if (pane == 0)
			{
				mvwprintw(main_w,loc,1,">");	
				mvwprintw(main_w,loc_,1," ");
			}
		}else if (in_c == 'l')
		{	sprintf(cmd,"devour mpv --no-video $(sed -n -e %up ~/.config/trdstations)",loc);
			system(cmd);
		}else if (in_c == '\t')
			pane ^= 1;
		in_c = getch();
		loc_=loc;

		int row, col;
		getmaxyx(stdscr, row, col);

		mvwprintw(db_w,db_y++,1,"loc: %u",loc);
		mvwprintw(db_w,db_y++,1,"col: %u",col);
		mvwprintw(db_w,db_y++,1,"row: %u",row);
	}
	return 0;
}
