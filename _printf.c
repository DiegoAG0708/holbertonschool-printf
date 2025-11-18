#include "main.h"

/**
*print_char - Writes a single character to stdout
*@c: The character to print
*
*Return: Number of characters written (1), or -1 on error
*/
static int print_char(char c)
{
if (write(1, &c, 1) == -1)
return (-1);
return (1);
}

/**
*print_string - Writes a string to stdout
*@s: The string to print
*
*Return: Number of characters written
*
*Description: If s is NULL, prints "(null)".
*/
static int print_string(const char *s)
{
int count = 0;
const char *nulls = "(null)";

if (s == NULL)
s = nulls;

while (*s)
{
if (write(1, s, 1) == -1)
return (-1);
count++;
s++;
}
return (count);
}

/**
*_printf - Produces output according to a format
*@format: A character string with zero or more directives
*
*Return: The number of characters printed
*
*Description: Handles conversion specifiers:
* c: character
* s: string
* %: percent sign
*/
int _printf(const char *format, ...)
{
va_list ap;
int i = 0, total = 0;
int wrote;

if (format == NULL)
return (-1);

va_start(ap, format);

while (format[i])

{
if (format[i] != '%')
{
wrote = print_char(format[i]);
if (wrote == -1)
{
va_end(ap);
return (-1);
}
total += wrote;
i++;
}
else
{
i++;
if (format[i] == '\0')
{
va_end(ap);
return (-1);
}

if (format[i] == 'c')
{
wrote = print_char((char)va_arg(ap, int));
if (wrote == -1)
{
va_end(ap);
return (-1);
}
total += wrote;
}
else if (format[i] == 's')
{
wrote = print_string(va_arg(ap, char *));
if (wrote == -1)
{
va_end(ap);
return (-1);
}
total += wrote;
}
else if (format[i] == '%')
{
wrote = print_char('%');
if (wrote == -1)
{
va_end(ap);
return (-1);
}
total += wrote;
}
else
{
wrote = print_char('%');
if (wrote == -1)
{
va_end(ap);
return (-1);
}
total += wrote;

wrote = print_char(format[i]);
if (wrote == -1)
{
va_end(ap);
return (-1);
}
total += wrote;
}
i++;
}
}

va_end(ap);
return (total);
}
