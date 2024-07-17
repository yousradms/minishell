
void execute_builtin(t_command **command)
{
    if (strcmp((*command)->arg[0], "cd") == 0)
    {
        char *target_dir = NULL;

        if ((*command)->arg[1] != NULL)
        {
            if (strcmp((*command)->arg[1], "~") == 0)
            {
                target_dir = getenv("HOME");
                if (target_dir == NULL)
                {
                    fprintf(stderr, "cd: HOME not set\n");
                    return;
                }
            }
            else if (strcmp((*command)->arg[1], "-") == 0)
            {
                target_dir = getenv("OLDPWD");
                if (target_dir == NULL)
                {
                    fprintf(stderr, "cd: OLDPWD not set\n");
                    return;
                }
            }
            else
            {
                target_dir = (*command)->arg[1];
            }
        }
        else
        {
            target_dir = getenv("HOME");
            if (target_dir == NULL)
            {
                fprintf(stderr, "cd: HOME not set\n");
                return;
            }
        }

        // Save the current directory as OLDPWD
        char current_dir[1024];
        if (getcwd(current_dir, sizeof(current_dir)) == NULL)
        {
            perror("getcwd");
            return;
        }

        // Change to the target directory
        if (chdir(target_dir) == -1)
        {
            perror("cd");
            return;
        }

        // Update OLDPWD and PWD environment variables
        if (setenv("OLDPWD", current_dir, 1) == -1)
        {
            perror("setenv");
            return;
        }

        if (getcwd(current_dir, sizeof(current_dir)) == NULL)
        {
            perror("getcwd");
            return;
        }

        if (setenv("PWD", current_dir, 1) == -1)
        {
            perror("setenv");
        }
    }
    else
    {
        fprintf(stderr, "Unknown built-in command\n");
    }
}