#include "revert_string.h"
#include <string.h>

void RevertString(char *str)
{
	int first = 0;
	int last = strlen(str) - 1;
	char temp;

	while (first < last) {

			temp = str[first];
			str[first] = str[last];
			str[last] = temp;
		
			first++;
			last--;
	}
}

