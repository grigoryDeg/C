#include <stdio.h>
int bit(int num);
int main(void)
{
    int number, count;

    puts("Please enter a integer:");
    while(scanf("%d", &number) == 1)
    {
        count = bit(number);
        printf("%d bits opened\r\n", count);
        puts("Please enter next integer:");
    }
    puts("Bye!");
    return 0;
}
int bit(int num)
{
    int mask = 1;
    int count = 0;
    while(num > 0)
    {
        count += num & mask;
        num >>= 1;
    }
    return count;
}