/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/13 17:19:13 by tlebrize          #+#    #+#             */
/*   Updated: 2014/12/30 16:15:42 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_display(t_list *list, t_args args)
{
	t_width	w;

	w = ft_get_width(list);
	if (args.t != 0)
		ft_bubbles_time(list, args.r);
	else
		ft_bubbles_lexi(list, args.r);
	if (args.l != 0)
		ft_total(list, args);
	if ((list->name[0] != '.' || args.a != 0) && args.f == 1)
		ft_putpath(list->path);
	while (list != NULL)
	{
		if ((list->name[0] != '.' || args.a != 0) && args.l != 0)
			ft_long(list, w);
		else if (list->name[0] != '.' || args.a != 0)
			ft_putstr(list->name);
		if (list->name[0] != '.' || args.a != 0)
			ft_putchar('\n');
		list = list->next;
	}
}

void		ft_recursive(t_list *list, t_args args)
{
	if (args.t != 0)
		ft_bubbles_time(list, args.r);
	else
		ft_bubbles_lexi(list, args.r);
	while (list != NULL)
	{
		ft_putchar('\n');
		args.f = 1;
		ft_base(list->path, args);
		list = list->next;
	}
}

int			ft_base(char *dirpath, t_args args)
{
	DIR				*dirs;
	struct dirent	*dire;
	struct stat		stats;
	t_list			*files;
	t_list			*directories;
	char			*path;

	dirs = opendir(dirpath);
	files = NULL;
	directories = NULL;
	if (dirs == NULL)
		return (-1);
	while ((dire = readdir(dirs)) != NULL)
	{
		path = ft_path(dirpath, dire->d_name);
		stat(path, &stats);
		files = ft_addlink(files, dire->d_name, path, stats);
		if (S_ISDIR(stats.st_mode) && ft_strcmp(dire->d_name, ".") != 0 &&
				ft_strcmp(dire->d_name, "..") != 0 && args.R != 0)
			directories = ft_addlink(directories, dire->d_name, path, stats);
	}
	ft_display(files, args);
	if (directories != NULL)
		ft_recursive(directories, args);
	return (0);
}
