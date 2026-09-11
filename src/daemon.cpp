#include "daemon.hpp"

Daemon::Daemon()
{
	lock_fd = -1;
}

Daemon::~Daemon() {}


void Daemon::start()
{
	pid_t pid = fork();
	if (pid < 0)
		exit(1);
	if (pid > 0)
		exit(0);
	if (setsid() < 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid > 0)
		exit(0);
	chdir("/");
	umask(0);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	open("/dev/null", O_RDONLY);
	open("/dev/null", O_WRONLY);
	open("/dev/null", O_WRONLY);
}

 
bool Daemon::create_lock()
{
	lock_fd = open("/var/lock/matt_daemon.lock", O_CREAT | O_RDWR, 0644);
	if (lock_fd < 0)
		return false;
	if (flock(lock_fd, LOCK_EX | LOCK_NB) < 0)
		return false;
	return true;
}


void Daemon::remove_lock()
{
	if (lock_fd >= 0)
	{
		flock(lock_fd, LOCK_UN);
		close(lock_fd);
	}
	unlink("/var/lock/matt_daemon.lock");
}


