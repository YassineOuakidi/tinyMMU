
#include "../inc/bitmap.h"


int frame_alloc()
{
	size_t 		i;
	
	i = 0;
	while( i < PHYSICAL_NUM_FRAMES)
	{
		if(memory[i]==0)
		{
			memory[i] = 1;
			return i;
		}
		i++;
	}
	return -1;
}

int frame_free(size_t index)
{
	if(index>=PHYSICAL_MEMORY_SIZE)
		return -1;
	memory[index] = 0;
	return 0;
}
