/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 16:57:11 by tlebrize          #+#    #+#             */
/*   Updated: 2014/12/15 10:27:46 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*ft_bubbles_time(t_list *list, int r)
{
	t_list		*first;
	int			bulle;

	first = list;
	bulle = 1;
	while (bulle != 0)
	{
		bulle = 0;
		while (list->next != NULL)
		{
			if ((r == 0 && (list->stats).st_mtimespec.tv_sec <
					(list->next->stats).st_mtimespec.tv_sec) ||
					(r != 0 && (list->stats).st_mtimespec.tv_sec >
					(list->next->stats).st_mtimespec.tv_sec))
			{
				ft_swaplink(list, list->next);
				bulle = 1;
			}
			list = list->next;
		}
		list = first;
	}
	return (first);
}

t_list	*ft_bubbles_lexi(t_list *list, int r)
{
	t_list		*first;
	int			bulle;

	first = list;
	bulle = 1;
	while (bulle != 0)
	{
		bulle = 0;
		while (list->next != NULL)
		{
			if ((r == 0 && ft_strcmp(list->name, list->next->name) == 1) ||
					(r != 0 && ft_strcmp(list->name, list->next->name) == -1))
			{
				ft_swaplink(list, list->next);
				bulle = 1;
			}
			list = list->next;
		}
		list = first;
	}
	return (first);
}
