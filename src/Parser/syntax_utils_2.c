
#include "minishell.h"
#include "parsing.h"

static void	init_vars(int *i, int *j, int *in_single,
						int *in_double)
{
	*i = 0;
	*j = 0;
	*in_single = 0;
	*in_double = 0;
}
// 
static char *remove_inner_quotes(char *input)
{
	int		i;
	int		j;
	int		in_single;
	int		in_double;
	char	*new_str;

	if (!input)
		return (NULL);
	new_str = malloc(ft_strlen(input) + 1);
	if (!new_str)
		return (NULL);
	init_vars(&i, &j, &in_single, &in_double);
	while (input[i])
	{
		if (input[i] == '\'' && !in_double) // Single quotes toggle
			in_single = !in_single;
		else if (input[i] == '"' && !in_single) // Double quotes toggle
			in_double = !in_double;
		else
			new_str[j++] = input[i]; // Copy character normally
		i++;
	}
	new_str[j] = '\0';
	free(input); // Free the original input
	return (new_str);
}

// Removal of the external quotes (single and double)
void	remove_external_quotes(t_token *token)
{
	char	*new_value;
	int		len;

	if (!token || !token->value)
		return;
	len = ft_strlen(token->value);
	if ((token->value[0] == '"' && token->value[len - 1] == '"')
		|| (token->value[0] == '\'' && token->value[len - 1] == '\''))
	{
		new_value = ft_substr(token->value, 1, len - 2);
		free(token->value);
		token->value = new_value;
	}
	// now call `remove_inner_quotes()` after removing external ones
	token->value = remove_inner_quotes(token->value);
}
