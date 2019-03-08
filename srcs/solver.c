/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:20:03 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/16 15:10:48 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		{
			min = dist[v];
			min_index = v;
		}
		v++;
	}
	return (min_index);
}

static t_byte	ft_initialise_solver(
							int (*dist)[], int (*visited)[], int (*parent)[])
{
	unsigned int	i;

	i = -1;
	while (++i < get_glob()->count)
	{
		(*dist)[i] = INT_MAX;
		(*visited)[i] = 0;
		(*parent)[0] = -1;
	}
	(*dist)[0] = 0;
	return (0);
}

int				ft_solve(int ants, unsigned int c, unsigned int v, int u)
{
	int				dist[get_glob()->count];
	int				visited[get_glob()->count];
	int				parent[get_glob()->count];

	(void)ft_initialise_solver(&dist, &visited, &parent);
	while (++c < get_glob()->count - 1)
	{
		v = -1;
		u = ft_shortest_path(dist, visited);
		visited[u] = 1;
		while (++v < get_glob()->count)
			if (!visited[v] && (*get_path())[u][v] && dist[u] != INT_MAX
							&& dist[u] + (*get_path())[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + (*get_path())[u][v];
			}
	}
	if (get_glob()->dist < dist[get_glob()->count - 1]
						|| dist[get_glob()->count - 1] == INT_MAX)
		return (get_glob()->dist == INT_MAX);
	get_glob()->dist = dist[get_glob()->count - 1];
	ft_lstadd(get_result(), ft_lstnew(parent, sizeof(parent)));
	(void)ft_remove_path((*get_result())->content);
	return (ft_solve(ants, -1, -1, 0));
}
