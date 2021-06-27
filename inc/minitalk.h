/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:52:54 by sshakya           #+#    #+#             */
/*   Updated: 2021/06/27 20:08:17 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include "libft/inc/libft.h"

# ifndef DONE
#  define DONE 1
# endif

# ifndef LIMIT
#  define LIMIT 2
# endif

# ifndef BUFFSIZE
#  define BUFFSIZE 1024
# endif

typedef struct s_mtalk
{
	char	msg[BUFFSIZE];
	int		bit;
	int		byte;
	char	flag;
}	t_mtalk;

#endif
