/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:04:33 by armitite          #+#    #+#             */
/*   Updated: 2025/01/18 15:45:38 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strlen(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

int	ft_doublecheck(char *base, int i)
{
	int	j;

	j = i + 1;
	while (base[j])
	{
		if (base[j] == base[i])
			return (1);
		j++;
	}
	return (0);
}

int	ft_checkbase(char *base)
{
	int	i;
	int	x;
	int	k;

	i = 0;
	k = ft_strlen(base);
	if (k <= 1)
		return (1);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (1);
		x = ft_doublecheck(base, i);
		if (x == 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		i;
	int		len;
	int		k;
	long	nb;

	i = 0;
	len = ft_strlen(base);
	k = ft_checkbase(base);
	nb = nbr;
	if (nb < -2147483648 || nb >= 2147483648)
		return ;
	if (k == 1)
		return ;
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
	}
	if (nb >= len)
	{
		ft_putnbr_base(nb / len, base);
		ft_putnbr_base(nb % len, base);
	}
	else
		ft_putchar(base[nb]);
}
