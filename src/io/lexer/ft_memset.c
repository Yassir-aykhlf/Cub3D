/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:52:29 by lazmoud           #+#    #+#             */
/*   Updated: 2025/09/18 11:01:55 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cube.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*mem;

	mem = (unsigned char *)b;
	while (len > 0)
	{
		*(mem++) = (unsigned char)c;
		len--;
	}
	return (b);
}
