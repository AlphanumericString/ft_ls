/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_dumps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:47:02 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/27 18:47:02 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_string.h"
#include "ft_vector.h"
#include <grp.h>
#include <pwd.h>
#include <stdio.h>

// unix vs gnu block size, 512 vs 1024
// so gnu-ls uses 1024, unix 512 - stat give 512 block ls uses 1024 so /2
void	dirdump_total(t_vector *ve)
{
	int		total;
	size_t	i;

	total = 0;
	i = 0;
	while (i < ve->n_e)
		total += ((struct dirent_stated *)ft_vec_at(ve, i++))->s.st_blocks;
	ft_print("total %d\n", total / 2);
}

// printf("%p\t%25s\t%8lu\t%10lu\t%10lu\t%30s\t%zu\n", (void *)ds, ds->name,
// 	d.d_ino, s.st_mtim.tv_sec, s.st_mtim.tv_nsec, ds->full_name,
// 	s.st_blocks / 2);
void	dump_debug(void *a)
{
	const struct dirent_stated	*ds = (struct dirent_stated *)a;
	const struct dirent			d = ds->d;
	const struct stat			s = ds->s;

	(void)ds;
	(void)d;
	(void)s;
}

void	dirdump_name(void *a)
{
	ft_print("%s\n", ((struct dirent_stated *)a)->name);
}

// epoch-utc -> epoch-paris -> Y-M-d-h-m-s
void	dirdump_long(void *a)
{
	const struct dirent_stated	*ds = (struct dirent_stated *)a;

	dump_stat(ds->s);
	ft_print(" %s", ds->name);
	if (S_ISLNK(ds->s.st_mode))
		dump_link(ds->full_name, ds->s);
	ft_print("\n");
}
