/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:52:54 by sshakya           #+#    #+#             */
/*   Updated: 2021/06/29 16:16:24 by sshakya          ###   ########.fr       */
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

# ifdef OS
#  define TIME 200
# else 
#  define TIME 600
# endif

typedef struct s_mtalk
{
	char	msg[BUFFSIZE];
	int		bit;
	int		index;
	char	flag;
}	t_mtalk;

#endif
