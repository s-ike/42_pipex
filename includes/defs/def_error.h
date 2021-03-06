/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:08:27 by sikeda            #+#    #+#             */
/*   Updated: 2022/04/23 23:00:22 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_ERROR_H
# define DEF_ERROR_H

# include "def_pipex.h"
# include "def_color.h"

/*
** program
*/
# define ERR_PREFIX COLOR_B_RED PRG_NAME ": "
# define ERR_SUFFIX COLOR_RESET "\n"
# define ERR_INVAL ERR_PREFIX "invalid argument" ERR_SUFFIX

/*
** system
*/
# define ERR_MALLOC "malloc error"

#endif
