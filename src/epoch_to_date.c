/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoch_to_date.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:26:03 by bgoulard          #+#    #+#             */
/*   Updated: 2026/05/19 17:26:03 by bgoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_mem.h"

static void	set_smh(t_fulldate *d, long *t)
{
	d->sec = *t % 60;
	*t /= 60;
	d->min = *t % 60;
	*t /= 60;
	d->hour = *t % 24;
}

static void	set_years(t_fulldate *d, long hours, bool *is_leap)
{
	long	total_days;
	long	year_iterator;
	int		lenght_of_year;

	year_iterator = 1970;
	lenght_of_year = 365;
	total_days = hours / 24;
	while (total_days >= lenght_of_year)
	{
		total_days -= lenght_of_year;
		*is_leap = ((year_iterator % 4 == 0 && year_iterator % 100 != 0)
				|| (year_iterator % 400 == 0));
		lenght_of_year = 365;
		if (*is_leap)
			lenght_of_year++;
		year_iterator++;
	}
	d->year = year_iterator;
	d->day = total_days;
}

// +1 at the end to make 0th month 0th day into -> jan 1st
t_fulldate	epoch_to_date(long t)
{
	const int	mdays_src[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,
		31};
	int			mdays[12];
	bool		is_leap;
	t_fulldate	d;

	is_leap = false;
	set_smh(&d, &t);
	set_years(&d, t, &is_leap);
	ft_memcpy(mdays, mdays_src, 12 * sizeof(*mdays));
	if (is_leap)
		mdays[1] = 29;
	d.month = 0;
	while (d.day >= mdays[d.month])
	{
		d.day -= mdays[d.month];
		d.month++;
	}
	d.day += 1;
	d.month += 1;
	return (d);
}
