/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:21:07 by tlebrize          #+#    #+#             */
/*   Updated: 2015/01/15 15:44:29 by tlebrize         ###   ########.fr       */
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
	if (args.f == 1)
		ft_putpath(list->path);
	if (args.l != 0)
		ft_total(list, args);
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
	t_list			*files;
	t_list			*directories;
	char			*path;

	dirs = opendir(dirpath);
	files = NULL;
	directories = NULL;
	if (dirs == NULL)
	{
		ft_EACESS(dirpath);
		return (0);
	}
	while ((dire = readdir(dirs)) != NULL)
	{
		path = ft_path(dirpath, dire->d_name);
		files = ft_addlink(files, dire->d_name, path);
		if (dire->d_type == DT_DIR && ft_strcmp(dire->d_name, ".") != 0 &&
				ft_strcmp(dire->d_name, "..") != 0 && args.R != 0)
			directories = ft_addlink(directories, dire->d_name, path);
	}
	ft_display(files, args);
	if (directories != NULL)
		ft_recursive(directories, args);
	closedir(dirs);
	return (0);
}
