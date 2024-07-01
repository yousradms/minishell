/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:57:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/30 15:19:13 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_error(t_node **head)
{
    (void)head;
    printf("Error\n");
    return (1);
}

// void parsing(t_node **head)
// {

//     t_node *temp = *head;
//     t_node *last = ft_lstlast(*head);
//     if(temp->type == 2)
//     {
//         if (temp->state == 1 )
//         {
//             ft_error(head);
//             return;
//         }
//         else
//             return;
//     }
//     if (last->type == 2 || last->type == 3 || last->type == 4 || last->type == 5 || last->type == 6)
//     {
//         if(last->state == 1)
//         {
//             ft_error(head);
//             return ;
//         }
//         else
//             return ;
//     }   
//     while(temp != NULL)
//     {
//         // if(temp->type == 6 && temp->state == 1)
//         // {
//         //     if(temp->next)
//         //         handle_herddoc(temp);
//         // }
//         if((temp->type == 3 || temp->type == 4 || temp->type == 5 || temp->type == 6) && temp->next->type != 9)
//         {
//             if(temp->state == 1)
//             {
//                 ft_error(head);
//                 return;
//             }

//         }   
//         if(temp->type == 2 && temp->next->type == 2)
//         {
//             if(temp->state == 1)
//             {
//                 ft_error(head);
//                 return;
//             }
           
//         }   
//         temp = temp->next;
//     }  
// }
static void	ft_handl_error(char *s1, char *s2, char *s3)
{

	char	*str;

	//g_tools.status_sign = status;
	str = ft_strjoin(s1, ft_strjoin(s2, s3));
	//ft_putendl_fd(str, 2);
    printf("%s",str);
}
// static int	error_pipe(t_node *token)
// {

// 	int	last_pipe;

// 	if (token->type == 2)
//     {
//         //exit(0);
// 		//return (ft_handl_error(NAME, "", ERR_PIPE), -1);
//         printf("error\n");
//         return(-1);
//     }
// 	while (token)
// 	{
// 		if (token->type == 2 && token->next != NULL)
// 		{
// 			token = token->next;
// 			if (token->type == 1 && token->next != NULL)
// 				token = token->next;
// 			if (token->type == 2)
// 				return (ft_handl_error(NAME, "", ERR_PIPE), -1);
// 		}
// 		last_pipe = token->type;
// 		token = token->next;
// 		if (!token)
// 		{
// 			if (last_pipe == 2)
// 				return (ft_handl_error(NAME, "", ERR_PIPE), -1);
// 		}
// 	}
// 	return (1);
// }
static int	error_pipe(t_node *token)
{
    int	last_pipe;

    if (token && token->type == 2)
    {
        printf("error\n");
        return (-1);
    }

    while (token)
    {
        if (token->type == 2 && token->next != NULL)
        {
            token = token->next;
            while (token->type == 1 && token->next != NULL)
                token = token->next;
            if (token->type == 2)
                return (ft_handl_error(NAME, "", ERR_PIPE), -1);
        }
        last_pipe = token->type;
        token = token->next; // Move to the next token
        if (!token)
        {
            if (last_pipe == 2)
                return (ft_handl_error(NAME, "", ERR_PIPE), -1);
        }
    }

        

    return (1);
}

static int	error_red(t_node *token)
{
	while (token)
	{
		if ((token->type == 3 || token->type == 4 || token->type == 5 || token->type == 6) && token->next == NULL)
			return (ft_handl_error(NAME, ERR_FILE, token->content), -1);
		if ((token->type == 3 || token->type == 4 || token->type == 5|| token->type == 6) && token->next != NULL)
		{
			token = token->next;
			while (token->type == 1 && token->next != NULL)
				token = token->next;
			if (token->type != 9 )//&& token->type != SIGN && token->type != EXIT_STATUS)
				return (ft_handl_error(NAME, ERR_FILE, token->content), -1);
		}
		token = token->next;
	}
	return (1);
}
int parsing(t_node *head)
{
    
    if(error_pipe(head) == -1)
        return(-1);
    if(error_red(head) == -1)
        return(-1);
    return(1);
}