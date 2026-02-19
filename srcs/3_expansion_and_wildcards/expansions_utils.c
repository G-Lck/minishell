#include "minishell.h"

char	*string_cleaner(char *string)
{
	int		index;
	int		index_2;
	int		in_dquote;
	int		in_quote;
	char	*cleaned_string;

	index = 0;
	index_2 = 0;
	in_dquote = 0;
	in_quote = 0;
	cleaned_string = ft_calloc(sizeof(char), ft_strlen(string) + 1);
	if (!cleaned_string)
		return (0);
	while (string[index])
	{
		if (string[index] == '"' && in_quote == 0)
		{
			in_dquote = !in_dquote;
			index ++;
		}
		else if (string[index] == '\'' && in_dquote == 0)
		{
			in_quote = !in_quote;
			index ++;
		}
		else
			cleaned_string[index_2 ++] = string[index ++];
	}
	free(string);
	return (cleaned_string);
}

int	check_wspaces(char *str)
{
	int	index;

	index = 0;
	while(str[index])
	{
		if ((str[index] >= 9 && str[index] <= 13) || str[index] == 32)
			return (1);
		index ++;
	}
	return (0);
}