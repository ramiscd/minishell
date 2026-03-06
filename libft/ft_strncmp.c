/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vade-mel <vade-mel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:16:54 by vade-mel          #+#    #+#             */
/*   Updated: 2025/07/21 22:16:59 by vade-mel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	count;
	int				diff;

	count = 0;
	diff = 0;
	while ((count < n) && !diff && (s1[count] != '\0') && (s2[count] != '\0'))
	{
		diff = (unsigned char)s1[count] - (unsigned char)s2[count];
		count++;
	}
	if (count < n && !diff && (s1[count] == '\0' || s2[count] == '\0'))
		diff = (unsigned char)s1[count] - (unsigned char)s2[count];
	return (diff);
}
