#include "minishell.h"

char	*single_quote_removal(char *str)
{
	char	*start;

	str++;
	start = str;
	while (*str && !(is_single_quote(*str)))
		str++;
	if (is_single_quote(*str))
		return (strndup(start, str - start));
	else
		return (NULL);
}

char	*double_quote_removal(char *str)
{
	char	*start;

	str++;
	start = str;
	while (*str && !(is_double_quote(*str)))
		str++;
	if (is_double_quote(*str))
		return (strndup(start, str - start));
	else
		return (NULL);
}
