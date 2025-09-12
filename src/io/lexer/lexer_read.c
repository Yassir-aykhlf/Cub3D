/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:14:56 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/09 10:36:52 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

static int	is_not_null(int c)
{
	return (c && !isspace(c));
}

void	lexer_read_word(t_lexer_state *lexer)
{
	lexer->cursor += push_while(&(lexer->current->u_data.string_data),
			lexer->lines->items[lexer->line_index],
			lexer->cursor,
			is_not_null);
	lexer->current->type = WORD;
}

void	lexer_read_map_line(t_lexer_state *lexer)
{
	lexer->cursor = push_while(&lexer->current->u_data.string_data,
			lexer->lines->items[lexer->line_index],
			0,
			is_valid_map_character);
	lexer->current->type = MAP_LINE;
}

void	lexer_read_number(t_lexer_state *lexer)
{
	int	num;

	num = 0;
	while (lexer_current_char(lexer)
		&& isdigit(lexer_current_char(lexer)))
	{
		num = (num * 10) + (lexer_current_char(lexer) - '0');
		lexer->cursor++;
		if (num > 255)
		{
			lexer->current->u_data.number_data = num;
			lexer->current->type = OVERFLOW_NUMBER;
			return ;
		}
	}
	lexer->current->u_data.number_data = num;
	lexer->current->type = NUMBER;
}

char	lexer_char_at(t_lexer_state *lexer, size_t index)
{
	return (lexer->lines->items[lexer->line_index][index]);
}
