/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 18:16:27 by tlebrize          #+#    #+#             */
/*   Updated: 2015/01/06 19:42:44 by tlebrize         ###   ########.fr       */
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

void	ft_long(t_list *list, t_width w)
{
	int				lspc;

	ft_putmodes(list->stats);
	lspc = w.links - ft_intlen((int)(list->stats).st_nlink);
	while (lspc-- != 0)
		ft_putchar(' ');
	ft_putnbr((int)(list->stats).st_nlink);
	ft_putchar(' ');
	ft_too_long(list, w);
}

void	ft_too_long(t_list *list, t_width w)
{
	struct passwd	*own;
	struct group	*grp;
	int				ospc;
	int				gspc;
	int				bspc;

	own = getpwuid((list->stats).st_uid);
	grp = getgrgid((list->stats).st_gid);
	ospc = 2 + (w.owner - ft_strlen(own->pw_name));
	gspc = 2 + (w.group - ft_strlen(grp->gr_name))
	bspc = (w.bytes - ft_intlen((int)(list->stats).st_size));
	ft_putstr(own->pw_name);
	while (ospc-- != 0)
		ft_putchar(' ');
	ft_putstr(grp->gr_name);
	while (gspc-- != 0)
		ft_putchar(' ');
	while (bspc-- != 0)
		ft_putchar(' ');
	ft_way_too_long(list, w);
}

void	ft_way_too_long(t_list *list, t_width w)
{
	char			link[NAME_MAX];

	if (S_ISBLK((list->stats).st_mode) || S_ISCHR((list->stats).st_mode))
		ft_majmin((list->stats).st_rdev, w);
	else
		ft_putnbr((int)(list->stats).st_size);
	ft_putchar(' ');
	ft_puttime(&(list->stats).st_mtimespec.tv_sec);
	ft_putstr(list->name);
	if (S_ISLNK((list->stats).st_mode))
	{
		ft_putstr(" -> ");
		readlink(list->path, link, NAME_MAX);
		ft_putstr(link);
	}
}
