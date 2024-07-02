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
    char qouat = 0;

    tab = malloc(sizeof(*tab) * (MAX_WORDS + 1));
    if (tab == NULL) {
        return NULL; 
    }

    while (is_whitespace(str[i]))
        i++;

    while (str[i]) {
        if (!is_whitespace(str[i]))
        {
            tab[i2] = malloc(sizeof(char) * (MAX_LENGTH + 1));
            // if (!qouat && (str[i] == '\'' || str[i] == '"'))
            //     qouat = str[i];
            // else if (qouat && str[i] == qouat)
            //     qouat = 0;
            i3 = 0;
            while (str[i] && (!is_whitespace(str[i]) || qouat))
            {
                if (!qouat && (str[i] == '\'' || str[i] == '"'))
                    qouat = str[i];
                else if (qouat && str[i] == qouat)
                    qouat = 0;
                tab[i2][i3++] = str[i];
                i++;
            }
            tab[i2][i3] = '\0'; 
            i2++;
            // if (str[i] == '\'' || str[i] == '"')
            // {
            //     //printf("start %c\n", str[i]);
            //     char quote_char = str[i];
            //     tab[i2][i3++] = quote_char;
            //     i++; 
            //     while (str[i] && str[i] != quote_char)
            //     {
            //         tab[i2][i3++] = str[i];
            //         i++;
            //     }

            //     if (str[i] == quote_char)
            //         tab[i2][i3++] = quote_char;
            //     //printf("end %c\n", str[i]);
            //     if (str[i] == quote_char)
            //         i++; 
            }
            else
            {
                // while (str[i] && (!is_whitespace(str[i]) || qouat))
                // {
                //     if (!qouat && (str[i] == '\'' || str[i] == '"'))
                //         qouat = str[i];
                //     else if (qouat && str[i] == qouat)
                //         qouat = 0;
                //     tab[i2][i3++] = str[i];
                //     i++;
                // }
                i++;
            }
            // tab[i2][i3] = '\0'; 
            // i2++;
        
        // else
        //     i++;
    }
    tab[i2] = NULL; 
    return (tab);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h> 
// int is_whitespace(char c) {
//     return (c == ' ' || c == '\t' || c == '\n');
// }

// char **ft_split3(char *str) {
//     int i = 0;
//     int i2 = 0;
//     int i3 = 0;
//     char **tab;
//     bool inside_quotes = false;
//     char quote_char = '\0';

//     tab = malloc(sizeof(*tab) * (MAX_WORDS + 1));
//     if (tab == NULL) {
//         return NULL;
//     }

//     while (is_whitespace(str[i]))
//         i++;

//     while (str[i]) {
//         if (!is_whitespace(str[i])) {
//             i3 = 0;
//             tab[i2] = malloc(sizeof(char) * (MAX_LENGTH + 1));
//             if (str[i] == '\'' || str[i] == '"') {
//                 quote_char = str[i];
//                 tab[i2][i3++] = ' '; // Add space before opening quote
//                 tab[i2][i3++] = quote_char;
//                 i++;
//                 inside_quotes = true;
//                 while (str[i] && (str[i] != quote_char || (inside_quotes && str[i] == quote_char))) {
//                     tab[i2][i3++] = str[i];
//                     if (str[i] == quote_char) {
//                         inside_quotes = !inside_quotes; // Toggle inside/outside quotes
//                     }
//                     i++;
//                 }
//                 if (str[i] == quote_char) {
//                     tab[i2][i3++] = quote_char;
//                 }
//                 tab[i2][i3++] = ' '; // Add space after closing quote
//             } else {
//                 if (str[i] == '"' && str[i + 1] == '"') {
//                     // Handle pairs of double quotes "" as a single unit
//                     tab[i2][i3++] = ' '; // Add space before opening quotes
//                     tab[i2][i3++] = '"';
//                     tab[i2][i3++] = '"';
//                     tab[i2][i3++] = ' '; // Add space after closing quotes
//                     i += 2;
//                 } else {
//                     while (str[i] && (!is_whitespace(str[i]) || inside_quotes)) {
//                         if (str[i] == '\'' || str[i] == '"') {
//                             quote_char = str[i];
//                             inside_quotes = true;
//                         }
//                         tab[i2][i3++] = str[i];
//                         i++;
//                     }
//                 }
//             }
//             tab[i2][i3] = '\0';
//             i2++;
//         } else {
//             i++;
//         }
//     }
//     tab[i2] = NULL;
//     return tab;
// }