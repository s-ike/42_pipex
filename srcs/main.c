/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:32:59 by sikeda            #+#    #+#             */
/*   Updated: 2022/04/30 23:25:09 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "ft_error.h"
#include "ft_execute.h"
#include "def_pipex.h"
#include "def_error.h"

#ifdef LEAKS

void
	destructor(void)__attribute__((destructor));

void
	destructor(void)
{
	int		status;
	char	buf[50];

	snprintf(buf, 50, "leaks %d &> leaksout", getpid());
	status = system(buf);
	if (status)
		system("cat leaksout >&2");
}
#endif

static void
	child_process(char **argv, char **environ, int fds[PIPE_NUM])
{
	int	fd;

	close(fds[PIPE_R]);
	fd = open(argv[ARG_FILE1], O_RDONLY, 0666);
	if (fd < 0)
		ft_puterror_and_exit_failure(ft_putperror, argv[ARG_FILE1]);
	dup2(fds[PIPE_W], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fds[PIPE_W]);
	close(fd);
	ft_execute(argv[ARG_CMD1], environ);
}

static void
	parent_process(char **argv, char **environ, int fds[PIPE_NUM])
{
	int	fd;

	close(fds[PIPE_W]);
	dup2(fds[PIPE_R], STDIN_FILENO);
	close(fds[PIPE_R]);
	fd = open(argv[ARG_FILE2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		ft_puterror_and_exit_failure(ft_putperror, argv[ARG_FILE2]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_execute(argv[ARG_CMD2], environ);
}

static void
	main_process(char **argv, char **environ)
{
	int		fds[PIPE_NUM];
	pid_t	pid;
	int		status;

	if (pipe(fds) < 0)
		ft_puterror_and_exit_failure(ft_putperror, "pipe");
	pid = fork();
	if (pid < 0)
		ft_puterror_and_exit_failure(ft_putperror, "fork");
	else if (pid == 0)
		child_process(argv, environ, fds);
	if (waitpid(pid, &status, 0) < 0)
		ft_puterror_and_exit_failure(ft_putperror, "waitpid");
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
			exit(EXIT_FAILURE);
		else
			parent_process(argv, environ, fds);
	}
	else if (WIFSIGNALED(status))
		exit(WTERMSIG(status));
	else
		exit(EXIT_FAILURE);
}

int
	main(int argc, char **argv)
{
	extern char	**environ;

	if (argc != ARG_NUM)
		ft_puterror_and_exit_failure(ft_puterror, ERR_INVAL);
	main_process(argv, environ);
	return (EXIT_FAILURE);
}
