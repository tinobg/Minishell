/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 21:59:31 by jubaldo           #+#    #+#             */
/*   Updated: 2024/02/02 18:48:21 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_PATH 4096
# define MAX_ARGS 512
# define VAR_MAX_SIZE 1024
# define MAX_TOKEN_LEN 1024

# define OLD_PWD "OLDPWD"
# define PWD "PWD"

# define STDOUT STDOUT_FILENO
# define STDIN  STDIN_FILENO
# define STDERR STDERR_FILENO

# define CMD_NOT_EXEC   126
# define CMD_NOT_FOUND  127

# define OR		1
# define AND	2
# define PIPE	3

typedef struct s_redirect
{
	bool	error;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
	int		cmd_index;
	char	*in_file;
	char	*out_file;
	char	*append_file;
	char	*heredoc_eof;
}	t_redirect;

typedef struct s_data
{
	char		**env;
	char		*user_input;
	char		*work_dir;
	char		*old_work_dir;
}	t_data;

typedef struct s_cmd
{
	char	*path;
	char	**args;
	char	**redirections;
}	t_cmd;

typedef struct s_pipe
{
	int	*fd;
}	t_pipe;

typedef struct s_commands
{
	pid_t			*pid;
	int				num_cmds;
	int				num_exec;
	int				*operators;
	int				exit_value;
	char			**cmds;
	char			**tokens;
	char			**paths;
	t_pipe			*pipe;
	t_redirect		*io;
	t_cmd			*cmd;
}	t_commands;

typedef struct s_index
{
	size_t	i;
	size_t	malloc_size;
	size_t	j;
}	t_index;

typedef struct s_num_parenth
{
	int	first_p;
	int	last_p;
}	t_num_parenth;

extern int	g_status_code;

// MAIN
int			main(int ac, char **av, char **envp);
int			minishell(int argc, char **argv, char **envp);

// BUILTINS
int			builtin_cd(t_data *data, t_commands *cmds, int i);
int			builtin_echo(t_commands *cmds, int num_cmd);
int			builtin_env(t_data *data, t_commands *cmds, int num_cmd);
int			builtin_exit(t_data *data, t_commands *cmds, int num_cmds);
int			builtin_export(t_data *data, t_commands *cmds, int num_cmd);
int			builtin_pwd(void);
int			builtin_unset(t_data *data, t_commands *cmds, int num_cmd);

// ENV
void		env_var_remove(t_data *data, int index);
char		**env_var_realloc(t_data *data, int len);
int			get_env_var_index(char **env, char *var);
int			env_var_count(char **envp);
char		*get_env_var_value(char **envp, char *var);
bool		set_env_var(t_data *data, char *key, char *value);
bool		is_valid_var_name(char *name);

// EXEC
bool		is_builtin_empty(t_commands *cmds);
void		exec_builtin_empty(t_commands *cmds, t_data *data);
int			exec_builtins(t_data *data, t_commands *cmds, int num_cmd);
int			exec_child(t_data *data, t_commands *cmds, int num_cmd);
int			execute_local(t_data *data, t_commands *cmds, int num_cmd);
char		*get_cmd_path(t_commands *cmds, int index);
int			execute_path(t_data *data, t_commands *cmds, int num_cmd);
int			execute(t_data *data, t_commands *cmds);
int			execute_cmd(t_data *data, t_commands *cmds, int num_cmd);

// INIT
void		init_cmd(t_data *data, t_commands *cmds, int num_cmd);
void		init_single_cmd(t_data *data, t_commands *cmds, int num_cmd);
void		init_commands(t_data *data, t_commands *cmds);
bool		init_path(t_data *data);
bool		init_data(t_data *data, char **envp);
void		init_parenth(int *i, t_num_parenth *num_p);
void		init_pipes(t_commands *cmds);
void		init_redirections(t_commands *cmds);

// LEXER
void		add_token(char const *input, char **str, size_t i);
void		handle_errors(t_index *i_data, const char *str, t_commands *cmds);
void		quotes_error(t_index *i_data, const char *str, t_commands *cmds);
void		lexer_operators(const char *str, t_commands *cmds);
void		lexer_parentheses(const char *str, t_commands *cmds);
void		lexer_redirections(const char *str, t_commands *cmds);
char		**tokenize_input(char const *input, t_commands *cmds);

// PARSER
void		add_arg_to_cmd(char *str, char *new_str);
void		add_parsed_token(char *s, char **str, size_t len);
void		parse_dollar_sign(t_data *data, t_commands *cmds, int n);
char		*parse_env(t_index *i_data, char *s, t_data *data);
void		find_export_cmd(t_commands *cmds, int num_cmd);
void		parse_full_redirections(char *input, char **str, size_t i);
char		**parse_redirections(char *str);
char		*rm_redirections(char *str);
void		parse_split(char const *input, char **str, size_t i);
char		**parse_whitespace(char const *s);
char		**parser(char *input);

// PIPES
void		check_pipes(t_commands *cmds, int index);
void		close_pipes(t_commands *cmds);
void		close_pipes_fd(t_commands *cmds);
void		create_pipes(t_commands *cmds, int index);

// REDIRECTIONS
bool		is_redirection_cmd(t_commands *cmds, int i);
void		handle_redirections(t_commands *cmds, int j);
void		handle_heredoc(t_commands *cmds, char *part);
int			handle_input(t_commands *cmds, char *part);
int			handle_output(t_commands *cmds, char *part, bool trunc);
void		redirect_io(t_redirect *io, int index_cmd);
void		restore_io(t_redirect *io);
bool		check_file(t_redirect *io, t_commands *cmds, bool free);

// LIBFT
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_isalnum(int c);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strdup(const char *src);
size_t		ft_strlen(char const *s);
char		*ft_strndup(const char *s1, size_t n);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
void		ft_putchar(char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strpbrk(const char *str, const char *accept);
size_t		ft_strspn(const char *str, const char *accept);
char		*ft_strtok(char *str, const char *delim);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isdigit(int c);
long		ft_strtol(const char *str, char **endptr, int base);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strsjoin(char *str, char *add);
int			ft_atol(const char *str, bool *error);
void		*ft_realloc(void *ptr, size_t newsize);
void		ft_putstr_fd(char *s, int fd);
int			ft_isalpha(int c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t len);
char		*ft_itoa(int nb);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		*ft_memmove(void *des, void *src, size_t len);

// SIGNALS
void		signals_wait_cmd(void);
void		signals_run_cmd(void);

// UTILS
bool		check_args(int ac, char **av);
void		check_operators(t_data *data, t_commands *cmds, int num_cmd);
void		free_io(t_redirect *io);
void		free_cmds(t_commands *cmds);
void		close_fds(t_commands *cmds, bool reset_io);
void		free_ptr(void *ptr);
void		free_str(char **str);
bool		clear_prev_input(t_redirect *io, bool in_file);
void		free_data(t_data *data, bool exit_shell);
void		free_pipes(t_commands *cmds);
int			error_msg(char *cmd, char *spec, char *msg, int status_code);
void		exit_minishell(t_data *data, int status_code);
void		free_exit(t_data *data, t_commands *cmds, int status_code);
char		**get_paths(char **envp);
char		*get_prompt(void);
bool		input_handler(t_data *data);
int			is_space(int c);
bool		is_builtin(char *cmd);
bool		is_in_out_file(t_redirect *io, t_commands *cmds, bool free);

#endif