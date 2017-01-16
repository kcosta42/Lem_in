/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:09:17 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/16 13:15:23 by kcosta           ###   ########.fr       */
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

t_byte			ft_parse(void)
{
	char	*line;
	t_byte	valid;

	if (ft_getline(0, &line) <= 0)
		return (1);
	ft_putendl(line);
	valid = !ft_strisdigit(line);
	get_glob()->ants = ft_atoi(line);
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
	return (valid);
}
