/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 22:27:18 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/10 17:49:56 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define END	0
# define START	1
# define STOP	2
# define COUNT	3
# define INDEX	4

typedef struct		s_glob
{
	t_byte			end;
	t_byte			start;
	t_byte			stop;
	unsigned int	count;
	unsigned int	index;
}					t_glob;

t_glob	*get_glob(void);
t_list	**get_room(void);
int		***get_path(void);

#endif
