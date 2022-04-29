#include "ft_execute.h"

static char
	*add_current(char *str)
{
	char	*ptr;
	char	*cpy;
	char	*new_path;
	size_t	i;

	ptr = ft_strnstr(str, "::", ft_strlen(str));
	cpy = str;
	new_path = (char *)malloc(ft_strlen(str) + 2 * sizeof(char));
	if (!new_path)
		return (NULL);
	i = 0;
	while (cpy != ptr)
		new_path[i++] = *cpy++;
	new_path[i++] = ':';
	new_path[i++] = '.';
	cpy++;
	new_path[i++] = *cpy++;
	while (*cpy)
		new_path[i++] = *cpy++;
	new_path[i] = '\0';
	return (new_path);
}

static char
	*get_path_str(char **environ)
{
	char			*path_str;
	char			*tmp;
	int				i;
	const char		*PATH = "PATH";
	const size_t	PATH_LEN = ft_strlen(PATH);

	i = 0;
	while (ft_strncmp(environ[i], PATH, PATH_LEN))
		++i;
	path_str = ft_strdup(environ[i] + PATH_LEN + 1);
	if (!path_str)
		return (NULL);
	if (*path_str == ':')
	{
		tmp = path_str;
		path_str = ft_strjoin(".", path_str);
		ft_free(&tmp);
	}
	if (ft_strlen(path_str) > 0 && path_str[ft_strlen(path_str) - 1] == ':')
	{
		tmp = path_str;
		path_str = ft_strjoin(path_str, ".");
		ft_free(&tmp);
	}
	while (ft_strnstr(path_str, "::", ft_strlen(path_str)))
	{
		tmp = add_current(path_str);
		ft_free(&path_str);
		path_str = tmp;
	}
	return (path_str);
}

static char
	*get_path(char *cmd, char **environ)
{
	char	**paths;
	char	*cmd_path;
	char	*path_str_from_env;
	char	*path;
	int		i;

	cmd_path = ft_strjoin("/", cmd);
	if (!cmd_path)
		return NULL;
	path_str_from_env = get_path_str(environ);
	paths = ft_split(path_str_from_env, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], cmd_path);
		if (!path)
			break ;
		if (access(path, F_OK) == 0)
			break ;
	}
	ft_free(&cmd_path);
	ft_free_split(&paths);
	if (access(path, F_OK) != 0)
		ft_free(&path);
	return (path);
}

void
	ft_execute(char *cmd_str, char **environ)
{
	char	*av[2];
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(cmd_str, ' ');
	if (cmd)
		cmd_path = get_path(cmd[0], environ);
	else
		ft_puterror_and_exit_failure(ft_putperror, "execute");
	av[0] = cmd_str;
	av[1] = NULL;
	execve(cmd_path, av, environ);
	ft_puterror_and_exit_failure(ft_putperror, cmd_str);
}
