#include <stdio.h>
#include "call.h"

int call(int res, char * msg)
{
	if (res == -1)
	{
		perror(msg);
		exit(1);
	}
	else return res;
}

