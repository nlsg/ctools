#include <stdio.h>
#include <string>

int main(int argc, char** argv)
{	std::string cmd = "links https://wiby.me/?q=";
	for (uint i = 1; i < argc;++i)
	{	cmd += argv[i];
		cmd += "+";
	}
	system(cmd.c_str());
	return 0;
}
