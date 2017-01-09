/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 22:28:06 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/09 16:03:11 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_byte		g_end;
t_byte		g_start;
t_byte		g_stop;

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
	return (1);
}

static t_byte	ft_add_room(char *line)
{
	static int	index = 1;
	char		*name;

	if (!ft_strchr(line, ' '))
		return (1);
	name = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
	while (*line != ' ')
		line++;
	if (!ft_isdigit(*line))
		return (2);
	while (ft_isdigit(*(line++)))
		;
	if (!ft_isdigit(*(line++)))
		return (3);
	while (ft_isdigit(*(line++)))
	ft_lstadd(get_rooms(), ft_lstnew(name, ft_strlen(name) + 1));
	(*get_room())->content_size = index++;
	return (0);
}

static t_byte	ft_add_path(char *line)
{
}

int			main(void)
{
	char	*line;
	int		ants;
	t_byte	valid;

	if (ft_getline(1, &line) <= 0)
		return (1);
	ants = ft_atoi(line);
	if (ants <= 0)
		return (-1);
	ft_strdel(&line);
	valid = 1;
	while (valid && ft_getline(1, &line) > 0)
	{
		if (*line == '#')
			valid = ft_check_command(line);
		if (ft_strchr(line, '-'))
			ft_add_path(line);
		else
			ft_add_room(line);
		ft_strdel(&line);
	}
	ft_solve();
	return (0);
}
