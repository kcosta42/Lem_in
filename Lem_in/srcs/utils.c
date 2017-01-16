/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:15:26 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/16 13:27:24 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_byte	ft_check_room(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		while (tmp)
		{
			if (tmp->content_size == list->content_size
				|| !ft_strcmp(tmp->content, list->content))
				return (1);
			tmp = tmp->next;
		}
		list = list->next;
	}
	return (0);
}

t_byte	ft_remove_path(int parent[])
{
	int		j;

	j = get_glob()->count - 1;
	while (parent[j] != -1)
	{
		(*get_path())[j][parent[j]] = 0;
		(*get_path())[parent[j]][j] = 0;
		j = parent[j];
	}
	return (1);
}

t_list	*ft_find_room(t_list *room, char *name, t_byte alt)
{
	char		*to_find;

	to_find = (alt) ? ft_strsub(name, 0, alt) : ft_strdup(name);
	while (room)
	{
		if (!ft_strcmp(room->content, to_find))
		{
			ft_strdel(&to_find);
			return (room);
		}
		room = room->next;
	}
	ft_strdel(&to_find);
	return (NULL);
}

t_list	*ft_find_name(t_list *room, size_t index)
{
	while (room)
	{
		if (room->content_size == index)
			return (room);
		room = room->next;
	}
	return (NULL);
}
