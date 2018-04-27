#include <stdio.h>
int bitt(int num, int bit);
int main(void)
{
    int num, bit;
    puts("Please enter an integer: ");
    scanf("%d", &num);
    puts("Please enter the bit you want to check: ");
    scanf("%d", &bit);
    printf("%d\r\n", bitt(num, bit));
    return 0;
}
int bitt(int num, int bit)
{
    int mask = 1;
    mask <<= bit;
    return(num & mask);
}