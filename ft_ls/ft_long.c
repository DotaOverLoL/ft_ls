/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 17:08:38 by tlebrize          #+#    #+#             */
/*   Updated: 2015/01/08 17:58:00 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_long(t_list *list, t_width width)
{
	char	link[NAME_MAX];

	ft_putmodes(list->stats);
	ft_putnlinks((list->stats).st_nlink, width.links);
	ft_putnames((list->stats).st_uid, (list->stats).st_gid, width);
	ft_putblocks(list, width);
	ft_puttime(&(list->stats).st_mtimespec.tv_sec);
	ft_putstr(list->name);
	if (S_ISLNK((list->stats).st_mode))
	{
		ft_putstr(" -> ");
		readlink(list->path, link, NAME_MAX);
		ft_putstr(link);
	}
}
