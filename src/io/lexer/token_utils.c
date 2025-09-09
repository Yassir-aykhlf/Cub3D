/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:53:02 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/08/21 15:01:41 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_token(t_token *token)
{
	memset(token, 0, sizeof(*token));
	token->u_data.number_data = 0;
	token->u_data.string_data.size = 0;
	token->u_data.string_data.cap = 0;
	token->u_data.string_data.items = NULL;
}

/*
 * tmp_ for debugging purposes
 */
void	tmp_print_token(t_token *token)
{
	if (token->type == MAP_LINE)
		printf("MAP_LINE: %s\n", token->u_data.string_data.items);
	else if (token->type == WORD)
		printf("WORD: %s\n", token->u_data.string_data.items);
	else if (token->type == NUMBER)
		printf("NUMBER: %d\n", token->u_data.number_data);
	else if (token->type == SEPARATOR)
		printf("SEPARATOR: %c\n", COMA);
	else if (token->type == EOL)
		printf("EOL\n");
	else if (token->type == EOF_)
		printf("EOF\n");
	else
		printf("UNKNOWN TOKEN TYPE\n");
}

void	cleanup_token(t_token *token)
{
	if (token->type == WORD || token->type == MAP_LINE)
	{
		if (token->u_data.string_data.items)
		{
			free(token->u_data.string_data.items);
			token->u_data.string_data.items = NULL;
		}
	}
	init_token(token);
}
