/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:02:03 by sikeda            #+#    #+#             */
/*   Updated: 2022/04/30 22:27:33 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execute.h"

static char
	*add_current(char *str)
{
	char	*ptr;
	char	*new_path;

	ptr = ft_strnstr(str, "::", ft_strlen(str));
	new_path = (char *)ft_calloc(ft_strlen(str) + 2, sizeof(char));
	if (!new_path)
		return (NULL);
	ft_memcpy(new_path, str, ptr - str);
	ft_strcat(new_path, ":.:");
	ft_strcat(new_path, ptr + 2);
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
		return (NULL);
	path_str_from_env = get_path_str(environ);
	if (!path_str_from_env)
	{
		ft_free(&cmd_path);
		return (NULL);
	}
	paths = ft_split(path_str_from_env, ':');
	ft_free(&path_str_from_env);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], cmd_path);
		if (!path || access(path, F_OK) == 0)
			break ;
		ft_free(&path);
	}
	ft_free(&cmd_path);
	ft_free_split(&paths);
	if (path && access(path, F_OK) != 0)
		ft_free(&path);
	return (path);
}

void
	ft_execute(char *cmd_str, char **environ)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(cmd_str, ' ');
	cmd_path = NULL;
	if (cmd)
		cmd_path = get_path(cmd[0], environ);
	if (!cmd_path)
	{
		if (cmd)
			ft_free_split(&cmd);
		ft_puterror_and_exit_failure(ft_putperror, "execute");
	}
	execve(cmd_path, cmd, environ);
	ft_free(&cmd_path);
	ft_free_split(&cmd);
	ft_puterror_and_exit_failure(ft_putperror, cmd_str);
}
