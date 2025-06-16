# include "minishell.h"
void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay(); 
		g_r_code = 130;
	}
	else if (signum == SIGQUIT)
		return ;
}

int	signal_handlers(t_global global)
{
	struct sigaction	action;

	action = (struct sigaction){};
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	return (0);
}