
#include "minishell.h"
#include "parsing.h"

// The replacement of the origina str from input to the value of ENV-VAR
char	*replace_var(char *input, char *var, char *value, int pos)
{
	char	*before;
	char	*after;
	char	*new_str;
	char	*final_str;
	int		var_len;

	var_len = ft_strlen(var);
	before = ft_substr(input, 0, pos);
	after = ft_strdup(input + pos + var_len + 1);
	if (!before || !after) // Handle memory failure
		return (NULL);
	if (value) // Normal case: Replace with value
		new_str = ft_strjoin(before, value);
	else // If value is NULL, just remove the $VAR
		new_str = ft_strdup(before);
	free(before);
	final_str = ft_strjoin(new_str, after);
	free(input);
	//here only assign a string to the LOCAL input variable
	//input = ft_strjoin(new_str, after);
	free(new_str);
	free(after);
	return (final_str);
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
	//printf(MAG"tok val after removal = %s\n"RESET, token->value); // TO DEBUG
}
