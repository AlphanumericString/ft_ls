/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 18:02:27 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/26 18:02:27 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_ls.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_vector.h"
#define UOPTS	"%s: unrecognized option '%s'.\n"
#define UOPTC	"%s: unrecognized option '%c'.\n"
#define TRY_HELP		"Try '%s --help' for more information.\n"

static int	handle_longopt(t_ls *st, char *a)
{
	if (ft_strcmp(a, "--recursive") == 0)
		return (st->recursive = true, 0);
	if (ft_strcmp(a, "--all") == 0)
		return (st->print_range = LS_PR_all, 0);
	if (ft_strcmp(a, "--reverse") == 0)
		return (st->order_modifier = LS_OM_reverse, 0);
	ft_print_fd(STDERR_FILENO, UOPTS TRY_HELP, "ft_ls", a, "ft_ls");
	return (1);
}

static int	handle_shortopt(t_ls *st, char *a)
{
	size_t	i;

	i = 0;
	while (a[++i])
	{
		if (a[i] == 'l')
			st->format_display = LS_FD_all_fields;
		else if (a[i] == 'r')
			st->order_modifier = LS_OM_reverse;
		else if (a[i] == 'R')
			st->recursive = true;
		else if (a[i] == 'a')
			st->print_range = LS_PR_all;
		else if (a[i] == 't')
			st->sort_order = LS_SO_mtime;
		else
			return (ft_print_fd(STDERR_FILENO, UOPTC TRY_HELP, "ft_ls",
					a[i], "ft_ls"), 1);
	}
	return (0);
}

static int	lsinitstate(t_ls *st)
{
	ft_bzero(st, sizeof(t_ls));
	st->tagets = ft_vec_create(sizeof(char *));
	if (!st->tagets || !st->tagets->data)
		return (-1);
	return (0);
}

int	parse_opt2(t_ls *state, int ac, char **av)
{
	static const char	*dflt = "./";
	int					error;
	bool				opt_end;

	ac = 1;
	opt_end = false;
	error = lsinitstate(state);
	while (av[ac] && !error)
	{
		if (av[ac][0] == '-' && av[ac][1] == '-' && av[ac][2] == 0)
			opt_end = true;
		else if (av[ac][0] == '-' && av[ac][1] == '-' && opt_end == false)
			error = handle_longopt(state, av[ac]);
		else if (av[ac][0] == '-' && opt_end == false)
			error = handle_shortopt(state, av[ac]);
		else
			ft_vec_add(state->tagets, &av[ac]);
		ac++;
	}
	if (!state->tagets->n_e)
		ft_vec_add(state->tagets, &dflt);
	return (error);
}
