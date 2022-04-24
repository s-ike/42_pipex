/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:52:51 by sikeda            #+#    #+#             */
/*   Updated: 2022/04/24 12:21:48 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include "def_error.h"
# include "def_color.h"

void	ft_puterror(char *msg);
void	ft_putperror(char *msg);
void	ft_puterror_and_exit_failure(void(*puterror)(char *msg), char *msg);

#endif
