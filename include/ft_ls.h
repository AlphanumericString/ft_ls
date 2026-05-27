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

#include "types/ft_vector_types.h"
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>

struct dirent_stated {
    struct dirent   d;
    struct stat		s;
    char            *name;
    char            *full_name;
};

typedef struct file_stated {
	char		*file;
	struct stat	s;
} t_file_stated;

enum e_pr {
	LS_PR_only_visibles = 0,
	LS_PR_all,
};

enum e_fd {
	LS_FD_names = 0,
	LS_FD_all_fields,
};

enum e_so {
	LS_SO_alpha = 0,
	LS_SO_mtime,
};

enum e_om {
	LS_OM_none = 0,
	LS_OM_reverse,
};

typedef struct s_ls_state2 {
	enum e_pr	print_range;
	bool		recursive;
	enum e_fd	format_display;
	enum e_so	sort_order;
	enum e_om	order_modifier;
	t_vector	*tagets;
	bool		files_section;
} t_ls;

typedef struct s_fulldate {
  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
} t_fulldate;

// dumpers.
void	dump_debug(void *a);
void	dirdump_name(void *a);
void	dirdump_long(void *a);
void	dirdump_total(t_vector *ve);
void	fdump_name(void *a);
void	fdump_long(void *a);

// utils - dir
bool		is_file(const void *d);
char		*join_dir(const char *src, const char *other);
bool		is_implied_dir(const char *dir);
// utils - time
t_fulldate	epoch_to_date(long t);
// utils
void		setperm_string(char *perms, unsigned int mode);
void		clear_entries(void *a);
bool		is_unreachable(void *a);
int			strcmp_sptr(void *a, void *b);

// parse_opt
int			parse_opt2(t_ls *state, int ac, char **av);

// comparators.
int	cmp_names(const void *a, const void *b);
int	cmp_sizes(const void *a, const void *b);
int	cmp_mtim(const void *a, const void *b);
int	fsort_alpha(const void *a, const void *b);
int	fsort_mt(const void *a, const void *b);

// cores
int ls_dir(const char *dir, const t_ls *ctx);
int	handle_files(t_vector *files, t_ls st);
