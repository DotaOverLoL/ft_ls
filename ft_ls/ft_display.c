/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 18:16:27 by tlebrize          #+#    #+#             */
/*   Updated: 2015/01/08 17:58:56 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_putmodes(struct stat buff)
{
	char		ft;

	ft = S_ISBLK(buff.st_mode) ? 'b' : 'e';
	ft = S_ISCHR(buff.st_mode) ? 'c' : ft;
	ft = S_ISDIR(buff.st_mode) ? 'd' : ft;
	ft = S_ISLNK(buff.st_mode) ? 'l' : ft;
	ft = S_ISSOCK(buff.st_mode) ? 's' : ft;
	ft = S_ISFIFO(buff.st_mode) ? 'p' : ft;
	ft = S_ISREG(buff.st_mode) ? '-' : ft;
	ft_putchar(ft);
	ft_putchar(buff.st_mode & S_IRUSR ? 'r' : '-');
	ft_putchar(buff.st_mode & S_IWUSR ? 'w' : '-');
	ft_putchar(buff.st_mode & S_IXUSR ? 'x' : '-');
	ft_putchar(buff.st_mode & S_IRGRP ? 'r' : '-');
	ft_putchar(buff.st_mode & S_IWGRP ? 'w' : '-');
	ft_putchar(buff.st_mode & S_IXGRP ? 'x' : '-');
	ft_putchar(buff.st_mode & S_IROTH ? 'r' : '-');
	ft_putchar(buff.st_mode & S_IWOTH ? 'w' : '-');
	ft_putchar(buff.st_mode & S_IXOTH ? 'x' : '-');
	ft_putstr("  ");
}

void	ft_puttime(time_t *clock)
{
	char	rtime[26];
	char	ptime[13];
	time_t	tloc;

	time(&tloc);
	ft_strcpy(rtime, ctime(clock));
	if (&tloc - clock < 15778458 || clock > &tloc)
	{
		ft_strncpy(ptime, rtime + 4, 7);
		ft_strncpy(ptime + 7, rtime + 19, 5);
	}
	else
		ft_strncpy(ptime, rtime + 4, 12);
	ptime[12] = '\0';
	ft_putstr(ptime);
	ft_putchar(' ');
}

void	ft_putnlinks(nlink_t links, int width)
{
	int links_spaces;

	links_spaces = width - ft_intlen((int)links);
	while (links_spaces-- != 0)
		ft_putchar(' ');
	ft_putnbr((int)links);
	ft_putchar(' ');
}

void	ft_putnames(uid_t uid, gid_t gid, t_width width)
{
	struct passwd	*owner;
	struct group	*group;
	int				owner_spaces;
	int				group_spaces;

	owner = getpwuid(uid);
	group = getgrgid(gid);
	owner_spaces = 2 + (width.owner - ft_strlen(owner->pw_name));
	group_spaces = 2 + (width.group - ft_strlen(group->gr_name));
	ft_putstr(owner->pw_name);
	while (owner_spaces-- != 0)
		ft_putchar(' ');
	ft_putstr(group->gr_name);
	while (group_spaces-- != 0)
		ft_putchar(' ');
}

void	ft_putblocks(t_list *list, t_width width)
{
	int		block_spaces;

	block_spaces = (width.bytes - ft_intlen((int)(list->stats).st_size));
	if (S_ISBLK((list->stats).st_mode) || S_ISCHR((list->stats).st_mode))
	{
		block_spaces = 0;
		ft_majmin((list->stats).st_rdev, width);
	}
	else
	{
		while (block_spaces-- != 0)
			ft_putchar(' ');
		ft_putnbr((int)(list->stats).st_size);
		ft_putchar(' ');
	}
}
