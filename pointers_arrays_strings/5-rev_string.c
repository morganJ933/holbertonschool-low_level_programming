
#include "main.h"

/**
 * rev_string - Reverses a string in place
 * @s: String to reverse
 *
 * Return: Nothing
 */
void rev_string(char *s)
{
	int i;
	int j;
	char temp;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}

	j = 0;
	i--;

	while (j < i)
	{
		temp = s[j];
		s[j] = s[i];
		s[i] = temp;
		j++;
		i--;
	}
}
