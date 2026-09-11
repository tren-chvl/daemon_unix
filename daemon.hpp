#ifndef DAEMON_HPP
#define DAEMON_HPP

#include <string>
#include <fstream>
#include <ctime>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <signal.h>
 #include <arpa/inet.h>
#include <fcntl.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <unistd.h>

class Tintin_reporter
{
	public:
		Tintin_reporter();
		~Tintin_reporter();

		void log_info(const std::string &msg);
		void log_error(const std::string &msg);
		void log_user(const std::string &msg);

	private:
		std::ofstream file;
		std::string timestamp();
};

class Daemon
{
	public:
		Daemon();
		~Daemon();

		bool create_lock();
		void remove_lock();
		void start();
		void stop();
		static void signal_handler(int sig);

	private:
		int lock_fd;
};

class Server
{
	public:
		Server();
		~Server();

		void run();
		void shutdown();

	private:
		int sockfd;
		int clients[3];
};

std::string xor_crypt(const std::string &input);
std::string xor_decrypt(const std::string &input);
#endif
