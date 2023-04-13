/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:23:17 by cpapot            #+#    #+#             */
/*   Updated: 2023/04/13 18:59:54 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H

# define ERROR_H

# define ERROR2			"\e[31m\e[1m[ERROR:2]\e[0m Command not found"
# define ERROR3			"\e[31m\e[1m[ERROR:3]\e[0m Parse error (quote not closed)"
# define ERROR4			"\e[31m\e[1m[ERROR:4]\e[0m Parse error on pipe"
# define ERROR5			"\e[31m\e[1m[ERROR:5]\e[0m Syntax error on redirect"
# define ERROR6			"\e[31m\e[1m[ERROR:6]\e[0m Parse error at end of command"
# define ERROR7			"\e[31m\e[1m[ERROR:7]\e[0m Is a directory"
# define ERROR10		"\e[31m\e[1m[ERROR:10]\e[0m Failed to create fork"
# define ERROR11		"\e[31m\e[1m[ERROR:11]\e[0m Failed to pipe fd"
# define ERROR12		"\e[31m\e[1m[ERROR:12]\e[0m Failed to execute command"
# define ERROR13		"\e[31m\e[1m[ERROR:13]\e[0m Failed to duplicate fd"
# define ERROR14		"\e[31m\e[1m[ERROR:14]\e[0m Can't open file"
# define ERROR15		"\e[31m\e[1m[ERROR:15]\e[0m Permission denied"
# define ERROR20		"\e[31m\e[1m[ERROR:20]\e[0m No such file or directory"
# define ERROR98		"\e[31m\e[1m[ERROR:98]\e[0m Failure to access/create logs"
# define ERROR99		"\e[31m\e[1m[ERROR:99]\e[0m Malloc cannot be created"
# define EXPORTERROR1	"\e[31m\e[1mexport\e[0m: not a valid identifier"
# define UNSETERROR1	"\e[31m\e[1munset\e[0m: not a valid identifier"

#endif
