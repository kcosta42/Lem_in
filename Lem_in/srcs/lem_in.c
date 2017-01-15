/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 22:28:06 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/13 19:27:30 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	return (get_glob()->start && get_glob()->end);
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

static t_list	*ft_find_name(t_list *room, size_t index)
{
	while (room)
	{
		if (room->content_size == index)
			return (room);
		room = room->next;
	}
	return (NULL);
}

static int		ft_shortest_path(int dist[], int visited[])
{
	int				min;
	int				min_index;
	unsigned int	v;

	min = INT_MAX;
	v = 0;
	while (v < get_glob()->count)
	{
		if (!visited[v] && dist[v] <= min)
			min = dist[v], min_index = v;
		v++;
	}
	return (min_index);
}

static void		ft_print_path(int parent[], int j)
{
	if (parent[j] == -1)
		return ;
	ft_print_path(parent, parent[j]);

	ft_printf("%s ", ft_find_name(*get_room(), j)->content);
}

static int		ft_print_result(int ants, int busy[], int parent[], int j)
{
	int			index;

	if (busy[get_glob()->count - 1] == ants)
		return (1);
	while (parent[j] != -1)
	{
		if (!busy[parent[j]])
			j = parent[j];
		else
		{
			index = busy[parent[j]] - 1;
			busy[j] = ((unsigned int)j == get_glob()->count - 1) ? busy[j] + 1
															: busy[parent[j]];
			busy[parent[j]] = (parent[j] == 0) ? busy[parent[j]] - 1 : 0;
			ft_printf("L%d-%s ", ants - index,
										ft_find_name(*get_room(), j)->content);
			return (ft_print_result(ants, busy, parent, parent[j]));
		}
	}
	ft_printf("\n");
	return (ft_print_result(ants, busy, parent, get_glob()->count - 1));
}

static int		ft_solve(int ants)
{
	int		**path;
	int		dist[get_glob()->count];
	int		visited[get_glob()->count];
	int		parent[get_glob()->count];
	int		busy[get_glob()->count];

	if (ants <= 0 || ft_check_room(*get_room()))
		return (1);
	path = *get_path();
	for (unsigned int i = 0; i <  get_glob()->count; i++)
		dist[i] = INT_MAX, visited[i] = 0, parent[0] = -1, busy[i] = 0;
	dist[0] = 0;
	busy[0] = ants;
	for (unsigned int c = 0; c < get_glob()->count - 1; c++)
	{
		int u = ft_shortest_path(dist, visited);
		visited[u] = 1;
		for (unsigned int v = 0; v < get_glob()->count; v++)
			if (!visited[v] && path[u][v] && dist[u] != INT_MAX
							&& dist[u] + path[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + path[u][v];
			}
	}
	if (get_glob()->dist >= dist[get_glob()->count - 1])
		get_glob()->dist = dist[get_glob()->count - 1];
	else
		return (0);
	ft_printf("\n%d -> %d\t%d\t%s ", 0, get_glob()->count - 1, dist[get_glob()->count - 1], ft_find_name(*get_room(), 0)->content);
	ft_print_path(parent, get_glob()->count - 1);
	ft_printf("\n");
	ft_lstadd(get_result(), ft_lstnew(parent, sizeof(parent)));
	ft_print_result(ants, busy, (*get_result())->content, get_glob()->count - 1);
	int		j;
	j = get_glob()->count - 1;
	while (parent[j] != -1)
	{
		(*get_path())[j][parent[j]] = 0;
		(*get_path())[parent[j]][j] = 0;
		j = parent[j];
	}
	return (ft_solve(ants));
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
	(*get_path())[second->content_size][first->content_size] = 1;
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
	while (ft_getline(0, &line) > 0)
	{
		ft_putendl(line);
		if (!valid && *line == '#')
			valid = ft_check_command(line);
		else if (!valid && ft_strchr(line, '-'))
			valid = ft_add_path(line);
		else if (!valid && *line != 'L')
			valid = ft_add_room(line);
		else
			valid = 1;
		ft_strdel(&line);
	}
	if (ft_solve(ants))
		ft_putstr_fd("\nERROR\n", 2);
	return (0);
}
