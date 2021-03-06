/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdisplay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/13 16:53:20 by tlebrize          #+#    #+#             */
/*   Updated: 2015/01/12 16:21:30 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_width		ft_get_width(t_list *list)
{
	t_width			w;
	struct passwd	*own;
	struct group	*grp;


	w.links = 0;
	w.owner = 0;
	w.group = 0;
	w.bytes = 0;
	w.major = 0;
	w.minor = 0;
	while (list != NULL)
	{
		own = getpwuid((list->stats).st_uid);
		grp = getgrgid((list->stats).st_gid);
		if (ft_intlen((int)(list->stats).st_nlink) > w.links)
			w.links = ft_intlen((int)(list->stats).st_nlink);
		if (ft_strlen(own->pw_name) > (size_t)w.owner)
			w.owner = ft_strlen(own->pw_name);
		if (ft_strlen(grp->gr_name) > (size_t)w.group)
			w.group = ft_strlen(grp->gr_name);
		if (ft_intlen((int)(list->stats).st_size) > w.bytes)
			w.bytes = ft_intlen((int)(list->stats).st_size);
		if (ft_intlen(major((list->stats).st_rdev)) > w.major)
			w.major = ft_intlen(major((list->stats).st_rdev));
		if (ft_intlen(minor((list->stats).st_rdev)) > w.minor)
			w.minor = ft_intlen(minor((list->stats).st_rdev));
		if (S_ISBLK((list->stats).st_mode) || S_ISCHR((list->stats).st_mode))
		{
			if (w.major > w.minor)
				w.bytes = 3 + (w.major * 2);
			else
				w.bytes = 3 + (w.minor * 2);
		}
		list = list->next;
	}
	return (w);
}

char		*ft_path(char *base, char *str)
{
	char	*new;
	int		i;

	new = (char*)malloc(sizeof (char) * (ft_strlen(base) + ft_strlen(str) + 2));
	i = 0;
	while (*base)
		new[i++] = *base++;
	new[i++] = '/';
	while (*str)
		new[i++] = *str++;
	new[i] = '\0';
	return (new);
}

void	ft_total(t_list *list, t_args args)
{
	int		blocks;
	int		empty;

	blocks = 0;
	empty = 0;
	while (list != NULL)
	{
		if (list->name[0] != '.' || args.a != 0)
		{
			blocks += (int)(list->stats).st_blocks;
			empty++;
		}
		list = list->next;
	}
	if (empty != 0)
	{
		ft_putstr("total ");
		ft_putnbr(blocks);
		ft_putchar('\n');
	}
}

int		ft_intlen(int i)
{
	int		len;

	len = 1;
	while ((i /= 10) != 0)
		len++;
	return (len);
}

void	ft_putpath(char *path)
{
	int		i;

	i = 0;
	while (path[i + 2] != '\0')
		ft_putchar(path[i++]);
	ft_putstr(":\n");
}
