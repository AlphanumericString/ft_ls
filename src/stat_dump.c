/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_dump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 12:32:34 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/30 12:32:34 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_defs.h"
#include "ft_string.h"
#include "ft_ls.h"
#include <grp.h>
#include <pwd.h>

void	dump_stat(struct stat s)
{
	t_fulldate	d;
	char		access_string[11];
	char		nmbs[32];

	access_string[10] = 0;
	setperm_string(access_string, s.st_mode);
	ft_print("%s ", access_string);
	nmbs[0] = 0;
	ft_stopa_base(s.st_nlink, FT_DECBASE, nmbs, 32);
	ft_print("%s ", nmbs);
	ft_print("%s %s ", getpwuid(s.st_uid)->pw_name,
		getgrgid(s.st_gid)->gr_name);
	nmbs[0] = 0;
	ft_stopa_base(s.st_size, FT_DECBASE, nmbs, 32);
	ft_print("%s ", nmbs);
	d = epoch_to_date(s.st_mtim.tv_sec + 3600 * 2);
	dump_date(d);
}
