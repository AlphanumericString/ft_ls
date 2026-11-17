/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:13:47 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/27 17:13:47 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_math.h"
#include "ft_string.h"
#include "ft_vector.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

#define CANT_OPEN	 "%s: cannot open directory '%s': %m"

static void	st_files(struct dirent_stated *ds, t_vector *vec, const char *dir)
{
	ds->full_name = join_dir(dir, ds->d.d_name);
	ds->name = ft_strdup(ds->d.d_name);
	if (lstat(ds->full_name, &ds->s) >= 0)
	{
		ft_vec_add(vec, ds);
		return ;
	}
	ft_print_fd(STDERR_FILENO, "%s: could not read '%s': %m\n", "ft_ls",
		ds->full_name);
	clear_entries(ds);
}

static t_vector	*collect_entries(const char *dir, const t_ls *ctx)
{
	DIR						*d;
	struct dirent			*d_entry;
	struct dirent_stated	ds;
	t_vector				*vec_entries;

	d = opendir(dir);
	if (!d)
		return (ft_print_fd(STDERR_FILENO, CANT_OPEN, "ft_ls", dir), NULL);
	vec_entries = ft_vec_create(sizeof(struct dirent_stated));
	d_entry = readdir(d);
	while (d_entry != NULL && vec_entries)
	{
		ds.d = *d_entry;
		if (!(ds.d.d_name[0] == '.' && ctx->print_range != LS_PR_all))
			st_files(&ds, vec_entries, dir);
		d_entry = readdir(d);
	}
	return (closedir(d), vec_entries);
}

static void	sort_entries(t_vector *entries, const t_ls *ctx)
{
	if (ctx->sort_order == LS_SO_mtime)
		ft_vec_sort(entries, cmp_mtim);
	else
		ft_vec_sort(entries, cmp_names);
	if (ctx->order_modifier == LS_OM_reverse)
		ft_vec_reverse(entries);
}

static void	dump_entries(t_vector *vec_entries, const t_ls *ctx)
{
	if (ctx->format_display == LS_FD_all_fields)
	{
		dirdump_total(vec_entries);
		ft_vec_apply(vec_entries, dirdump_long);
	}
	else
		ft_vec_apply(vec_entries, dirdump_name);
}

int	ls_dir(const char *dir, const t_ls *ctx)
{
	t_vector				*vec_entries;
	static int				i = 0;
	struct dirent_stated	*ds;
	int						rets;
	size_t					j;

	vec_entries = collect_entries(dir, ctx);
	if (!vec_entries)
		return (2);
	if (i++ > 0 || ctx->files_section)
		ft_print("\n");
	if (ctx->tagets->n_e > 1 || ctx->recursive || ctx->files_section)
		ft_print("%s:\n", dir);
	sort_entries(vec_entries, ctx);
	dump_entries(vec_entries, ctx);
	rets = 0;
	j = 0;
	while (ctx->recursive == true && j < vec_entries->n_e)
	{
		ds = (struct dirent_stated *)ft_vec_at(vec_entries, j++);
		if (S_ISDIR(ds->s.st_mode) && !is_implied_dir(ds->name))
			rets += ls_dir(ds->full_name, ctx);
	}
	return (ft_vec_apply(vec_entries, clear_entries),
		ft_vec_destroy(&vec_entries), ft_min(rets, 1));
}
