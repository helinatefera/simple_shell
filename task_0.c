/**
 * print_string - prints a string followed by a new line
 * @str: string to print
 *
 * Return: void
 */
void print_string(char *str)
{
    if (str != NULL)
    {
        while (*str)
        {
            putchar(*str);
            str++;
        }
        putchar('\n');
    }
}