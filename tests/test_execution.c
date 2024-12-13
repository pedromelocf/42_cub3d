/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:12:37 by jovicto2          #+#    #+#             */
/*   Updated: 2024/11/20 15:12:41 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

//TODO: change main
//TODO: test log with cube and args
//TODO: check redirect for cub outputs
//TODO: separate tests made in main to a test file
//TODO: update valgrind to last version

#include <criterion/criterion.h>
#include "../includes/cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <valgrind/valgrind.h>

void close_all_fds_except_std() {
	long max_fds = sysconf(_SC_OPEN_MAX);
	if (max_fds == -1) {
		perror("sysconf failed");
		return;
	}

	for (int fd = 3; fd < max_fds; ++fd) {// Skip stdin(0), stdout(1), stderr(2)
		close(fd);
	}
}

int valgrind_exec(const char *command) {
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork failed");
		return -1;
	}

	if (pid == 0) { // Child process
		close_all_fds_except_std(); // Close all FDs except std
		execl("/bin/sh", "sh", "-c", command, NULL);
	}

	// Parent process waits for child
	int status;
	if (waitpid(pid, &status, 0) == -1) {
		perror("waitpid failed");
		return -1;
	}

	return status;
}

Test(end_to_end, test_execution_with_no_args)
{
	const char *command = "valgrind "
						  "--leak-check=full "
						  "--show-leak-kinds=all "
						  "--errors-for-leak-kinds=all "
						  "--track-origins=yes "
//						  "--track-fds=yes "
						  "--trace-children=yes "
						  "--quiet "
						  "./cub3D "
						  "1> tests/cub3d_stdout.log ";
//						  "2> tests/cub3d_stderr.log "
//						  "2> tests/valgrind_output.log";

	int status = valgrind_exec(command);

	cr_assert_neq(status, -1, "system() call failed");

	cr_assert(WIFEXITED(status), "Valgrind did not exit normally");

	FILE *log_file = fopen("tests/valgrind_output.log", "r");
	cr_assert_not_null(log_file, "Failed to open Valgrind output file");

	fseek(log_file, 0, SEEK_END);
	long log_size = ftell(log_file);
	fseek(log_file, 0, SEEK_SET);

	char *valgrind_output = malloc(log_size + 1);
	fread(valgrind_output, 1, log_size, log_file);
	valgrind_output[log_size] = '\0';

	fclose(log_file);
//	remove("tests/valgrind_output.txt");

	cr_assert(!log_size,
				   "Valgrind detected memory leaks:\n%s", valgrind_output);

	int exit_status = WEXITSTATUS(status);
	cr_assert_eq(exit_status, EXIT_FAILURE,
				 "Program should return EXIT_FAILURE with no arguments");
}