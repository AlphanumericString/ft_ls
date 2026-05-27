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

void	dump_debug(void *a)
{
	const struct dirent_stated	*ds = (struct dirent_stated *)a;
	const struct dirent			d = ds->d;
	const struct stat			s = ds->s;

	printf("%p\t%25s\t%8lu\t%10lu\t%10lu\t%30s\t%zu\n", (void *)ds, ds->name,
		d.d_ino, s.st_mtim.tv_sec, s.st_mtim.tv_nsec, ds->full_name,
		s.st_blocks / 2);
}

void	dirdump_name(void *a)
{
	const struct dirent_stated	*ds = (struct dirent_stated *)a;

	ft_print("%s\n", ds->name);
}

// epoch-utc -> epoch-paris -> Y-M-d-h-m-s
void	dirdump_long(void *a)
{
	const char					*months[] = {"", "Jan", "Feb", "Mar", "Apr",
		"May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	const struct dirent_stated	*ds = (struct dirent_stated *)a;
	char						access_string[11];
	t_fulldate					d;

	access_string[10] = 0;
	setperm_string(access_string, ds->s.st_mode);
	d = epoch_to_date(ds->s.st_mtim.tv_sec + 3600 * 2);
	printf("%s %zu %s ", access_string, ds->s.st_nlink,
		getpwuid(ds->s.st_uid)->pw_name);
	printf("%s %5zu %s ", getgrgid(ds->s.st_gid)->gr_name, ds->s.st_size,
		months[d.month]);
	printf("%d %02d:%02d", d.day, d.hour, d.min);
	ft_print(" %s\n", ds->name);
}
