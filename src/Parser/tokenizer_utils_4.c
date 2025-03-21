#include "minishell.h"
#include "parsing.h"

// Appends the string 'segment' to 'result' by concatenating them,
// frees the memory allocated for both 'result' and 'segment',
// and returns the newly allocated concatenated string.
char	*append_segment(char *result, char *segment)
{
	char	*temp;

	temp = ft_strjoin(result, segment);
	free(result);
	free(segment);
	return (temp);
}
