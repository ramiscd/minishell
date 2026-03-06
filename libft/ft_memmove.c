/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:28:47 by vade-mel          #+#    #+#             */
/*   Updated: 2025/08/07 23:20:20 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*dest;

	tmp = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (tmp == dest || n == 0)
		return (dst);
	if (tmp < dest)
	{
		while (n)
		{
			dest[n - 1] = tmp[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest, tmp, n);
	return (dst);
}
