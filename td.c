#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <nls.h>	

#define PATH_ "~/td/"
#define MAX_TABLES 20

//split this process in two functions 
//one to fetch data in arr[WND][TD]and one to draw it 
struct td_t
{	uint td_amount
		,sizes[MAX_TABLES];
	char td_a[MAX_TABLES][MAX_TABLES][256];
}td_pkg;

struct td_t * test_func(struct td_t * td_pkg)
{	printf(_b"pkg_t\n"_n"sz: %u\n",td_pkg->sizes[0]);
	td_pkg->sizes[0] = 99;
	return td_pkg;
}
char *** fetch_tables(struct td_t * td_pkg)
{	
	char buff_[256], buff [256];
	FILE * fp = popen("ls "PATH_" | grep .td","r");
	uint i = 0, i_ = 0;
	while(fgets(buff,sizeof(buff),fp) != NULL)
	{	sprintf(buff_,"cat "PATH_"%s",buff);
		FILE * fp_ = popen(buff_,"r");
		i_ = 0;
		strcpy(td_pkg->td_a[i][i_++],buff);
		while(fgets(buff,sizeof(buff),fp_) != NULL)
			strcpy(td_pkg->td_a[i][i_++],buff);
		td_pkg->td_a[i++][i_][0] = '\0';
		td_pkg->sizes[i] = i_;
		pclose(fp_);
	}
	td_pkg->td_amount = i;
	td_pkg->td_a[i][0][0] = '\0';
	pclose(fp);
	return td_pkg->td_a;
}
WINDOW ** wnd_a_init(char td_a[MAX_TABLES][MAX_TABLES][256], uint selected[2])
{					//array of tables with are arrays of str	//selected {table, item}
	WINDOW ** wnd_a = malloc((sizeof (WINDOW*))* MAX_TABLES);
	int y,x,n = 0, i_off = 0;
	getmaxyx(stdscr,y,x);
	for(int i = 0;;i++)											//iterate thru tables
	{	if (td_a[i][0][0] == '\0')
		{	wnd_a[i] = NULL;
			break;
		}
		if (((i-i_off+1)*30) >= x)								//if window has no space on screen
		{	n++;												//for y-axis
			i_off = i;
		}
		wnd_a[i] = newwin(15,29,2 + 16*n ,2 + 30*(i-i_off));
		for(uint i_ = 1; td_a[i][i_][0] != '\0' ;i_++) 
			for(uint j = 0;j <= strlen(td_a[i][i_]) - 2; j++)	//iterate thru content
			{
				if (i == selected[0] && i_ == selected[1])
				{
					wattron(wnd_a[i],A_STANDOUT);
					mvwprintw(wnd_a[i],i_,1 + j,"%c",td_a[i][i_][j]);
					wattroff(wnd_a[i],A_STANDOUT);
				}else
					mvwprintw(wnd_a[i],i_,1 + j,"%c",td_a[i][i_][j]);
			}
		box(wnd_a[i],0,0);
		wattron(wnd_a[i],A_BOLD);
		uint j = 0;
		for(; j <= strlen(td_a[i][0]) -2;j++)
			mvwprintw(wnd_a[i],0,1+j,"%c",td_a[i][0][j]);
		mvwprintw(wnd_a[i],0,1+j,"[%u]",td_pkg.sizes[i+1]-1);

		wrefresh(wnd_a[i]);		
	}
	return wnd_a;

}

