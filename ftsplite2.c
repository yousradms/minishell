#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"



t_command *ft_split2(t_node **head) {
    t_command *result = NULL;
    t_command *current_command = NULL;
    t_node *current_node = *head;

    while (current_node != NULL) {
        if (current_node->type == PIPE || current_command == NULL) {
            t_command *new_command = (t_command *)malloc(sizeof(t_command));
            if (!new_command) {
                while (result) {
                    t_command *temp = result;
                    result = result->next;
                    free(temp->arg);
                    free(temp);
                }
                return NULL;
            }
            new_command->arg = (char **)malloc(2 * sizeof(char *));
            if (!new_command->arg) {
                free(new_command);
                while (result) {
                    t_command *temp = result;
                    result = result->next;
                    free(temp->arg);
                    free(temp);
                }
                return NULL;
            }
            new_command->arg[0] = NULL;
            new_command->next = NULL;

            if (current_command) {
                current_command->next = new_command;
            } else {
                result = new_command;
            }
            current_command = new_command;
        }

        if (current_node->type != PIPE && current_node->type != WSPACE)
        {
            int i = 0;
            while (current_command->arg[i] != NULL) {
                i++;
            }
            current_command->arg = (char **)realloc(current_command->arg, (i + 2) * sizeof(char *));
            if (!current_command->arg) {
                while (result) {
                    t_command *temp = result;
                    result = result->next;
                    free(temp->arg);
                    free(temp);
                }
                return NULL;
            }
            current_command->arg[i] = current_node->content;
            current_command->arg[i + 1] = NULL;
        }

        current_node = current_node->next;
    }
    return result;
}
