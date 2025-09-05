/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_game_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 09:34:59 by lazmoud           #+#    #+#             */
/*   Updated: 2025/08/21 15:01:41 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	handle_identifier(t_game *game, t_lexer_state *lexer, t_token *store)
{
	int			(*procedure)(t_game *, t_lexer_state *);
	const char	*id;

	id = store->u_data.string_data.items;
	procedure = NULL;
	if (strcmp(id, "F") == 0)
		procedure = parse_floor_color;
	else if (strcmp(id, "C") == 0)
		procedure = parse_ceiling_color;
	else if (strcmp(id, "NO") == 0)
		procedure = parse_north_texture;
	else if (strcmp(id, "SO") == 0)
		procedure = parse_south_texture;
	else if (strcmp(id, "WE") == 0)
		procedure = parse_west_texture;
	else if (strcmp(id, "EA") == 0)
		procedure = parse_east_texture;
	return (throw_error_on_failure(id, game, lexer, procedure));
}

int	process_token(t_game *game, t_lexer_state *lexer, t_token *token)
{
	int		code;

	if (token->type == WORD)
	{
		code = handle_identifier(game, lexer, token);
		if (code != CUBE_SUCCESS)
		{
			cleanup_token(token);
			return (code);
		}
	}
	else if (token->type == MAP_LINE)
	{
		if (parse_map(game, lexer, token) == CUBE_FAILURE)
			return (CUBE_FAILURE);
	}
	return (CUBE_SUCCESS);
}

int	parse_game_config(t_game *game, t_lexer_state *lexer)
{
	t_token	token;

	init_token(&token);
	while (1)
	{
		cleanup_token(&token);
		get_next_token(lexer, &token);
		if (token.type == EOF_)
			break ;
		if (process_token(game, lexer, &token) != CUBE_SUCCESS)
		{
			cleanup_token(&token);
			return (CUBE_FAILURE);
		}
	}
	print_parsed_config(game);
	return (CUBE_SUCCESS);
}
