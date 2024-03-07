/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:37:33 by hakobaya          #+#    #+#             */
/*   Updated: 2024/03/08 00:43:24 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/struct.h"

//gcc main.c -lreadline

static void	shell_loop(char *line)
{
	add_history(line);
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	printf("a\n");
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			shell_loop(line);
		free(line);
	}
	exit(0);
}
