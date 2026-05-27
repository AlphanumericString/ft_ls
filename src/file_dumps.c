/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_dumps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:47:34 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/27 18:47:34 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_string.h"
#include <grp.h>
#include <pwd.h>
#include <stdio.h>

void	fdump_name(void *a)
{
	const t_file_stated	*fs = (t_file_stated *)a;

	ft_print("%s\n", fs->file);
}

// epoch-utc -> epoch-paris -> Y-M-d-h-m-s
void	fdump_long(void *a)
{
	const char			*months[] = {"", "Jan", "Feb", "Mar", "Apr", "May",
		"Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	const t_file_stated	*fs = (t_file_stated *)a;
	char				access_string[11];
	t_fulldate			d;

	access_string[10] = 0;
	setperm_string(access_string, fs->s.st_mode);
	d = epoch_to_date(fs->s.st_mtim.tv_sec + 3600 * 2);
	printf("%s %zu %s %s %5zu %s %d %02d:%02d %s\n", access_string,
		fs->s.st_nlink, getpwuid(fs->s.st_uid)->pw_name,
		getgrgid(fs->s.st_gid)->gr_name, fs->s.st_size, months[d.month],
		d.day, d.hour, d.min, fs->file);
}
