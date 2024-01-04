/*
 * ErrorHandling.c
 *
 *  Created on: Nov 4, 2023
 *      Author: stewa
 */

#include "ErrorHandling.h"

void APPLICATION_ASSERT(bool input)
{
	if(!input)
	{
		for(;;);
	}
}


