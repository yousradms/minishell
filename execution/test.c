#include <stdio.h>
int check_n(char *s)
{
    while(*s)
    {
        if(*s == '-')
            s++;
        else
            return(0);
        if(*s != 'n')
            return(0);
        s++;
    }
    return(1);
}
//0
int main()
{
	printf("%d\n",check_n("-nnnnnnnnn"));
}
