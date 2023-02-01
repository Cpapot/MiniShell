/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:49:21 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/18 20:12:14 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>

int		ft_printf_fd(int fd, const char *format, ...);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
void	ft_bzero(void *s, size_t n);
ssize_t	ft_putnull_len(int fd);
ssize_t	ft_putchar_len(int fd, char c);
ssize_t	ft_putint_len(int fd, int nbr);
ssize_t	ft_putpercent_len(int fd);
ssize_t	ft_putstr_len(int fd, char *str);
ssize_t	ft_putunsint_len(int fd, unsigned int nbr);
ssize_t	ft_puthexamin_len(int fd, unsigned int nbr);
ssize_t	ft_puthexamaj_len(int fd, unsigned int nbr);
ssize_t	ft_puthexavoid_len(int fd, void *arg);
ssize_t	ft_callformat(int fd, char const *format, va_list variadic);

#endif
