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
#include <unistd.h>

void	fdump_name(void *a)
{
	const t_file_stated	*fs = (t_file_stated *)a;

	ft_print("%s\n", fs->file);
}

// epoch-utc -> epoch-paris -> Y-M-d-h-m-s
void	fdump_long(void *a)
{
	const t_file_stated	*fs = (t_file_stated *)a;

	dump_stat(fs->s);
	ft_print(" %s", fs->file);
	if (S_ISLNK(fs->s.st_mode))
		dump_link(fs->file, fs->s);
	ft_print("\n");
}
