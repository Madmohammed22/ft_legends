#include <stdio.h>

int	main(void)
{
	const char	*reset = "\033[0m";
	const char	*red = "\033[31m";
	const char	*green = "\033[32m";
	const char	*yellow = "\033[33m";
	const char	*blue = "\033[34m";
	const char	*magenta = "\033[35m";
	const char	*cyan = "\033[36m";

	// ANSI escape code to reset all attributes
	// ANSI escape codes for different colors
	// Printing text in different colors
	printf("%sThis text is red.%s\n", red, reset);
	printf("%sThis text is green.%s\n", green, reset);
	printf("%sThis text is yellow.%s\n", yellow, reset);
	printf("%sThis text is blue.%s\n", blue, reset);
	printf("%sThis text is magenta.%s\n", magenta, reset);
	printf("%sThis text is cyan.%s\n", cyan, reset);
	return (0);
}
