#include <libc.h>
#include <stdlib.h>
#include <string.h>

// #define w_count 1000
// #define L_count 1000

// char    **ft_split(char *str)
// {
//     int i = 0;
//     int i2 = 0;
//     int i3 = 0;
//     int found_equal = 0;
//     char **tab;

//     tab = malloc(sizeof(** tab) * w_count);
//     while (str[i])
//     {
//         if (str[i] == '=' && !found_equal)
//         {
//             found_equal = 1;
//             i++;
//         }
//         else if (str[i] > 32)
//         {
//             i3 = 0;
//             tab[i2] = malloc(sizeof(char) * L_count);
//             while (str[i] > 32 && str[i] != '=')
//             {
//                 tab[i2][i3] = str[i];
//                 i++;
//                 i3++;
//             }
//             tab[i2][i3] = '\0';
//             i2++;
//         }
//         else
//             i++;
//     }
//     tab[i2] = 0;
//     return (tab);
// }
//s7i7a
// #include <stdlib.h>
// #include <stdio.h>

// char **ft_split(char *str)
// {
//     int i = 0;
//     char **tab;

//     tab = malloc(sizeof(char *) * 2); // On alloue de l'espace pour deux pointeurs de chaînes
//     if (!tab)
//         return NULL;

//     // Recherche du premier '='
//     while (str[i] && str[i] != '=')
//         i++;

//     if (str[i] == '=')
//     {
//         // Allouer de la mémoire pour la première partie (avant le '=')
//         tab[0] = malloc(sizeof(char) * (i + 1));
//         if (!tab[0])
//         {
//             free(tab);
//             return NULL;
//         }

//         // Copier la première partie dans tab[0]
//         for (int j = 0; j < i; j++)
//             tab[0][j] = str[j];
//         tab[0][i] = '\0'; // Terminer la chaîne avec '\0'

//         // Trouver le début de la deuxième partie (après le '=')
//         i++;
//         while (str[i] && str[i] == ' ')
//             i++; // Ignorer les espaces après le '='

//         // Allouer de la mémoire pour la deuxième partie
//         tab[1] = malloc(sizeof(char) * (strlen(str) - i + 1));
//         if (!tab[1])
//         {
//             free(tab[0]); // Libérer la première partie déjà allouée
//             free(tab);    // Libérer tab
//             return NULL;
//         }

//         // Copier la deuxième partie dans tab[1]
//         int k = 0;
//         while (str[i])
//         {
//             tab[1][k++] = str[i++];
//         }
//         tab[1][k] = '\0'; // Terminer la chaîne avec '\0'
//     }
//     else
//     {
//         // Si aucun '=' n'est trouvé, libérer tab et retourner NULL
//         free(tab);
//         return NULL;
//     }

//     return tab;
// }

// int main(void)
// {
//     char *str = "$USER = ydoumas=kjjjkk    =ojkjhhpjd=tyuiopddj";

//     char **str2 = ft_split(str);

//     if (!str2)
//     {
//         printf("Memory allocation failed or no '=' found.\n");
//         return 1;
//     }

//     // Afficher les deux parties séparées par le premier '='
//     printf("First part: '%s'\n", str2[0]);
//     printf("Second part: '%s'\n", str2[1]);

//     // Libérer la mémoire allouée
//     free(str2[0]);
//     free(str2[1]);
//     free(str2);

//     return 0;
// }
#include <stdlib.h>
#include <stdio.h>

char **ft_split(char *str)
{
    int i = 0;
    char **tab;

    tab = malloc(sizeof(char *) * 2); // On alloue de l'espace pour deux pointeurs de chaînes
    if (!tab)
        return NULL;

    // kanqelbo eala le premier '='
    while (str[i] && str[i] != '=')
        i++;

    if (str[i] == '=')
    {
        // kan allouer la mémoire pour la première partie (avant le '=')
        tab[0] = malloc(sizeof(char) * (i + 1));
        if (!tab[0])
        {
            free(tab);
            return NULL;
        }

        // kan copiiw la première partie dans tab[0], en excluant les espaces à la fin
        int j;
        for (j = 0; j < i && str[j] != ' '; j++)
            tab[0][j] = str[j];
        tab[0][j] = '\0'; 

        // Trouver le début de la deuxième partie (après le '=')
        i++;
        while (str[i] && str[i] == ' ')
            i++; // Ignorer les espaces mn baed '='

        // kan allouer la deuxieme partie
        tab[1] = malloc(sizeof(char) * (strlen(str) - i + 1));
        if (!tab[1])
        {
            free(tab[0]); 
            free(tab);    
            return NULL;
        }

        // Copier la deuxième partie dans tab[1]
        int k = 0;
        while (str[i])
        {
            tab[1][k++] = str[i++];
        }
        tab[1][k] = '\0'; 
    }
    else
    {
        
        free(tab);
        return NULL;
    }

    return tab;
}

int main(void)
{
    char *str = "$PWD = ydoumas = jfjfjfkdk=rifkdd";

    char **str2 = ft_split(str);

    if (!str2)
    {
        printf("Memory allocation failed or no '=' found.\n");
        return 1;
    }

    // Afficher les deux parties séparées par le premier '='
    printf("First part:'%s'\n", str2[0]);
    printf("Second part: '%s'\n", str2[1]);

    // Libérer la mémoire allouée
    free(str2[0]);
    free(str2[1]);
    free(str2);

    return 0;
}






