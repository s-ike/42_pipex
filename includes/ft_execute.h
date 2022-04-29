/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:09:36 by sikeda            #+#    #+#             */
/*   Updated: 2022/04/29 17:11:33 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTE_H
# define FT_EXECUTE_H

# include <unistd.h>
# include "libft.h"
# include "ft_error.h"
# include "ft_free.h"

void	ft_execute(char *cmd_str, char **environ);

#endif
