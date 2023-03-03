#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_fd
{
	int	stdout;
	int	stdin;
	int	stderr;
}	t_fd;

typedef struct s_commands
{
	t_list	*command;
	t_fd	fd;
}	t_commands;

typedef struct s_memstock
{
	void				*content;
	struct s_memstock	*next;
}						t_memlist;

typedef struct s_info
{
	char		*prompt_string;
	t_commands	**final_parse;
	t_fd		fd;
	t_memlist	*parsing;
	t_memlist	*lexer;
	t_list		**command;
}	t_info;

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
void	print_error(t_info *info, char *error)
{
	write (1, error, ft_strlen(error));
	exit(1);
}


static void	lst_mem_add(t_memlist **lst, t_memlist *new)
{
	t_memlist	*last;

	if (new == NULL || lst == NULL)
		return ;
	last = *lst;
	if (last == NULL)
		*lst = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	while (us1[i] != '\0' && us2[i] != '\0' && i < n)
	{
		if (us1[i] != us2[i])
			return (us1[i] - us2[i]);
		i++;
	}
	if (i < n)
		return (us1[i] - us2[i]);
	return (0);
}

static t_memlist	*lst_mem_new(void *content)
{
	t_memlist	*node;

	node = malloc(sizeof(t_memlist));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	*stock_malloc(size_t size, t_memlist **stock)
{
	void		*result;
	t_memlist	*tmp;

	result = malloc(size);
	if (result == NULL)
		return (NULL);
	if (*stock == NULL)
		*stock = lst_mem_new(result);
	else
	{
		tmp = lst_mem_new(result);
		lst_mem_add(stock, tmp);
	}
	return (result);
}

static int	com_count(t_list *lst)
{
	int	result;

	result = 0;
	while (lst)
	{
		if (lst->content == "|")
			result++;
		lst = lst->next;
	}
	return (result + 1);
}

static void	first_command(t_list **lst)
{

}

static t_fd	set_start_fd(void)
{
	t_fd	result;

	result.stderr = 2;
	result.stdin = 0;
	result.stdout = 1;
	return (result);
}

static	void	go_next_cmd(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->content == "|")
			(*lst) = tmp->next;
		tmp = tmp->next;
	}
}

t_commands	*split_pipe(t_info *info, t_list *lst)
{
	int			i;
	int			count;
	t_list		*tmp;
	t_commands	*result;

	i = 0;
	tmp = lst;
	count = com_count(tmp);
	result = stock_malloc(sizeof(t_commands) * (count + 1), &info->parsing);
	if (result == NULL)
		print_error(info, "Memory error");
	while (i != count)
	{
		result[i].fd = set_start_fd();
		first_command(&tmp);
		result[i].command = tmp;
		tmp = lst;
		go_next_cmd(&lst);
		if (i != 0)
			result[i].fd.stdin = result[i - 1].fd.stdout;
		i++;
	}
	return (result);
}

int main(void)
{
    // Créer une liste chaînée de commandes
    t_list *cmd1 = malloc(sizeof(t_list));
    cmd1->content = "ls";
    t_list *cmd2 = malloc(sizeof(t_list));
    cmd2->content = "|";
    t_list *cmd3 = malloc(sizeof(t_list));
    cmd3->content = "grep";
    t_list *cmd4 = malloc(sizeof(t_list));
    cmd4->content = "hello";
	t_list *cmd5 = malloc(sizeof(t_list));
    cmd5->content = "|";
	t_list *cmd6 = malloc(sizeof(t_list));
    cmd6->content = "hey";

    // Lier les commandes en une liste chaînée
    cmd1->next = cmd2;
    cmd2->next = cmd3;
    cmd3->next = cmd4;
	cmd4->next = cmd5;
	cmd5->next = cmd6;
    cmd6->next = NULL;

    // Créer une structure t_info pour stocker des informations de contexte
    t_info info;
    memset(&info, 0, sizeof(info));

    // Appeler la fonction split_pipe
    t_commands *result = split_pipe(&info, cmd1);

    // Afficher le résultat
	t_list	*tmp;
    int i = 0;
    while (result[i].command != NULL)
    {
		tmp = (result[i]).command;
        printf("\nCommande %d :\n", i);
		while (tmp)
		{
			printf("%s ", tmp->content);
			tmp = tmp->next;
		}
        printf("\nstdin : %d\n", result[i].fd.stdin);
        printf("stdout : %d\n", result[i].fd.stdout);
        printf("stderr : %d\n", result[i].fd.stderr);
        i++;
    }

    // Libérer la mémoire
    free(cmd1);
    free(cmd2);
    free(cmd3);
    free(cmd4);
    free(result);

    return 0;
}
