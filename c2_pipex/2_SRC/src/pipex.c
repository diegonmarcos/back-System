/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:19 by dinepomu          #+#    #+#             */
/*   Updated: 2025/03/10 10:07:37 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* https://linktr.ee/diegonmarcos											  */
/* ************************************************************************** */

#include "pipex.h"

/** @brief The pipex project is a simplified implementation of a Unix pipeline.
 *
 * 	@details
 * 	@par Details:
 * 		Reads input from a file, processes this input through a series of 
 *  commands, and then writes the processed output to another file. This 
 *  project mimics the behavior of Unix pipelines, allowing for the chaining 
 *  of commands where the output of one command becomes the input for the next.
 *  The project is designed to be run from the command line, utilizing 
 *  command-line argumentsand environment variables to specify the input file,
 *  commands, and output file.
 * 
 * 	@par Usage:
 * 	- @b [parm1] argc: The number of command-line arguments.
 * 	- @b [parm2] argv: An array of command-line arguments.
 * 	- @b [parm3] env: An array of environment variables.
 * 	- @b return: Returns 0 on successful execution.
 * 
 * 	@par Example:
 * 	@code
 * 	env > infile.txt
 *	./pipex infile.txt "grep -x "PATH=.*"" "cat" outfile.txt
 * 	@endcode
 */
int	main(int argc, char **argv, char **env)
{
	error_handling_pipex(argc);
	ft_piping(argv, env);
	return (0);
}
