/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 17:42:23 by tlebrize          #+#    #+#             */
/*   Updated: 2014/12/10 17:11:43 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"
#include "list.h"


void	ft_print_list(t_list *list)
{
	while (list)
	{
		ft_putendl(list->name);
		list = list->next;
	}
}

t_list	*ft_add_link(t_list *list, char *name, char *path)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	new->name = (char*)malloc(sizeof(char) * (ft_strlen(name) + 1));
	new->path = (char*)malloc(sizeof(char) * (ft_strlen(path) + 1));
	if (new && new->name && new->path)
	{
		ft_strcpy(new->name, name);
		ft_strcpy(new->path, path);
		new->next = list;
	}
	return (new);
}

char	*ft_path(char *path, char *str)
{
	char	*new;
	int		i;

	new = (char*)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(str) + 2));
	i = 0;
	while (*path)
		new[i++] = *path++;
	new[i++] = '/';
	while (*str)
		new[i++] = *str++;
	new[i] = '\0';
	return (new);
}

int		ft_list_dir(const char *dirname)
{
	DIR				*dirs;
	struct dirent	*dire;

	dirs = opendir(dirname);
	if (dirs == NULL)
		return (-1);
	while ((dire = readdir(dirs)) != NULL)
		ft_putendl(dire->d_name);
	return (0);
}

int		ft_list_dir_R(char *dirname)
{
	DIR				*dirs;
	struct dirent	*dire;
	struct stat		buff;
	t_list			*list;
	char			*path;

	dirs = opendir(dirname);
	list = NULL;
	if (dirs == NULL)
		return (-1);
	ft_putendl(dirname);
	while ((dire = readdir(dirs)) != NULL)
	{
		path = ft_path(dirname, dire->d_name);
		ft_putendl(dire->d_name);
		if (stat(path, &buff) == -1)
			ft_putendl(strerror(errno));
		else if (S_ISDIR(buff.st_mode) && ft_strcmp(dire->d_name, ".") != 0 &&
				ft_strcmp(dire->d_name, "..") != 0)
					list = ft_add_link(list, dire->d_name, path);
	}
	ft_putchar('\n');
	while (list)
	{
		ft_list_dir_R(list->path);
		list = list->next;
	}
	closedir(dirs);
	return (0);
}

int		main(int ac, char **av)
{
	ft_putnbr(ft_list_dir_R("dir.useless"));
	return (0);
}
