#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define char_to_num(c) (c - '0')
#define num_to_char(c) ('0' + c)

char *long_addition(char *num_long, char *num_short, char *sum)
{
	int c = 0;
	int s = 0;
	int index_long = strlen(num_long) - 1;
	int index_short = strlen(num_short) - 1;

	while (index_short >= 0) {
		s = char_to_num(num_long[index_long]) + char_to_num(num_short[index_short]) + c;
		printf("%d+%d=%d\n", char_to_num(num_long[index_long]), char_to_num(num_short[index_short]), s);
		c = s/10;
		*(sum + 1 + index_long) = num_to_char(s%10);
		index_short--;
		index_long--;
	}

	while (index_long >= 0) {
		s = char_to_num(num_long[index_long]) + c;
		printf("%d\n", s);
		c = s/10;
		printf("%d+%d=%d\n", c, char_to_num(num_long[index_long]), s);
		*(sum + 1 + index_long) = num_to_char(s%10);
		index_long--;
	}

	if (c)
		*(sum) = '1';
	else
		*(sum) = ' ';
	return(sum);
}

int main()
{
	char *a = "56921343";
	char *b = "1";

	/* account for overflow */
	char *s = malloc(strlen(a) + strlen(b) + 1);

	if (strlen(a) > strlen(b))
		s = long_addition(a, b, s);
	else
		s = long_addition(b, a, s);

	printf("%s+%s=%s\n", a,b,s);
	return 0;
}
