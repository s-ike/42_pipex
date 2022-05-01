/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:02:03 by sikeda            #+#    #+#             */
/*   Updated: 2022/05/01 22:41:36 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execute.h"

void
	ft_execute(char *cmd_str, char **environ)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(cmd_str, ' ');
	cmd_path = NULL;
	if (cmd && ft_strchr(cmd[0], '/'))
		cmd_path = ft_strdup(cmd[0]);
	else if (cmd)
		cmd_path = ft_get_cmd_path(cmd[0], environ);
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
