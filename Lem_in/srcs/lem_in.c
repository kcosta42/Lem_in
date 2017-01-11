/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 22:28:06 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/11 16:07:27 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_byte		g_end = 0;
t_byte		g_start = 0;
t_byte		g_stop = 0;
int			g_index = 0;
int			g_max = 1;

static t_byte	ft_check_command(char *line)
{
	if (ft_strcmp(line, "##start"))
	{
		if (ft_strcmp(line, "##end"))
			return (0);
		else
			get_glob()->end = 1;
	}
	else
		get_glob()->start = 1;
	return (0);
}

static t_byte	ft_add_room(char *line)
{
	char		*name;

	if (get_glob()->stop || !ft_strchr(line, ' '))
		return (1);
	name = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
	while (*line != ' ')
		line++;
	if (!ft_isdigit(*(++line)))
		return (2);
	while (ft_isdigit(*(line++)))
		;
	if (!*line || !ft_isdigit(*line))
		return (3);
	while (ft_isdigit(*(line++)))
		;
	ft_lstadd(get_room(), ft_lstnew(name, ft_strlen(name) + 1));
	(*get_room())->content_size = (get_glob()->start) ? 0 : get_glob()->index;
	(*get_room())->content_size = (get_glob()->end) ? (size_t)-1
											: (*get_room())->content_size;
	get_glob()->index += (!get_glob()->start && !get_glob()->end);
	get_glob()->count++;
	get_glob()->start = (get_glob()->start) ? 0 : get_glob()->start;
	get_glob()->end = (get_glob()->end) ? 0 : get_glob()->end;
	return (0);
}

static t_byte	ft_check_room(t_list *list)
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

static t_list	*ft_find_room(t_list *room, char *name, t_byte alt)
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

static int		ft_solve(int ants)
{
	int		**path;

	if (ants <= 0 || ft_check_room(*get_room()))
		return (1);
	path = *get_path();
	for (unsigned int i = 0; i < get_glob()->count; i++)
		for (unsigned int j = 0; j < get_glob()->count; j++)
			if (path[i][j])
				ft_printf("%d-%d = %d\n", i, j, path[i][j]);
	return (0);
}

static t_byte	ft_add_path(char *line)
{
	t_list		*first;
	t_list		*second;

	get_glob()->stop = 1;
	first = ft_find_room(*get_room(), line, ft_strchr(line, '-') - line);
	second = ft_find_room(*get_room(), ft_strchr(line, '-') + 1, 0);
	if (!first || !second)
		return (1);
	if (first->content_size == (size_t)-1)
		first->content_size = get_glob()->index;
	else if (second->content_size == (size_t)-1)
		second->content_size = get_glob()->index;
	(*get_path())[first->content_size][second->content_size] = 1;
	return (0);
}

int			main(void)
{
	char	*line;
	int		ants;
	t_byte	valid;

	if (ft_getline(0, &line) <= 0)
		return (1);
	ft_putendl(line);
	valid = !ft_strisdigit(line);
	ants = ft_atoi(line);
	ft_strdel(&line);
	while (!valid && ft_getline(0, &line) > 0)
	{
		ft_putendl(line);
		if (*line == '#')
			valid = ft_check_command(line);
		else if (ft_strchr(line, '-'))
			valid = ft_add_path(line);
		else if (*line != 'L')
			valid = ft_add_room(line);
		else
			valid = 1;
		ft_strdel(&line);
	}
	if (ft_solve(ants))
		ft_putstr_fd("\nError\n", 2);
	return (0);
}
