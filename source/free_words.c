/*
 * PES Project Three free words source code implementation
 * Tristan Duenas
 * References:
 */

#include "free_words.h"

void free_words(uint32_t* src)
{
	if (src == NULL)
	{
		#ifdef FB_DEBUG
			PRINTF("Warning no memory allocated.\n");
		#endif
		#ifdef PC_DEBUG
			printf("Warning no memory allocated.\n");
		#endif
	}
	else
	{
		free(src);
	}
}
