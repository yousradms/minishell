/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixdelimiters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:45:33 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/24 10:03:41 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_single_quote_delimiters(char *s, int *i, int *len)
{
    int j;

    j = *len;
    while(j > *i)
    {
        s[j + 1] = s[j];
        j--;
    }
    s[*i] = ' ';
    s[*i + 1] = '\'';
    *i += 2;
    *len += 1;
    (*i)++;
    while(s[*i]!= '\'')
        (*i)++;
    j = *len;
    while(j > *i)
    {
        s[j + 1] = s[j];
        j--;
    }
    s[*i] = '\'';
    s[*i + 1] = ' ';
    *i += 2;
    *len += 1;
}

void add_double_quote_delimiters(char *s, int *i, int *len)
{
    int j;

    j = *len;
    while(j > *i)
    {
        s[j + 1] = s[j];
        j--;
    }
    s[*i] = ' ';
    s[*i + 1] = '\"';
    *i += 2;
    *len += 1;
    (*i)++;
    while(s[*i]!= '\"')
        (*i)++;
    j = *len;
    while(j > *i)
    {
        s[j + 1] = s[j];
        j--;
    }
    s[*i] = '\"';
    s[*i + 1] = ' ';
    *i += 2;
    *len += 1;
}

void add_one_delimiters(char *s, int *i, int *len, char c)
{
    int j;

    j = *len;
    while(j > *i)
    {
        s[j + 2] = s[j];
        j--;
    }
    s[*i] = ' ';
    s[*i + 1] = c;
    s[*i + 2] = ' ';
    *i += 3;
    *len += 2;
}

void add_one_delimiters_before(char *s, int *i, int *len, char c)
{
    int j;

    j = *len;
    while(j > *i)
    {
        s[j + 1] = s[j];
        j--;
    }
    s[*i] = ' ';
    s[*i + 1] = c;
    *i += 2;
    *len += 1;
}

void add_double_delimiters(char *s, int *i, int *len,char c1,char c2)
{
    int j;

    j = *len;
    while(j > *i)
    {
        s[j + 2] = s[j];
        j--;
    }
    s[*i] = ' ';
    s[*i + 1] = c1;
    s[*i + 2] = c2;
    s[*i + 3] = ' ';
    *i += 4;
    *len += 2;
}
int double_dquote_before(char *s,int i)
{
    int len = 0;
    while(len < i)
    {
        if(s[len] == '\"')
            return(1);
        len++;
    }
    return(0);
}

int simple_squote_after(char *s,int i)
{
    int len = ft_strlen(s);
    i++;
    while(i < len)
    {
        if(s[i] == '\'')
            return(1);
        i++;
    }
    return(0);
}
//i = 5
//6
//len = 11
char *add_delimiter(char *s)
{
    int i;
    int len;

    i = 0;
    len = strlen(s);
    while (i < len)
    {
        if(s[i] == '\'')
        {
            if(!double_dquote_before(s,i) && !simple_squote_after(s,i))
            {
                add_one_delimiters(s, &i, &len, s[i]);
            }
            else
            {
                add_single_quote_delimiters(s, &i, &len);
            }
        }
        else if(s[i] == '\"')
            add_double_quote_delimiters(s, &i, &len);
        else if (s[i] == '|') 
            add_one_delimiters(s, &i, &len, s[i]);
        else if (s[i] == '>' && i + 1 < len && s[i + 1] == '>')
            add_double_delimiters(s,&i,&len,s[i],s[i + 1]);
        else if (s[i] == '<' && i + 1 < len && s[i + 1] == '<')
            add_double_delimiters(s, &i, &len,s[i],s[i+1]);
        else if (s[i] == '<' || s[i] == '>') 
            add_one_delimiters(s,&i,&len,s[i]);
        else if (s[i] == '$'  && s[i + 1] == '?')
            add_double_delimiters(s,&i,&len,s[i],s[i+1]);
        else if (s[i] == '$')
            add_one_delimiters_before(s,&i,&len,s[i]);
        else
            i++;
    }
    return(s);
}