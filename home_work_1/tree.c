

#include <stdio.h>

char f0[][9]={"   *   \n",
					  "  ***  \n",
					 " ***** \n",
					"*******\n",
					" HHOHH \n",
					" ZZZZZ "
					};


int main(void)
{
	for(int i=0;i<6;i++){
		printf(*(f0+i));
	}

	return 0;
}

