/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_loggers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:09:26 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/09 10:36:52 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	log_system_error(const char *resource)
{
	char	*error;

	error = strerror(errno);
	if (error)
	{
		if (resource)
			printf(ERR_HEADER"./Cub3d: %s: %s\n", resource, error);
		else
			printf(ERR_HEADER"./Cub3d: %s\n", error);
	}
}

int	log_missing(const char *missing_label)
{
	printf(ERR_HEADER"%s is actually missing,"
		" please add up this configuration "
		"field before trying to use the config.\n",
		missing_label);
	return (CUBE_FAILURE);
}

int	log_duplication_error(const char *duplication_label)
{
	printf(ERR_HEADER"Duplicated %ss are not allowed, please use one %s\n",
		duplication_label,
		duplication_label);
	return (CUBE_FAILURE);
}

int	throw_error_on_failure(const char *element,
	t_game *game,
	t_lexer_state *lexer,
	int (*proc)(t_game *, t_lexer_state *))
{
	int	code;

	code = CUBE_SUCCESS;
	if (!proc)
	{
		printf(ERR_HEADER"Unknown identifier: `%s`\n", element);
		code = (CUBE_FAILURE);
	}
	else
	{
		code = proc(game, lexer);
		if (code != CUBE_SUCCESS)
		{
			printf(ERR_HEADER"Failed to parse %s\n",
				element);
		}
	}
	return (code);
}

int	log_map_not_enclosed(void)
{
	printf(ERR_HEADER"Map is not properly enclosed by walls. "
		"Player can escape to undefined areas.\n");
	return (CUBE_FAILURE);
}
