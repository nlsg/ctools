#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <genutils.h>

int main(int argc, char** argv)
{	int return_code = 0;
	bool logging = 1;
	std::string
	   path = (std::string)getenv("HOME") + "/.bat.log"
	  ,options_s
	  ,bat_info 
	   = gul::exec("upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep -E \"State|to\\ |time|percentage\"")
	  ,log 
	   = gul::exec("date")
	   + bat_info
       + "------------------------------------------------\n\n"
    ;
	std::ofstream fs_(path, std::ios::app);
	fs_.close();
	if (argc > 1)
	{	options_s = argv[1];
		if (!(argv[1][0] == '-' || argv[1][0] == '+'))
		{	fprintf(stderr, "wrong synopsys!\n");	
			return_code = 1;
			options_s = "h";
		}
    	if (options_s.find("+l") != std::string::npos)
	    {	std::ofstream fs(path, std::ios::app);
	    	fs << "LOG_ON\n";
	    	fs.close();
    	}
    	if (options_s.find("-l") != std::string::npos)
    	{	std::ofstream fs(path, std::ios::app);
    		fs << "LOG_OFF\n";
    		fs.close();
    	}
		if (!(options_s.find("-h") == std::string::npos))
			printf(	 "bat, used to fetch and log battery info"
					 "\nlog stored stored in ~/.bat.log"
			IO_BOLD	 "\nSYNOPSYS:" 
			IO_RESET "\n\t bat [options]" 
			IO_BOLD  "\nOPTIONS:"
        	IO_RESET "\n\t-h 	 -> help"
        			 "\n\t-f 	 -> full"
        			 "\n\t-d 	 -> dont-log"
        			 "\n\t+l     -> switch logging permanently on <default>"
        			 "\n\t-l     -> switch logging permanently off"
        		 	 "\n\t-s     -> show-history"
        		 	 "\n\t-c 	 -> clear-history"
			IO_BOLD  "\nDEPENDENCIES:"
			IO_RESET "\n\t-upower"
			"\n");
    	if ((gul::lastLine(path.c_str()).find("LOG_OFF") != std::string::npos)
    	 || (options_s.find("-d") != std::string::npos))
    	{	logging = 0;
			printf(IO_BOLD "log: " IO_RESET " off\n");
    	}
    	else
		{	printf(IO_BOLD "log: " IO_RESET " on\n");
		}
		if (options_s.find("-f") != std::string::npos)
			bat_info = gul::exec("upower -i /org/freedesktop/UPower/devices/battery_BAT0");
    	if (options_s.find("-c") != std::string::npos)
    	{	system(((std::string)"rm " + path).c_str());
			printf("'~/.bat.log' cleared!");
			return 0;
    	}	
    	if (options_s.find("-s") != std::string::npos)
    	    {	if (argc == 2)
				{	system(((std::string)"cat " + path).c_str());
    				return 0;
				}
				else if (argc == 3)
				{	int input_ = atoi(argv[2]);
					if (!input_)
					{	fprintf(stderr,"not a nr\n");
						return -1;
					}
					std::string cmd_ 
						= (std::string)"tail -" 
						+ std::to_string(input_ * 5) 
						+ " " 
						+ (std::string)path
						;
					printf(cmd_.c_str());
					system(cmd_.c_str());
				}
			}	
	}
	if(logging)
	{   std::ofstream fs(path, std::ios::app);
   		fs << log;
   		fs.close();
	}
	printf(bat_info.c_str());
	return return_code;
}

/*
notes for file handling:

mode a+ => read from beginning(r) or append(w)

*/
