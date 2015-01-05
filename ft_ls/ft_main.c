/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 11:39:52 by tlebrize          #+#    #+#             */
/*   Updated: 2014/12/17 20:00:49 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, char **argv)
{
	t_args	args;
	int		i;
	int		j;

	i = 1;
	j = 1;
	args = ft_args(argv);
	while (argv[j] != '\0')
	{
		if (argv[i][0] == '-')
			i++;
		j++;
	}
	if (i == j)
		ft_base(".", args);
	if (i + 1 == j)
		args.f = 1;
	while (i < argc)
	{
		ft_base(argv[i++], args);
		if (i != argc)
			ft_putchar('\n');
	}
	return (0);
}

t_args		ft_args(char **argv)
{
	int		i;
	int		j;
	t_args	args;

	i = 1;
	args.l = 0;
	args.R = 0;
	args.a = 0;
	args.r = 0;
	args.t = 0;
	args.f = 0;
	while (argv[i] != '\0')
	{
		j = 1;
		if (argv[i][0] != '-')
			return (args);
		while (argv[i][j] != '\0')
		{
			args.l = argv[i][j] == 'l' ? args.l + 1 : args.l;
			args.R = argv[i][j] == 'R' ? args.R + 1 : args.R;
			args.a = argv[i][j] == 'a' ? args.a + 1 : args.a;
			args.r = argv[i][j] == 'r' ? args.r + 1 : args.r;
			args.t = argv[i][j] == 't' ? args.t + 1 : args.t;
			j++;
		}
		i++;
	}
	return (args);
}

