/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:06:54 by sikeda            #+#    #+#             */
/*   Updated: 2022/04/29 17:07:44 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_free.h"

void
	ft_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void
	ft_free_split(char ***split)
{
	char	**head;

	if (split)
		head = *split;
	while (**split)
	{
		ft_free(*split);
		(*split)++;
	}
	free(head);
	head = NULL;
}
