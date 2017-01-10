/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 14:37:18 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/10 12:55:17 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list		**get_room(void)
{
	static t_list	*rooms = NULL;

	return (&rooms);
}

int			***get_path(void)
{
	static int		**path = NULL;

	return (&path);
}
