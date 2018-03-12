/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:36:17 by pde-rent          #+#    #+#             */
/*   Updated: 2018/03/09 12:46:24 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		fmt_hd(t_param *p)
{
	short	d;
	int		ret;

	ret = 0;
	d = va_arg(p->va, int);
	if (!(p->precision) && d == 0)
		return (print_spaces(p));
	if (p->flags[LEFT])
		ret += print_d(d, p);
	if ((!p->flags[ZPAD] || p->flags[LEFT] || p->precision) && p->padding)
		while (p->padding-- > (p->flags[PLUS] || p->flags[SPACE])
				+ (d < 0 && p->precision > len_int(ABS(d), 10)) +
				(p->precision > len_int(d, 10) ? p->precision : len_int(d, 10))
				&& ret++)
			pchar(32);
	if (!p->flags[LEFT])
		ret += print_d(d, p);
	return (ret);
}

int		fmt_ho(t_param *p)
{
	unsigned short	o;
	int				ret;

	ret = 0;
	o = va_arg(p->va, int);
	if (!(p->precision) && o == 0 && !p->flags[HASH])
		return (print_spaces(p));
	if (p->flags[LEFT])
		ret += print_o(o, p);
	if (p->flags[ZPAD] && !p->precision && !p->flags[LEFT])
		while (p->padding-- > len_int(o, 8) && ret++)
			pchar('0');
	while (p->padding-- > (p->flags[HASH] && o != 0) +
			(p->precision > len_int(o, 8) ? p->precision : len_int(o, 8))
			&& ret++)
		pchar(32);
	if (!p->flags[LEFT])
		ret += print_o(o, p);
	return (ret);
}

int		fmt_hu(t_param *p)
{
	unsigned short	u;
	int				ret;

	ret = 0;
	u = va_arg(p->va, int);
	if (!(p->precision) && u == 0)
		return (print_spaces(p));
	if (p->flags[LEFT])
		ret += print_u(u, p);
	while (p->padding-- > (p->precision > len_uint(u, 10) ?
				p->precision : len_uint(u, 10))
			&& ret++)
		pchar(32);
	if (!p->flags[LEFT])
		ret += print_u(u, p);
	return (ret);
}

int		fmt_hx(t_param *p)
{
	unsigned short	x;
	int				ret;
	int				ln;

	ret = 0;
	x = va_arg(p->va, int);
	if (!(p->precision) && x == 0)
		return (print_spaces(p));
	ln = (p->precision > len_uint(x, 16)) ? p->precision : len_uint(x, 16)
		+ 2 * (p->flags[HASH] && x != 0);
	if (p->flags[LEFT])
		ret += print_x(x, p);
	if (p->flags[ZPAD] && !p->precision && !p->flags[LEFT])
		while (p->padding-- > ln && ret++)
			pchar('0');
	while (!p->flags[ZPAD] && p->padding-- > ln && ret++)
		pchar(32);
	if (!p->flags[LEFT])
		ret += print_x(x, p);
	return (ret);
}

int		fmt_hbx(t_param *p)
{
	unsigned short	x;
	int				ret;
	int				ln;

	ret = 0;
	x = va_arg(p->va, int);
	if (!(p->precision) && x == 0)
		return (print_spaces(p));
	ln = (p->precision > len_uint(x, 16)) ? p->precision : len_uint(x, 16)
		+ 2 * (p->flags[HASH] && x != 0);
	if (p->flags[LEFT])
		ret += print_bx(x, p);
	if (p->flags[ZPAD] && !p->precision && !p->flags[LEFT])
		while (p->padding-- > ln && ret++)
			pchar('0');
	while (!p->flags[ZPAD] && p->padding-- > ln && ret++)
		pchar(32);
	if (!p->flags[LEFT])
		ret += print_bx(x, p);
	return (ret);
}
