#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **ft_split3(char *str) {
    char **tab = NULL;
    int i = 0, j = 0, k = 0, count = 0;
    int in_quote = 0;

    // Count the number of words
    while (str[i]) {
        if ((str[i] == ' ' || str[i] == '\t') && !in_quote) {
            count++;
        } else if (str[i] == '\'' || str[i] == '\"') {
            in_quote = !in_quote;
        }
        i++;
    }

    // Allocate memory for the result array
    tab = (char **)malloc(sizeof(char *) * (count + 2));
    if (!tab) {
        return NULL;
    }

    // Split the string
    i = 0, in_quote = 0;
    while (str[i]) {
        if ((str[i] == ' ' || str[i] == '\t') && !in_quote) {
            tab[j++] = malloc(sizeof(char) * (k + 1));
            strncpy(tab[j - 1], &str[i - k], k);
            tab[j - 1][k] = '\0';
            k = 0;
        } else if (str[i] == '\'' || str[i] == '\"') {
            in_quote = !in_quote;
            k++;
        } else {
            k++;
        }
        i++;
    }

    // Handle the last word
    if (k > 0) {
        tab[j] = malloc(sizeof(char) * (k + 1));
        strncpy(tab[j], &str[i - k], k);
        tab[j][k] = '\0';
        j++;
    }

    // Terminate the array
    tab[j] = NULL;

    return tab;
}



int main(int ac, char **av) {
    char *line = "ls-l";
    char **result = ft_split3(line);
    int i = 0;
    while (result[i]) {
        printf("%s\n", result[i]);
        free(result[i]);
        i++;
    }
    free(result);
    return (0);
}