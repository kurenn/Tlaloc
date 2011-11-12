/* atoi example */
//gcc -o test `pkg-config --cflags --libs glib-2.0` test_functions.c
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

int main ()
{
    char i;
    for (i = 'a'; i < 'z'; i++) {
        printf("%c", i);
    }
    return 0;
}
