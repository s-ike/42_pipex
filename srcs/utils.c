/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:51:46 by sikeda            #+#    #+#             */
/*   Updated: 2022/04/23 23:07:11 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void
	ft_puterror(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
}

void
	ft_putperror(char *msg)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	perror(msg);
	ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
}