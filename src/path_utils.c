/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:42:47 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/27 18:42:47 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"
#include "ft_string.h"

bool	is_file(const void *d)
{
	struct stat	sta;

	stat(*(char **)d, &sta);
	if (!S_ISDIR(sta.st_mode))
		return (true);
	return (false);
}

bool	is_implied_dir(const char *dir)
{
	return (!ft_strcmp(dir, ".") || !ft_strcmp(dir, ".."));
}

char	*join_dir(const char *src, const char *other)
{
	char	*src_primed;
	char	*ret;

	src_primed = (char *)src;
	if (src[ft_strlen(src) - 1] != '/')
		src_primed = ft_strjoin(src, "/");
	ret = ft_strjoin(src_primed, other);
	if (src != src_primed)
		ft_free(src_primed);
	return (ret);
}
