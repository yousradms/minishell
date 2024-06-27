#include "../minishell.h"
static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}
static int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count += 1;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static void	ft_free_split(char **split_strings, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split_strings[i]);
		i++;
	}
	free(split_strings);
}

static int	word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char	*strndup1( char *s, size_t n)
{
	char	*dup;

	dup = (char *)malloc(n + 1);
	if (dup != NULL)
	{
		ft_strlcpy(dup, s, n + 1);
	}
	return (dup);
}

char	**ft_split4( char *s, char c)
{
	char	**result;
	int		i;
	int		word_count;

	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (*s == c)
			s++;
		result[i] = strndup1(s, word_len(s, c));
		if (!result[i])
		{
			ft_free_split(result, i);
			return (NULL);
		}
		s += word_len(s, c);
		i++;
	}
	result[i] = NULL;
	return (result);
}