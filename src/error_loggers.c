/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_loggers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:13:26 by lazmoud           #+#    #+#             */
/*   Updated: 2025/08/22 20:25:41 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	print_error_header(void)
{
	printf("Error\n");
}

int	log_missing(const char *missing_label)
{
	print_error_header();
	printf("%s is actually missing,"
		" please add up this configuration "
		"field before trying to use the config.\n",
		missing_label);
	return (CUBE_FAILURE);
}

int	log_duplication_error(const char *duplication_label)
{
	print_error_header();
	printf("Duplicated %ss are not allowed, please use one %s\n",
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
		print_error_header();
		printf("Unknown identifier: `%s`\n", element);
		code = (CUBE_FAILURE);
	}
	else
	{
		code = proc(game, lexer);
		if (code != CUBE_SUCCESS)
		{
			print_error_header();
			printf("Failed to parse %s\n",
				element);
		}
	}
	return (code);
}

int	log_map_not_enclosed(void)
{
	print_error_header();
	printf("Map is not properly enclosed by walls. "
		"Player can escape to undefined areas.\n");
	return (CUBE_FAILURE);
}
