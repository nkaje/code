/*
A sequence of calls to this function split str into tokens, which are sequences of contiguous
characters separated by any of the characters that are part of delimiters.

On a first call, the function expects a C string as argument for str, whose first character 
is used as the starting location to scan for tokens. In subsequent calls, 
the function expects a null pointer and uses the position right after the end of the last token 
as the new starting location for scanning.

To determine the beginning and the end of a token, the function first scans from the starting location
 for the first character not contained in delimiters
(which becomes the beginning of the token). And then scans starting from this beginning of the token for
 the first character contained in delimiters, which becomes the end of the token.
The scan also stops if the terminating null character is found.

This end of the token is automatically replaced by a null-character, and the beginning of the token is
returned by the function.

Once the terminating null character of str is found in a call to strtok, all subsequent calls to this function
(with a null pointer as the first argument) return a null pointer.

The point where the last token was found is kept internally by the function to be used on the
next call (particular library implementations are not required to avoid data races).

*/


#include <stdio.h>
#include <string.h>


#define TRUE	1
#define FALSE	0


int check_in_ct(char c, const char *ct)
{
	int i;

	for (i=0; *(ct + i) != '\0'; i++) {
		if(*(ct + i) == c)
			return(TRUE);

	}
	return FALSE;
}


char *strtok(char *s, const char *ct)
{
	static int cur_idx = 0;
	static int orig_len;
	static char *s_cache;
	int begin = 0;
	int end = -1;

	/* bound check */
	if(cur_idx > orig_len)
		return NULL;

	if (!s) {
		s = s_cache;
		begin = cur_idx;
	} else {
		s_cache = s;
		orig_len = (int)strlen(s);
	}

	if (check_in_ct(s[cur_idx], ct)) {
		cur_idx++;
		while (check_in_ct(s[cur_idx], ct))
			cur_idx++;
	}
	begin = cur_idx;

	/* include non delimiters */
	while (!check_in_ct(s[cur_idx], ct))
			cur_idx++;

	end = cur_idx;
	*(s + end) = '\0';
	cur_idx++;

	printf("begin %d end %d cur_idx %d\n", begin, end, cur_idx);
	return (s+begin);
}


int main()
{
	char *ret = NULL;
	char input[] = "-, This a string.";
	char ct[] = " ,-.";

	ret = strtok(input, ct);

	while (ret != NULL) {
		printf("%s\n", ret);
		ret = strtok(NULL, ct);
	}

	return 0;
}
