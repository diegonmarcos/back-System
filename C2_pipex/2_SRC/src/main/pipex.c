/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinepomu <dinepomu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:30:19 by dinepomu          #+#    #+#             */
/*   Updated: 2025/02/27 13:38:47 by dinepomu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** @brief 
 *
 * 	@details
 * 	@par Details:
 * 	- 
 * 	- 
 * 	- 
 * 	- 
 * 	-  
 * 
 * 	@par Usage:
 * 	- @b [parm1] is
 * 	- @b [parm2] is
 * 	- @b [parm3] is
 * 	- @b return is
 */
int	main(int argc, char **argv, char **env)
{
	error_handling_pipex(argc);
	ft_piping(argv, env);
	return (0);
}
