	#include "minishell.h"

	volatile sig_atomic_t g_sig = 0;

	void sigint_heredoc(int sig)
	{
		(void)sig;
		g_sig = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_done = 1;
	}

	void sigint_exec(int sig)
	{
		if (sig == SIGINT)
			write(1, "\n", 1);
	}

	void sigquit_exec(int sig)
	{
		if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
	}

	void sig_handler(int sig)
	{
		g_sig = sig;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}

	void init_signals(void)
	{

		struct sigaction sig;

		sig.sa_handler = sig_handler;
		sigemptyset(&sig.sa_mask);
		sig.sa_flags = 0;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);
	}