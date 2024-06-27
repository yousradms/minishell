#include "../minishell.h"

#define MAX_WORDS 1000
#define MAX_LENGTH 1000

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

char **ft_split3(char *str)
{
    int i = 0;
    int i2 = 0;
    int i3 = 0;
    char **tab;

    tab = malloc(sizeof(*tab) * (MAX_WORDS + 1)); 
    if (tab == NULL) {
        return NULL; 
    }

    while (is_whitespace(str[i]))
        i++;

    while (str[i]) {
        if (!is_whitespace(str[i]))
        { 
            i3 = 0;
            tab[i2] = malloc(sizeof(char) * (MAX_LENGTH + 1)); 
            if (str[i] == '\'' || str[i] == '"')
            {
                char quote_char = str[i];
                tab[i2][i3++] = quote_char;
                i++; 

                while (str[i] && str[i] != quote_char)
                {
                    tab[i2][i3++] = str[i];
                    i++;
                }

                if (str[i] == quote_char)
                    tab[i2][i3++] = quote_char;

                if (str[i] == quote_char)
                    i++; 
            }
            else
            {
                while (str[i] && !is_whitespace(str[i]))
                {
                    tab[i2][i3++] = str[i];
                    i++;
                }
            }
            tab[i2][i3] = '\0'; 
            i2++;
        }
        else
            i++;
    }
    tab[i2] = NULL; 
    return (tab);
}

