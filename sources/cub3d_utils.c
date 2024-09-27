/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:09:00 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/09/26 15:09:00 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_valid_file(char *path)
{
	if (!access(path, X_OK))
          return(TRUE);
    return (FALSE);
}

void	remove_line_break(char **old_string)
{
	int 	i;
	int		j;
	char	*new_string;

	i = 0;
	j = 0;
	new_string = ft_calloc(ft_strlen(*old_string) + 1, sizeof(char));
	if (!new_string)
		error_handler(5, "Failed calloc\n" , NULL);
	while ((*old_string)[i])
	{
		if ((*old_string)[i] != '\n')
			new_string[j++] = (*old_string)[i];
		i++;
	}
	new_string[j] = '\0';
	free(*old_string);
	*old_string = new_string;
}

int	ft_atoi_cub(const char *nptr)
{
	size_t	i;
	size_t	c;
	size_t	sign;

	c = 0;
	i = 0;
	sign = 1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		c = c * 10 + nptr[i] - '0';
		i++;
	}
	if (nptr[i] != '\0')
		return (-1);
	return (sign * c);
}
