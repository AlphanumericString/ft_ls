/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:19:35 by bgoulard          #+#    #+#             */
/*   Updated: 2026/03/11 13:19:35 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <dirent.h>
#include <sys/stat.h>

struct dirent_stated {
    struct dirent    d;
    struct stat        s;
    char            *name;
    char            *full_name;
};


void    dump_dirent(void *a);
void    dump_only_name(void *a);
void    clear_entries(void *a);
int        cmp_mtim(const void *a, const void *b);
