#include <stdio.h>
#include <string.h>

/*
*	Test if a given string can be formed from
*	a given set of characters.
*	Return True/1 when possible, False/0: otherwise
*	example: 
*		String: "treesandplants"
*		Set of Characters: "eetrsstdalasnspn"
*		Returns True
*/

#define TRUE 1
#define FALSE 0

unsigned int test_formation(char *string, char *set)
{
	unsigned lookup[256] = {0};
	unsigned flag = TRUE;
	unsigned index;

	for (index=0; index<strlen(set); index++) {
		lookup[(unsigned)set[index]]++;
	}

	for(index=0; index<strlen(string); index++) {
		if (lookup[(unsigned)string[index]] > 0) {
			lookup[(unsigned)string[index]]--;
		} else {
			flag = FALSE;
			break;
		}
	}

	return flag;
}


int main()
{
	char *string = "treesandplants";
	char *set = "eetrsstdalasnsp";


	if (test_formation(string, set))
		printf("%s can be formed from %s\n", string, set);
	else
		printf("%s can not be formed from %s\n", string, set);

	return 0;
}
