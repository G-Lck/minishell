/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:12:44 by theo              #+#    #+#             */
/*   Updated: 2025/08/03 15:12:44 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include "unistd.h"
# include "stdlib.h"
# include "stdint.h"
# include "stdarg.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_atoi(const char *nbr);
int		ft_isalpha(int character);
int		ft_isdigit(int character);
int		ft_isalnum(int character);
int		ft_isascii(int character);
int		ft_isprint(int character);
int		ft_toupper(int character);
int		ft_tolower(int character);
int		ft_fprintf(int fd, const char *str, ...);
int		ft_printf(const char *str, ...);
size_t	ft_printf_putstr(char *str);
size_t	ft_printf_putstr_fd(int fd, char *str);
size_t	ft_printf_char(int character);
size_t	ft_printf_char_fd(int fd, int character);
size_t	get_number_size(long long int nb, char *base);
size_t	ft_print_ptr(uintptr_t ptr);
size_t	ft_print_ptr_fd(int fd, uintptr_t ptr);
size_t	ft_print_number(long long number);
size_t	ft_print_number_fd(int fd, long long number);
size_t	ft_print_hexadecimal(unsigned long number, int upper);
size_t	ft_print_hexadecimal_fd(int fd, unsigned long number, int upper);
void	ft_putchar(char c);
void	ft_putnbr_base(long long int nb, char *base);
int		ft_strncmp(const char *first, const char *second, size_t lenght);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
size_t	ft_strlen(const char *string);
size_t	ft_strlcat(char *destination, const char *source, size_t size);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	*ft_strchr(const char *string, int searchChar);
char	*ft_strrchr(const char *string, int searchChar);
char	*ft_strnstr(const char *string, const char *to_find, size_t len);
char	*ft_strdup(const char *source);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char *set);
char	*ft_realloc(char *dest, char *src);
int		char_isfind(char *str, char c);
void	*ft_memset(void *pointer, int value, size_t count);
void	*ft_memcpy(void *destination, const void *source, size_t size);
void	*ft_memchr(const void *memoryBlock, int searchChar, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *pointer, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*get_next_line(int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *l);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	*get_next_line(int fd);

#endif
