/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 19:03:51 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/26 19:03:51 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_vector.h"
#include "ft_math.h"

#include <stdio.h>

static void do_files(t_ls *ctx)
{
	t_vector *files;

	files = ft_vec_dup(ctx->tagets);
	if (!files)
		return ;
	ft_vec_filter(files, is_file, NULL);
	ft_vec_filterout(ctx->tagets, is_file, NULL);
	handle_files(files, ctx);
	ft_vec_destroy(&files);
}

int	main(int ac, char **av)
{
	t_ls		ctx;
	int			ret;
	size_t		i;

	ret = 0;
	if (parse_opt2(&ctx, ac, av) != 0)
		return (2);
	if (ctx.stop == true)
		return (0);
	if (ft_vec_filterout(ctx.tagets, (t_data_is)is_unreachable, NULL))
		ret = 2;
	do_files(&ctx);
	ft_vec_sort(ctx.tagets, (t_data_cmp)strcmp_sptr);
	if (ctx.order_modifier == LS_OM_reverse)
		ft_vec_reverse(ctx.tagets);
	i = 0;
	while (i < ctx.tagets->n_e)
		ret = ft_max(ls_dir(*(char **)ft_vec_at(ctx.tagets, i++), &ctx), ret);
	return (ft_vec_destroy(&ctx.tagets), ret);
}
