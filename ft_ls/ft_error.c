/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 20:30:16 by tlebrize          #+#    #+#             */
/*   Updated: 2015/01/15 16:13:43 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error_option(char option)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(option);
	ft_putchar('\n');
	ft_putstr("usage: ft_ls [-Ralrt]\n");
	exit(0);
}

void	ft_putENOENT(t_files *file)
{
	while (file != NULL)
	{
		if (file->error == 2)
		{
			ft_putstr("ft_ls: ");
			ft_putstr(file->filename);
			ft_putendl(": No such file or directory");
		}
		file = file->next;
	}
}

void	ft_putEACESS(t_files *file)
{
	while (file != NULL)
	{
		if (file->error == 3)
		{
			ft_putstr("ft_ls: ");
			ft_putstr(file->filename);
			ft_putendl(": Permission denied\n");
		}
		file = file->next;
	}
}

void	ft_EACESS(char *filename)
{
	ft_putstr(filename);
	ft_putstr(":\n");
	ft_putstr("ft_ls: ");
	ft_putstr(filename);
	ft_putstr(": Permission denied\n");
}

t_files	*ft_addfile(t_files *file, char *name)
{
	t_files			*new;
	t_files			*tmp;
	struct stat		buf;

	new = (t_files*)malloc(sizeof(t_files*));
	tmp = file;
	if (new)
	{
		ft_strcpy(new->filename, name);
		new->error = 0;
		stat(name, &buf);
		if (errno == ENOENT)
			new->error = 2;
		listxattr(name, NULL, 0, XATTR_NOFOLLOW);
		if (errno == EACCES)
			new->error = 3;
		errno = 0;
		if (file == NULL)
			return (new);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (file);
}
