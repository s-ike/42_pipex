/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 23:13:43 by sikeda            #+#    #+#             */
/*   Updated: 2022/04/30 23:28:09 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_cmd_path.h"

static char
	*add_current_middle(char *str)
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
	*add_current_both_ends(char *str)
{
	char	*tmp;

	if (*str == ':')
	{
		tmp = str;
		str = ft_strjoin(".", str);
		ft_free(&tmp);
		if (!str)
			return (NULL);
	}
	if (ft_strlen(str) > 0 && str[ft_strlen(str) - 1] == ':')
	{
		tmp = str;
		str = ft_strjoin(str, ".");
		ft_free(&tmp);
	}
	return (str);
}

static char
	*get_path_str(char **environ)
{
	char	*path_str;
	char	*tmp;
	int		i;

	i = 0;
	while (ft_strncmp(environ[i], "PATH=", ft_strlen("PATH=")))
		++i;
	path_str = ft_strdup(environ[i] + ft_strlen("PATH="));
	if (!path_str)
		return (NULL);
	path_str = add_current_both_ends(path_str);
	if (!path_str)
		return (NULL);
	while (ft_strnstr(path_str, "::", ft_strlen(path_str)))
	{
		tmp = add_current_middle(path_str);
		ft_free(&path_str);
		path_str = tmp;
		if (!path_str)
			return (NULL);
	}
	return (path_str);
}

static char
	*search_path(char **paths, char *cmd)
{
	char	*path;
	char	*cmd_path;
	int		i;

	cmd_path = ft_strjoin("/", cmd);
	if (!cmd_path)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], cmd_path);
		if (!path || access(path, F_OK) == 0)
			break ;
		ft_free(&path);
	}
	ft_free(&cmd_path);
	if (path && access(path, F_OK) != 0)
		ft_free(&path);
	return (path);
}

char
	*ft_get_cmd_path(char *cmd, char **environ)
{
	char	**paths;
	char	*path_str_from_env;
	char	*path;

	path_str_from_env = get_path_str(environ);
	if (!path_str_from_env)
		return (NULL);
	paths = ft_split(path_str_from_env, ':');
	ft_free(&path_str_from_env);
	if (!paths)
		return (NULL);
	path = search_path(paths, cmd);
	ft_free_split(&paths);
	return (path);
}
