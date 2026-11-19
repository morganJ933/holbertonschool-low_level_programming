#include "function_pointers.h"

/**
 * print_name - prints a name using a function pointer
 * @name: the name to be printed
 * @f: a pointer to a function that takes a string as an argument
 *
 * Description: This function takes a string and a function pointer as
 * arguments. It calls the function pointed to by 'f' with 'name' as its
 * argument, allowing for custom printing behavior.
 */
void print_name(char *name, void (*f)(char *))
{
    
    if (name == NULL || f == NULL)
        return;

    f(name);
}
