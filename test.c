#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{	
	uint ui_;
	unsigned int uii_;
	size_t sz_;
	int in_;
	uint8_t ui8_;
	long ln_;
	long long lln_;
	float fl_;
	double db_;
	bool bo_;
	short sh_;

	printf("--SIZES--\nuint: %u\nunsigned int: %u\nsize_t: %u\nint: %u\nuint8: %u"
			"long: %u\nlonglong: %u\nfloat: %u\ndouble: %u\nbool: %u\nshort: %u"
			,sizeof(ui_),sizeof(uii_),sizeof(sz_), sizeof(in_) , sizeof(ui8_)
			,sizeof(ln_), sizeof(lln_), sizeof(fl_), sizeof(db_),sizeof(bo_),sizeof(sh_)
		  );
	return 0;
}
