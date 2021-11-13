#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{ char cmd[512];
	sprintf(cmd,"notify-send \"bat\" \"$(%s)\""
			,"upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep -E \"State|to\\ |time|percentage\""
		   );
	system(cmd);
}
