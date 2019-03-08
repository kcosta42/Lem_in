/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 22:28:06 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/16 16:15:09 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_error(char *str, int ft_errnum)
{
	ft_putstr_fd(str, 2);
	return (ft_errnum);
}

static t_byte	ft_print_result(int ants, int busy[], int parent[], int j)
{
	int			index;

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
	return (0);
}

static t_byte	ft_manage_result(int ants, int busy[])
{
	t_list		*parent;

	if (busy[get_glob()->count - 1] == ants)
		return (1);
	parent = *get_result();
	while (parent)
	{
		ft_print_result(ants, busy, parent->content, get_glob()->count - 1);
		parent = parent->next;
	}
	ft_putchar('\n');
	return (ft_manage_result(ants, busy));
}

int				main(void)
{
	int				*busy;

	(void)ft_parse();
	busy = (int*)ft_memalloc(sizeof(int) * get_glob()->count);
	busy[0] = get_glob()->ants;
	if (get_glob()->ants <= 0 || ft_check_room(*get_room()))
		return (ft_error("\nERROR\n", 2));
	if (ft_solve(get_glob()->ants, -1, -1, 0))
		return (ft_error("\nERROR\n", 2));
	ft_putchar('\n');
	(void)ft_manage_result(get_glob()->ants, busy);
	free(busy);
	busy = NULL;
	return (0);
}
