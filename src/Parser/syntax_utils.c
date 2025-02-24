
#include "minishell.h"
#include "parsing.h"

// Remove external (single and double) quotes.
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
}
// Expand variables inside double quotes or outside quotes
char	*expand_env_vars(char *input, char **env)
{
int		i;
char	*var;
char	*value;
int		in_single;


}

// expand environment variables, but ignore inside single quotes
void expand_variables(t_token *token, char **env)
{
	char	*expanded;
	int		i;
	int		in_single;

	if (!token || !token->value)
		return;
	i = 0;
	in_single = 0; // flag to verify if inside single quotes
	while (token->value[i])
	{
		if (token->value[i] == '\'')
			in_single = !in_single;
		else if (token->value[i] == '$' && !in_single)
		{
			expanded = expand_env_vars(token->value, env);
		}

	}
}




