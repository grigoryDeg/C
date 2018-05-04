#include<stdio.h>
int main(void)
{
    FILE *in, *out;
    int c;


    if ( (in = fopen ("infa.txt", "r")) == NULL )
    {
        printf ("Couldn't read %s\n", "infa.txt");
        return 1;
    }

    if ( (out = fopen ("copyinfa.txt", "w")) == NULL )
    {
        printf ("Couldn't copy %s\n", "copyinfa.txt");
        return 1;
    }

    while ( (c = getc (in)) != EOF )
        putc (c-32, out);

    fclose (in);
    fclose (out);
    printf ("Success \n");

    return 0;
}
