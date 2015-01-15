/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/13 19:06:46 by tlebrize          #+#    #+#             */
/*   Updated: 2015/01/15 16:01:39 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <errno.h>
# include <dirent.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <sys/xattr.h>
# include <sys/syslimits.h>
# include "libft.h"

typedef struct			s_args
{
	int					l;
	int					R;
	int					a;
	int					r;
	int					t;
	int					f;
	int					c;
	char				e;
}						t_args;

typedef struct s_list	t_list;
struct					s_list
{
	char				*name;
	char				*path;
	struct stat			stats;
	t_list				*next;
};

typedef struct			s_width
{
	int					links;
	int					owner;
	int					group;
	int					bytes;
	int					major;
	int					minor;
}						t_width;

typedef struct s_files t_files;
struct					s_files
{
	char				filename[PATH_MAX];
	int					error;
	t_files				*next;
};


t_args					ft_args(char **argv);
void					ft_fill_args(char **argv, t_args *args, int i);
void					ft_putmodes(struct stat buff);
t_list					*ft_addlink(t_list *l, char *n, char *p);
void					ft_clearlist(t_list *list);
void					ft_swaplink(t_list *l1, t_list *l2);
void					ft_printlist(t_list *list);
void					ft_long(t_list *list, t_width w);
void					ft_total(t_list *list, t_args args);
int						ft_intlen(int i);
t_list					*ft_bubbles_time(t_list *list, int r);
t_list					*ft_bubbles_lexi(t_list *list, int r);
char					*ft_path(char *base, char *str);
int						ft_base(char *dirpath, t_args args);
void					ft_recursive(t_list *directories, t_args args);
t_width					ft_get_width(t_list *list);
void					ft_display(t_list *list, t_args args);
void					ft_putpath(char *path);
void					ft_majmin(dev_t, t_width w);
void					ft_putnlinks(nlink_t links, int width);
void					ft_putnames(uid_t uid, gid_t gid, t_width width);
void					ft_putblocks(t_list *list, t_width width);
void					ft_puttime(time_t *clock);
void					ft_error_option(char option);
int						ft_count_options(int argc, char **argv);
void					ft_putENOENT(t_files *file);
void					ft_putEACESS(t_files *file);
void					ft_EACESS(char *filename);
t_files					*ft_setfiles(t_files *file, int argc, char **argv);
t_files					*ft_addfile(t_files *file, char *name);
#endif
