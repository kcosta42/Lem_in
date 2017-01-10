/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 22:28:06 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/10 13:48:38 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_byte		g_end = 0;
t_byte		g_start = 0;
t_byte		g_stop = 0;
int			g_index;

static t_byte	ft_check_command(char *line)
{
	if (ft_strcmp(line, "##start"))
	{
		if (ft_strcmp(line, "##end"))
			return (0);
		else
			g_end = 1;
	}
	else
		g_start = 1;
	return (0);
}

static t_byte	ft_add_room(char *line)
{
	char		*name;

	if (g_stop || !ft_strchr(line, ' '))
		return (1);
	name = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
	while (*line != ' ')
		line++;
	if (!ft_isdigit(*(++line)))
		return (2);
	while (ft_isdigit(*(line++)))
		;
	if (*line || !ft_isdigit(*(++line)))
		return (3);
	while (ft_isdigit(*(line++)))
		;
	ft_lstadd(get_room(), ft_lstnew(name, ft_strlen(name) + 1));
	ft_printf("%s\n", (*get_room())->content);
	(*get_room())->content_size = (g_start) ? 0 : g_index;
	(*get_room())->content_size = (g_end) ? (size_t)-1 : g_index;
	g_start = (g_start) ? 0 : 1;
	g_end = (g_end) ? 0 : 1;
	g_index++;
	return (0);
}

static t_byte	ft_check_room(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		while (tmp)
		{
			if (tmp->content_size == list->content_size)
				return (1);
			tmp = tmp->next;
		}
		list = list->next;
	}
	return (0);
}

static t_list	*ft_find_room(char *name, t_byte alt)
{
	t_list		*room;

	room = *get_room();
	while (room)
	{
		ft_printf("%s %s\n", room->content, name);
		if ((alt) ? !ft_strncmp(room->content, name, alt) : !ft_strcmp(room->content, name))
			return (room);
		room = room->next;
	}
	return (NULL);
}

static void		ft_solve()
{
	int		**path;

	path = *get_path();
	ft_printf("%d\n", g_index);
	for (int i = 0; i < g_index; i++)
		for (int j = 0; j < g_index; j++)
			ft_printf("%d-%d = %d\n", i, j, path[i][j]);
}

static t_byte	ft_add_path(char *line)
{
	t_list		*first;
	t_list		*second;

	if (ft_check_room(*get_room()))
		return (1);
	g_stop = 1;
	if (!*get_path())
		*get_path() = ft_memalloc(sizeof(int[g_index][g_index]));
	first = ft_find_room(line, line - ft_strchr(line, '-'));
	second = ft_find_room(ft_strchr(line, '-') + 1, 0);
	if (!first || !second)
		return (2);
	if (first->content_size == (size_t)-1)
		first->content_size = g_index;
	else if (second->content_size == (size_t)-1)
		second->content_size = g_index;
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
	ants = ft_atoi(line);
	if (ants <= 0)
		return (-1);
	ft_strdel(&line);
	valid = 1;
	while (valid && ft_getline(0, &line) > 0)
	{
		ft_putendl(line);
		if (*line == '#')
			valid = ft_check_command(line);
		if (ft_strchr(line, '-'))
			valid = ft_add_path(line);
		else
			valid = ft_add_room(line);
		ft_strdel(&line);
	}
	ft_solve();
	return (0);
}
