/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 13:00:08 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/30 13:00:08 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_ls.h"

void	print_help(int fd)
{
	ft_print_fd(fd, "%s:\n", "ft_ls");
	ft_print_fd(fd, "\t-a --all: do not ignore entries starting with .\n");
	ft_print_fd(fd, "\t-R --recursive : list subdirectories recursively\n");
	ft_print_fd(fd, "\t--reverse : reverse order while sorting\n");
	ft_print_fd(fd, "\t-t : sort by time, newest first\n");
	ft_print_fd(fd, "\t-l : use a long listing format\n");
}
