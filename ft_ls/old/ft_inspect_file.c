/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inspect_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 15:21:19 by tlebrize          #+#    #+#             */
/*   Updated: 2014/12/11 15:51:30 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>
#include "libft.h"

#include "ft_ls.h"

void	ft_putmodes(struct stat buff)
{
	char			ft;

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
	ft_putchar('\n');
}

/*int		ft_inspect_file(char *filename)
{
	struct stat		buff;
	struct passwd	*owner;
	struct group	*grp;

	if (lstat(filename, &buff))
	{
		ft_putstr("stat failed : ");
		ft_putendl(strerror(errno));
		return (-1);
	}
	owner = getpwuid(buff.st_uid);
	grp = getgrgid(buff.st_gid);
	ft_putstr("Nom : ");
	ft_putendl(filename);
	ft_putstr("Modes : ");
	ft_putmodes(filename);
	ft_putstr("Nombre de liens : ");
	ft_putnbr((long)buff.st_nlink);
	ft_putchar('\n');
	ft_putstr("Prorietaire : ");
	ft_putendl(owner->pw_name);
	ft_putstr("Groupe : ");
	ft_putendl(grp->gr_name);
	ft_putstr("Taille : ");
	ft_putnbr((int)buff.st_size);
	ft_putchar('\n');
	ft_putstr("Date de derniere modification : ");
	ft_putstr(ctime((&buff.st_mtimespec.tv_sec)));
	ft_putchar('\n');
	return (0);
}

int		main(int ac, char **av)
{
	if (ac < 2)
		ft_putnbr(11);
	else
	{
		while(ac >= 2)
			ft_inspect_file(av[--ac]);
	}
	return (0);
}*/
