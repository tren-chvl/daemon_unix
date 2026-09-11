#include "daemon.hpp"

void Daemon::signal_handler(int sig)
{
    Tintin_reporter logger;

    logger.log_info("Matt_daemon: Signal handler. Signal = " + std::to_string(sig));
    logger.log_info("Matt_daemon: Quitting.");
    unlink("/var/lock/matt_daemon.lock");
    exit(0);
}