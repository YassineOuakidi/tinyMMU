
#include "../inc/bitmap.h"


void bitmap_init()
{
	memset(memory , 0 , PHYSICAL_NUM_FRAMES);
}

void bitmap_clear()
{
	memset(memory , 0 , PHYSICAL_NUM_FRAMES);
}

void bitmap_get_status(size_t index)
{
	if(index>= PHYSICAL_NUM_FRAMES)
	{
		printf("-1\n");
		return;
	}
	printf("%d\n" , memory[index]);
}


void bitmap_print()
{
	size_t		i;
	
	i = 0;
	
	while(i < PHYSICAL_NUM_FRAMES)
	{
		printf("%d " , memory[i]);
		i++;
	}
	printf("\n");
}
