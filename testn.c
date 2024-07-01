#include <stdio.h>
int check_n(char *s)
{
    while(*s)
    {
        if(*s == '-')
            s++;
        else
            return(0);
        while(*s == 'n')
            s++;
    }
	if(*s != '\0')
		return(0);
    return(1);
}
//0
int main()
{
	printf("%d\n",check_n("-nnnnnnnnn"));
}