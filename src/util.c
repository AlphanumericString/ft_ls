/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:40:44 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/26 14:40:44 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

#include "ft_mem.h"
#include "ft_ls.h"
#include "ft_string.h"

int	strcmp_sptr(void *a, void *b)
{
	return (ft_strcmp(*(char **)a, *(char **)b));
}

static void	first_char(char *perms, unsigned int mode)
{
	if (S_ISREG(mode))
		perms[0] = '-';
	else if (S_ISDIR(mode))
		perms[0] = 'd';
	else if (S_ISLNK(mode))
		perms[0] = 'l';
	else if (S_ISCHR(mode))
		perms[0] = 'c';
	else if (S_ISBLK(mode))
		perms[0] = 'b';
	else if (S_ISFIFO(mode))
		perms[0] = 'p';
	else if (S_ISSOCK(mode))
		perms[0] = 's';
}

void	setperm_string(char *perms, unsigned int mode)
{
	first_char(perms, mode);
	ft_memset(perms + 1, '-', 3 * 3);
	if (mode & S_IRUSR)
		perms[1 + 0] = 'r';
	if (mode & S_IWUSR)
		perms[2 + 0] = 'w';
	if (mode & S_IXUSR)
		perms[3 + 0] = 'x';
	if (mode & S_IRGRP)
		perms[1 + 3] = 'r';
	if (mode & S_IWGRP)
		perms[2 + 3] = 'w';
	if (mode & S_IXGRP)
		perms[3 + 3] = 'x';
	if (mode & S_IROTH)
		perms[1 + 6] = 'r';
	if (mode & S_IWOTH)
		perms[2 + 6] = 'w';
	if (mode & S_IXOTH)
		perms[3 + 6] = 'x';
	perms[10] = 0;
}

void	clear_entries(void *a)
{
	struct dirent_stated	*ds;

	ds = (struct dirent_stated *)a;
	ft_free(ds->full_name);
	ft_free(ds->name);
}

bool	is_unreachable(void *a)
{
	struct stat	s;

	if (stat(*(char **)a, &s) == -1)
		return (ft_print_fd(STDERR_FILENO,
				"%s: cannot access '%s': %m\n", "ft_ls", *(char **)a),
			1);
	return (0);
}
