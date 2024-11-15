//TODO: suppress open fds
//TODO: check if the log will be created when valgrind is empty of errors
//TODO: apply 42 header
//TODO: change libft's Makefile to all flags
//TODO: change compile messsages in Makefile
//TODO: separate tests made in main to a test file
//TODO: -Wno-unused-result in CFLAGS on both Makefile

#include <criterion/criterion.h>
#include "../includes/cub3d.h"


Test(end_to_end, test_execution_with_no_args)
{
	const char *command = "valgrind "
						  "--leak-check=full "
						  "--show-leak-kinds=all "
						  "--errors-for-leak-kinds=all "
//						  "--error-exitcode=42 "
						  "--track-origins=yes "
						  "--track-fds=yes "
						  "--trace-children=yes "
						  "--log-file=valgrind_output.txt "
						  "-q "
//						  "--suppressions=cub3D.sup "
						  "./cub3D 2 > /dev/null 2>&1";
	int status = system(command);

	cr_assert_neq(status, -1, "system() call failed");

	cr_assert(WIFEXITED(status), "Valgrind did not exit normally");

	int valgrind_exit_code = WEXITSTATUS(status);

//	if (valgrind_exit_code == 42) {
		FILE *log_file = fopen("valgrind_output.txt", "r");
		cr_assert_not_null(log_file, "Failed to open Valgrind output file");

		fseek(log_file, 0, SEEK_END);
		long log_size = ftell(log_file);
		fseek(log_file, 0, SEEK_SET);

		char *valgrind_output = malloc(log_size + 1);
		fread(valgrind_output, 1, log_size, log_file);
		fclose(log_file);
		valgrind_output[log_size] = '\0';

//		cr_assert_fail("Valgrind detected memory leaks or errors:\n%s",
//					   valgrind_output);


		free(valgrind_output);
//	}

//	remove("valgrind_output.txt");

//	cr_assert_eq(valgrind_exit_code, EXIT_FAILURE,
//				 "Program should return EXIT_FAILURE with no arguments");
}
