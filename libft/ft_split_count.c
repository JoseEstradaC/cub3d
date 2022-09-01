/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestrada <jestrada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:27:22 by jestrada          #+#    #+#             */
/*   Updated: 2022/09/01 20:52:52 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_split_count(char **split)
{
	int	size;

	size = 0;
	if (!split)
		return (0);
	while (*split)
	{
		size++;
		split++;
	}
	return (size);
}
