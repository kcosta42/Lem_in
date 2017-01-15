/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 22:27:18 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/13 17:21:31 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct		s_glob
{
	t_byte			end;
	t_byte			start;
	t_byte			stop;
	unsigned int	count;
	unsigned int	index;
	int				dist;
}					t_glob;

t_glob	*get_glob(void);
t_list	**get_room(void);
t_list	**get_result(void);
int		***get_path(void);

#endif
