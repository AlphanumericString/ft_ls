/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:21:36 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/19 17:21:36 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_string.h"

int	cmp_mtim(const void *a, const void *b)
{
	struct dirent_stated	*ds_a;
	struct dirent_stated	*ds_b;
	const char				*name_a;
	const char				*name_b;

	ds_a = (struct dirent_stated *)a;
	ds_b = (struct dirent_stated *)b;
	name_a = ds_a->name;
	name_b = ds_b->name;
	if (ds_a->s.st_mtim.tv_sec != ds_b->s.st_mtim.tv_sec)
		return (ds_b->s.st_mtim.tv_sec - ds_a->s.st_mtim.tv_sec);
	if (ds_a->s.st_mtim.tv_nsec != ds_b->s.st_mtim.tv_nsec)
		return (ds_b->s.st_mtim.tv_nsec - ds_a->s.st_mtim.tv_nsec);
	return (ft_strcmp(name_a, name_b));
}

int	cmp_names(const void *a, const void *b)
{
	const struct dirent_stated	*ds_a = (struct dirent_stated *)a;
	const struct dirent_stated	*ds_b = (struct dirent_stated *)b;

	return (ft_strcmp(ds_a->name, ds_b->name));
}

int	cmp_sizes(const void *a, const void *b)
{
	struct dirent_stated	*ds_a;
	struct dirent_stated	*ds_b;

	ds_a = (struct dirent_stated *)a;
	ds_b = (struct dirent_stated *)b;
	if (ds_a->s.st_size != ds_b->s.st_size)
		return (ds_b->s.st_size - ds_a->s.st_size);
	return (ft_strcmp(ds_a->name, ds_b->name));
}

int	fsort_alpha(const void *a, const void *b)
{
	const t_file_stated	*fs_a = (t_file_stated *)a;
	const t_file_stated	*fs_b = (t_file_stated *)b;

	return (ft_strcmp(fs_a->file, fs_b->file));
}

int	fsort_mt(const void *a, const void *b)
{
	const t_file_stated	*ds_a;
	const t_file_stated	*ds_b;
	const char			*name_a;
	const char			*name_b;

	ds_a = (t_file_stated *)a;
	ds_b = (t_file_stated *)b;
	name_a = ds_a->file;
	name_b = ds_b->file;
	if (ds_a->s.st_mtim.tv_sec != ds_b->s.st_mtim.tv_sec)
		return (ds_b->s.st_mtim.tv_sec - ds_a->s.st_mtim.tv_sec);
	if (ds_a->s.st_mtim.tv_nsec != ds_b->s.st_mtim.tv_nsec)
		return (ds_b->s.st_mtim.tv_nsec - ds_a->s.st_mtim.tv_nsec);
	return (ft_strcmp(name_a, name_b));
}
