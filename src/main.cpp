#include "daemon.hpp"


int main(void)
{
	if (geteuid() != 0)
	{
		std::cerr << "Matt_daemon must be run as root." << std::endl;
		return 1;
	}
	Tintin_reporter log;
	log.log_info("Matt_daemon: Started.");

	Daemon daemon;
	struct sigaction sa;
	sa.sa_handler = Daemon::signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGHUP, &sa, NULL);
	if (!daemon.create_lock())
	{
		std::cerr << "Can 't :/var/lock/matt_daemon.lock" << std::endl;
		return 1;
	}
	log.log_info("Matt_daemon: Creating server.");
	daemon.start();
	log.log_info("Matt_daemon: Enter daemon mode.");

	Server server;
	log.log_info("Matt_daemon: Server created.");
	log.log_info("Matt_daemon: started. PID: " + std::to_string(getpid()));
	server.run();
	log.log_info("Matt_daemmon: Quitting.");
	daemon.remove_lock();
	return 0;
}


