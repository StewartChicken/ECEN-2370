/*
 * ApplicationCode.c
 *
 *  Created on: Aug 29, 2023
 *      Author: stewa
 */

#include <stdio.h>
#include "ApplicationCode.h"

void printMyNameAndFactAboutMe() {
	char name[] = "Evan\0";

	printf("My name is %s and I worked in a law firm!\n", name);
}
