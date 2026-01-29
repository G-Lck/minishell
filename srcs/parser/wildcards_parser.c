#include "minishell.h"

int	pattern_checker(char *ref, char *pat, int n, int m)
{
	int	index;

	if (m == 0)
		return (n == 0);

	index = 0;
	if (n == 0)
	{
		while (index < m)
		{
			if (pat[index] != '*')
				return (0);
			index++;
		}
		return (1);
	}
	if (ref[n - 1] == pat[m - 1])
		return pattern_checker(ref, pat, n - 1, m - 1);
	if (pat[m - 1] == '*')
		return (pattern_checker(ref, pat, n, m - 1)
			|| pattern_checker(ref, pat, n - 1, m));
	return (0);
}

char **wildcards_parser(char *pattern, t_minishell *minishell)
{
	char	**results;
	DIR		*dir = opendir(minishell->current_dir);

	struct dirent	*dent;
	dent = readdir(dir);
	while (dent != NULL)
	{
		if (dent->d_name[0] != '.')
		{
			if (pattern_checker(dent->d_name, pattern, ft_strlen(dent->d_name), ft_strlen(pattern)))
				ft_printf("[MATCH!] : %s\n", dent->d_name);
		}
		dent = readdir(dir);
	}
	closedir(dir);
	return (results);
}
