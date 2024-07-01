#include "../minishell.h"

#define BUFFER_SIZE 1024

void handle_herdoc(t_node *head)
{
    t_node *temp = head;
    while(temp != NULL)
    {
        if(temp->type == 6 && temp->state == 1)
        {
            temp = temp->next;
            while(temp->type == 1 && temp->state == 1)
                temp = temp->next;
           
                char *delimiter = temp->content;
                char *line;
    int temp_fd;

    temp_fd = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (temp_fd == -1) {
        perror("Error creating temporary file");
        return;
    }

    while (1) {
        line = readline("herdoc> ");
        if (line == NULL)
            break;
        if (strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        write(temp_fd, line, strlen(line));
        write(temp_fd, "\n", 1);
        free(line);
    }
    close(temp_fd);

    temp_fd = open("temp.txt", O_RDWR, 0644);
    if (temp_fd == -1) {
        perror("Error opening temporary file for reading");
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(temp_fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytes_read);
    }
    close(temp_fd);
    unlink("temp.txt");

        }
        temp = temp->next;
    }
    //char *line;
    int temp_fd;

    temp_fd = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (temp_fd == -1) {
        perror("Error creating temporary file");
        return;
    }


}