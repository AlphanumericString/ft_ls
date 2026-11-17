/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_dump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 12:28:13 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/30 12:28:13 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_string.h"

void	dump_date(t_fulldate d)
{
	const char					*months[] = {"", "Jan", "Feb", "Mar", "Apr",
		"May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	static char					hm_str[6];

	hm_str[0] = (d.hour / 10) + '0';
	hm_str[1] = (d.hour % 10) + '0';
	hm_str[2] = ':';
	hm_str[3] = (d.min / 10) + '0';
	hm_str[4] = (d.min % 10) + '0';
	hm_str[5] = 0;
	ft_print("%s %d %s", months[d.month], d.day, hm_str);
}
