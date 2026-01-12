#include "builtins.h"

int	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_printf("pwd: error retrieving current directory\n");
		return (1);
	}
	ft_printf("%s\n", cwd);
	return (0);
}
