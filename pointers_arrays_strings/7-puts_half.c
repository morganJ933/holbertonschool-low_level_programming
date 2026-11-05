
#include "main.h"

/**
 * puts_half - Prints the second half of a string
 * @str: String to print
 *
 * Return: Nothing
 */
void puts_half(char *str)
{
	int length;
	int i;

	length = 0;

	while (str[length] != '\0')
	{
		length++;
	}

	i = length / 2;

	if (length % 2 != 0)
	{
		i++;
	}

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}

	_putchar('\n');
}
