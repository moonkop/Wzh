#include "string.h"
int strlen(char * str)
{
	int i = 0;
	while (*(str++))
		i++;
	return i;
}
void strcpy(char* dest, char * source)
{
	while (*dest++ = *source++);
}

void strcat(char* str1, char * str2)
{
	while (*(str1++));
	str1--;
	while (*(str1++) = *(str2++));
	str1 = 0;
}
