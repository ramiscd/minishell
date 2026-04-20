/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 21:07:37 by vade-mel          #+#    #+#             */
/*   Updated: 2025/08/01 21:14:11 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;

	dst = (char *)malloc(ft_strlen(src) + 1);
	if (!(dst))
		return (0);
	ft_memcpy(dst, src, ft_strlen(src) + 1);
	return (dst);
}
