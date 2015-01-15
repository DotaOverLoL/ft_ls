/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 17:04:59 by tlebrize          #+#    #+#             */
/*   Updated: 2015/01/12 17:17:28 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*ft_addlink(t_list *list, char *name, char *path)
{
	t_list		*new;
	struct stat	stats;

	new = (t_list*)malloc(sizeof(t_list));
	new->name = (char*)malloc(sizeof(char) * (ft_strlen(name) + 1));
	new->path = (char*)malloc(sizeof(char) * (ft_strlen(path) + 1));
	if (new && new->name && new->path)
	{
		stat(path, &stats);
		ft_strcpy(new->name, name);
		ft_strcpy(new->path, path);
		new->stats = stats;
		new->next = list;
		return (new);
	}
	else
		return (NULL);
}

void		ft_clearlist(t_list *list)
{
	t_list	*new;

	if (list != NULL)
	{
		new = list->next;
		list->next = NULL;
		free(list->name);
		free(list->path);
		ft_clearlist(new);
	}
}

void		ft_swaplink(t_list *l1, t_list *l2)
{
	char		name[ft_strlen(l1->name) + 1];
	char		path[ft_strlen(l1->path) + 1];
	struct stat	stats;

	ft_strcpy(name, l1->name);
	ft_strcpy(path, l1->path);
	free(l1->name);
	free(l1->path);
	l1->name = (char*)malloc(sizeof(char) * (ft_strlen(l2->name) + 1));
	l1->path = (char*)malloc(sizeof(char) * (ft_strlen(l2->path) + 1));
	stats = l1->stats;
	ft_strcpy(l1->name, l2->name);
	ft_strcpy(l1->path, l2->path);
	l1->stats = l2->stats;
	free(l2->name);
	free(l2->path);
	l2->name = (char*)malloc(sizeof(char) * (ft_strlen(name) + 1));
	l2->path = (char*)malloc(sizeof(char) * (ft_strlen(path) + 1));
	ft_strcpy(l2->name, name);
	ft_strcpy(l2->path, path);
	l2->stats = stats;
}

void		ft_printlist(t_list *list)
{
	while (list != NULL)
	{
		ft_putstr(list->name);
		ft_putstr(" : ");
		ft_putendl(list->path);
		ft_putmodes(list->stats);
		list = list->next;
	}
	ft_putchar('\n');
}
