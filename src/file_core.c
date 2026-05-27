/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:13:47 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/27 17:13:47 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_vector.h"
#include <stdio.h>

	// sort order
static void	f_so(t_vector *stated, t_ls st)
{
	ft_vec_sort(stated, fsort_alpha);
	if (st.sort_order == LS_SO_mtime)
		ft_vec_sort(stated, fsort_mt);
}

	// order modify
static void	f_om(t_vector *stated, t_ls st)
{
	if (st.order_modifier == LS_OM_reverse)
		ft_vec_reverse(stated);
}

	// format display
static void	f_fd(t_vector *stated, t_ls st)
{
	if (st.format_display == LS_FD_all_fields)
		ft_vec_apply(stated, fdump_long);
	else
		ft_vec_apply(stated, fdump_name);
}

int	handle_files(t_vector *files, t_ls st)
{
	t_vector		*stated;
	size_t			i;
	t_file_stated	*fst;

	if (!files || !files->n_e)
		return (0);
	st.files_section = true;
	stated = ft_vec_create(sizeof(t_file_stated));
	if (!stated || !ft_vec_reserve(stated, files->n_e))
		return (ft_vec_destroy(&stated), 2);
	stated->n_e = files->n_e;
	i = 0;
	while (i < files->n_e)
	{
		fst = ((t_file_stated *)ft_vec_at(stated, i));
		fst->file = *(char **)ft_vec_at(files, i++);
		stat(fst->file, &fst->s);
	}
	f_so(stated, st);
	f_om(stated, st);
	f_fd(stated, st);
	return (ft_vec_destroy(&stated), 0);
}
