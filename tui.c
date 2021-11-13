#include <ncurses.h>
#include <stdio.h>
#include <iodef.h>

#define loc_max 4

int rget()
{	refresh();
	return getch();
}	
int main(int argc, char** argv)
{	int x,y,in_c = 0;
	size_t loc = 1,loc_;

	initscr();
	//start_ncurses(true,true);
	cbreak();
	noecho();
	curs_set(0);

	WINDOW * main_w = newwin(15,20,5,2);
	WINDOW * db_w   = newwin(15,20,5,22);
	  short db_y = 0, db_x = 1;

	char * opt1 = "option1"
		,* opt2 = "option2"
		,* opt3 = "option3"
		,* opt4 = "option4"
		;
		 
	printw(
		"   _         _"
		"\n  | |_ _   _(_)"
		"\n  | __| | | | |"
		"\n  | |_| |_| | |"
		"\n   \\__|\\__,_|_|"
	);

	box(main_w, 0,0);
	box(db_w, 0,0);
	mvwprintw(main_w,1,1," opt1");
	mvwprintw(main_w,2,1," opt2");
	mvwprintw(main_w,3,1," opt3");
	mvwprintw(main_w,4,1," opt4");
	
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

	mvwprintw(db_w,db_y++,1,"<debug>");
		y = db_y;
	for (bool running = true; running == true;)
	{	db_y = y;	
		refresh();
		wrefresh(main_w);
		wrefresh(db_w);
		in_c = getch();
		if(in_c == 'q' | in_c == '!')	
		{	running = false;
			mvprintw(0,20,"quiting!");
		}else if ((in_c == 'k' | in_c == 'u') & loc > 1)
		{	loc--;
			mvwprintw(main_w,loc,1,">");	
			mvwprintw(main_w,loc_,1," ");
		}
		else if  ((in_c == 'j' | in_c == 'd') & loc < loc_max)
		{	loc++;
			mvwprintw(main_w,loc,1,">");	
			mvwprintw(main_w,loc_,1," ");
		}
			
		loc_=loc;

		int row, col;
		getmaxyx(stdscr, row, col);

		mvwprintw(db_w,db_y++,1,"loc: %u",loc);
		mvwprintw(db_w,db_y++,1,"col: %u",col);
		mvwprintw(db_w,db_y++,1,"row: %u",row);
	}
	return 0;
}
