/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 11:39:52 by tlebrize          #+#    #+#             */
/*   Updated: 2015/01/15 15:58:54 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"



int			main(int argc, char **argv)
{
	t_args	args;
	t_files	*file;
	t_files	*copy;
	int		i;

	i = ft_count_options(argc, argv);
	args = ft_args(argv);
	file = NULL;
	file = ft_setfiles(file, argc, argv);
	ft_putENOENT(file);
	copy = file;
	if (i + 1 == argc)
		ft_base(".", args);
	if (argc - i > 2)
		args.f = 1;
	while (file != NULL)
	{
		if (file->error == 0)
			ft_base(file->filename, args);
		file = file->next;
	}
	ft_putEACESS(copy);
	return (0);
}

t_files	*ft_setfiles(t_files *file, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc && argv[i][0] == '-')
		i++;
	while (i < argc)
		file = ft_addfile(file, argv[i++]);
	return (file);
}

int		ft_count_options(int argc, char **argv)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (j < argc)
	{
		if (argv[j][0] == '-')
			i++;
		else
			return (i);
		j++;
	}
	return (i);
}

void		ft_fill_args(char **argv, t_args *args, int i)
{
		args->c = 0;
		while (argv[i][args->c + 1] != '-' && argv[i][args->c + 1] != '\0')
		{
			if (argv[i][args->c + 1] == 'l' )
				args->l++;
			else if (argv[i][args->c + 1] == 'R')
				args->R++;
			else if (argv[i][args->c + 1] == 'a')
				args->a++;
			else if (argv[i][args->c + 1] == 'r')
				args->r++;
			else if (argv[i][args->c + 1] == 't')
				args->t++;
			else
				args->e = argv[i][args->c + 1];
			args->c++;
		}
		if (args->e != '\0')
			ft_error_option(args->e);
}

t_args		ft_args(char **argv)
{
	int		i;
	t_args	args;

	i = 1;
	args.l = 0;
	args.R = 0;
	args.a = 0;
	args.r = 0;
	args.t = 0;
	args.f = 0;
	args.e = '\0';
	while (argv[i] != '\0')
	{
		if (argv[i][0] != '-')
			return (args);
		ft_fill_args(argv, &args, i);
		i++;
	}
	return (args);
}
