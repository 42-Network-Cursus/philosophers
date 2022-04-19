/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:48:50 by cwastche          #+#    #+#             */
/*   Updated: 2022/03/16 09:48:54 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_overflow(char *str)
{
	int	i;

	i = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		i++;
		str++;
	}
	if (i > 19)
		return (1);
	else
		return (0);
}

static int	ft_check_res(unsigned long long int res, int sign)
{
	if (res == MAX_LONG && sign == -1)
		return (1);
	else if (res > MAX_LONG && sign == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	res;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (invalid_input(str))
		return
	if (ft_overflow((char *)str))
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10 + *str++ - '0';
	if ((res == MAX_LONG && !(*str)) || res > MAX_LONG)
		return (ft_check_res(res, sign));
	return ((int)res * sign);
}
