#include "main.h"

/**
*print_char - Writes a single character to stdout
*@c: The character to print
*
*Return: 1 on success, -1 on error
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
*Return: Number of characters written, or -1 on error
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
*print_int - Writes an integer to stdout
*@n: The integer to print
*
*Return: Number of characters written, or -1 on error
*/
static int print_int(int n)
{
int count = 0;
unsigned int num;

if (n < 0)
{
if (print_char('-') == -1)
return (-1);
count++;
num = -n;
}
else
{
num = n;
}

if (num / 10)
{
int sub = print_int(num / 10);
if (sub == -1)
return (-1);
count += sub;
}

if (print_char((num % 10) + '0') == -1)
return (-1);
count++;

return (count);
}

/**
*_printf - Produces output according to a format
*@format: A character string with directives
*
*Return: Number of characters printed, or -1 on error
*/
int _printf(const char *format, ...)
{
va_list ap;
int i = 0, total = 0, wrote;

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
}
else if (format[i] == 's')
{
wrote = print_string(va_arg(ap, char *));
}
else if (format[i] == '%')
{
wrote = print_char('%');
}
else if (format[i] == 'd' || format[i] == 'i')
{
wrote = print_int(va_arg(ap, int));
}
else
{
wrote = print_char('%');
if (wrote != -1)
wrote += print_char(format[i]);
}

if (wrote == -1)
{
va_end(ap);
return (-1);
}
total += wrote;
i++;
}
}

va_end(ap);
return (total);
}
