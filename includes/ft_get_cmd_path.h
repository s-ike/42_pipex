/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_path.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 23:13:13 by sikeda            #+#    #+#             */
/*   Updated: 2022/04/30 23:16:43 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_CMD_PATH_H
# define FT_GET_CMD_PATH_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_error.h"
# include "ft_free.h"

char	*ft_get_cmd_path(char *cmd, char **environ);

#endif
