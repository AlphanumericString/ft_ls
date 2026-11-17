/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_dump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 12:15:38 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/30 12:15:38 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_string.h"
#include "ft_ls.h"
#include <unistd.h>

void	dump_link(const char *name, struct stat s)
{
	char	*to_print;
	char	link[PATH_MAX + 1];
	ssize_t	r;

	ft_print(" -> ");
	if (s.st_size < PATH_MAX)
		to_print = link;
	else
		to_print = malloc(sizeof(char) * s.st_size + 1);
	if (!to_print)
		return ;
	r = readlink(name, to_print, ft_max(PATH_MAX, s.st_size));
	if (r >= 0)
		to_print[r] = 0;
	else
		to_print[0] = 0;
	ft_print("%s", to_print);
	if (to_print != link)
		free(to_print);
}
