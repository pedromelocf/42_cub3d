/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:12:37 by jovicto2          #+#    #+#             */
/*   Updated: 2024/11/20 15:12:41 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_file(char	*file)
{
	int	fd;

    fd = open(file, O_DIRECTORY);
    if (fd >= 0)
    {
    	close(fd);
		handle_error(MSG_INV_FILE_DIR);
    }
	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error(MSG_INV_FILE_OPEN);
	close(fd);
	if (!ft_strnstr(file, ".cub", ft_strlen(file)))
		handle_error(MSG_INV_FILE_EXT_CUB);
	//TODO: check if .cub before extension (example: .cube .cub.txt .cub cub.42)
}

bool	is_valid_png(char *file)
{
    int	fd;

    fd = open(file, O_DIRECTORY);
    if (fd >= 0)
    {
        close(fd);
        return (false);
    }
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (false);
    close(fd);
    if (!ft_strnstr(file, ".png", ft_strlen(file)))
        return (false);
    return (true);
}

bool	is_valid_color_tag(char *line)
{
	char    **split;
    char    **init;

    if (!line)
        return (true);
    split = ft_split(line, ',');
    init = split;
    while (*split)
    {
        if (!ft_isdigit(**split))
        {
           	ft_for_each((void **)init, free);
            free(init);
            return (false);
        }
        if (ft_atoi(*split) < 0 || ft_atoi(*split) > 255)
        {
            ft_for_each((void **)init, free);
            free(init);
            return (false);
        }
        split++;
    }
    ft_for_each((void **)init, free);
    free(init);
    return (true);
}

bool    is_valid_map(t_list *list)
{
  	t_list	*lines;

    lines = list;
    while (lines)
    {
		if (is_empty_line(lines->content))
	        return (false);
        lines = lines->next;
    }
    return (true);
}

bool	is_empty_line(char *line)
{
    while (*line && ft_strchr(BLANK_CHARS, *line))
		line++;
	return (!*line);
}