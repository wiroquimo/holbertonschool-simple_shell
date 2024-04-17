#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * print_error - prints error
 * @str: message error to print
 *
 * Return: error code
*/
int print_error(char *str)
{
	perror(str);

	return (1);
}

/**
 * main - Entry point
 *
 * Return: 0 on sucess, 1 on fail
*/
int main(void)
{
	pid_t new_process;
	int status;
	ssize_t readed_bytes;
	char *buffer = NULL, *argv[2];
	size_t bufsize = 1024;

	buffer = malloc(sizeof(char) * bufsize);
	if (!buffer)
		return (print_error("Buffer error"));

	printf("#cisfun$ ");
	readed_bytes = getline(&buffer, &bufsize, stdin);
	if (readed_bytes == -1)
		return (print_error("Readed bytes error"));

	buffer[readed_bytes - 1] = '\0';
	argv[0] = buffer;
	argv[1] = NULL;

	new_process = fork();
	if (new_process == -1)
		return (print_error("New process error"));

	if (new_process == 0)
	{
		if (execve(buffer, argv, NULL) == -1)
			return (print_error("Executing program error"));
	}
	else
		wait(&status);

	free(buffer);

	return (0);
}
