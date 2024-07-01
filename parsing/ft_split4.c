#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

#define w_count 1000
#define L_count 1000

char **ft_split(char *str) {
    int i = 0;
    int i2 = 0;
    int i3 = 0;

    char **tab = malloc(sizeof(char *) * (w_count + 1));

    if (tab == NULL) {
        return NULL;
    }

    while (str[i]) {
        if (str[i] == '=') {
            tab[i2] = malloc(sizeof(char) * (i3 + 1));

            if (tab[i2] == NULL) {
                for (int j = 0; j < i2; j++) {
                    free(tab[j]);
                }
                free(tab);
                return NULL;
            }

            strncpy(tab[i2], str, i3);
            tab[i2][i3] = '\0';

            i2++;
            str += i3 + 1;
            i3 = 0;
            break;
        }

        i++;
        i3++;
    }

    tab[i2] = NULL;

    return tab;
}
int main(void)
{
    char *str = "$USER=ydoumas";

    int i =0;

    char **str2 = ft_split(str);

    while(str2[i])
    {
        printf("%s\n", str2[i]);
        i++;
    }
}