char * get_cmd(WINDOW * status_bar_w,char buff[256])
{	mvwprintw(status_bar_w,0,0,":");
	curs_set(1);
	wrefresh(status_bar_w);
	for(uint i = 0;;i++)
	{	wrefresh(status_bar_w);
		int ch = getchar();
		if (ch == 13)		//enter-key
		{	buff[i] = '\0';
			break;
		}
		else if(ch == 127)//backspace-key
		{	ch = 8;
			i-=2;
			wprintw(status_bar_w,"%c",ch);
			wprintw(status_bar_w," ",ch);
		}
		else //if char is not a special char
			buff[i] = ch;
		wprintw(status_bar_w,"%c",ch);
	}
	curs_set(0);
	return &buff;
}
void wnd_debug_show(char content[16][256])
{	uint bounds[2];
	getmaxyx(stdscr,bounds[0],bounds[1]);
	WINDOW * wnd_debug = newwin(bounds[0] * 4/6,bounds[1] * 4/6,bounds[0]/6,bounds[1]/6);
	box(wnd_debug,0,0);
	wattron(wnd_debug, A_BOLD);
	mvwprintw(wnd_debug,0,1,"debug");
	wattroff(wnd_debug, A_BOLD);
	for(uint i = 0; i < 16; i++)
		mvwprintw(wnd_debug,1+i,1,content[i]);
	wrefresh(wnd_debug);
	getchar();
}
int main(int argc, char ** argv)
{	//popen throu cat and creat window in WINDOW ** set title to namue
	//
	//get win lenght and hight and adopt location accordingly
	//
	//HINTS: curs_set();
	//int row, col;
	//	getmaxyx(stdscr, row, col);
	
	char td_a[MAX_TABLES][MAX_TABLES][256];
	if (0)
	{
		system("clear");
		printf(_b"strlen:\n"_n);
		for(uint i = 0; td_a[i][0][0] != '\0';i++)
			printf("\ttd_a[%u][0]-> %s size: %u; sizeof: %u\n\r"
					,i,td_a[i][0],strlen(td_a[i]),sizeof td_a[i]);
		test_func(&td_pkg);
		printf("sz: %u\n",td_pkg.sizes[0]);
		printf("sizeof: td_a->%u, sizes->%u, td_pkg->%u\n"
				,sizeof td_pkg.td_a, sizeof td_pkg.sizes, sizeof td_pkg);
		return 0;
	}
	initscr();
	cbreak();	
	noecho();
	curs_set(0);
	
	WINDOW ** wnd_a;	//window_array
	int ch;
	uint main_w[2], selected[2] = {3,5}//selected window, selected item
		;
	for(uint i;;)
	{	getmaxyx(stdscr,main_w[0],main_w[1]);
		WINDOW ** status_bar_w = newwin(2,main_w[1],main_w[0]-2,0);
	//inout evaluation
		char buff[256], ch_hist[5];
		if		(ch == 'c' || ch == 'q')
			break;
		else if (ch == 'j' && selected[1] <= MAX_TABLES)	
			selected[1]+=1;
		else if (ch == 'k' && selected[1] > 1)
			selected[1]-=1;
		else if (ch == 'l' && selected[0] <= MAX_TABLES)
			selected[0]+=1;
		else if (ch == 'h' && selected[0] > 0)
			selected[0]-=1;
		else if (ch == ':')
		{	get_cmd(status_bar_w,buff);
			if		(strcmp(buff,"quit") == NULL) 
				break;
			else if (strcmp(buff,"db") == NULL 
				||	 strcmp(buff,"debug") == NULL) 
			{	char content[16][256] = 
				{"it's"}; 
				sprintf(content[1],"bounds: %u,%u",main_w[0],main_w[1]);
				wnd_debug_show(content);
				refresh();
			}

		}
	//inout history		
		for(uint u = 4;u != 0;)
			ch_hist[u--] = ch_hist[u];
		ch_hist[0] = ch;

		wnd_a = wnd_a_init(fetch_tables(&td_pkg),selected);

	//status bar
		wattron(status_bar_w, A_STANDOUT);
		for(uint i = 1 ;i <= main_w[1];i++)	//print white space in stand-
			wprintw(status_bar_w," ");		//out thru the hole status bar
		wattroff(status_bar_w, A_STANDOUT);

		mvwprintw(status_bar_w,1,0,
				"->%c[%u] h,w->[%u,%u] selected[%u,%u], rfrsh: %u, cmd: %s, hist: %s"
				,ch,ch,main_w[0],main_w[1],selected[0],selected[1],i++,buff,ch_hist
				);
		wrefresh(status_bar_w);
	ch = getchar();

	} //for(;;)

	free(wnd_a);
	endwin();
	return 0;

}
