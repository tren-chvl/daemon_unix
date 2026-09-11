#include "daemon.hpp"


Tintin_reporter::Tintin_reporter()
{
	mkdir("/var/log/matt_daemon", 0755);
	file.open("/var/log/matt_daemon.log", std::ios::app);
}


Tintin_reporter::~Tintin_reporter()
{
	if (file.is_open())
		file.close();
}


std::string Tintin_reporter::timestamp()
{
	time_t now = time(nullptr);
	struct tm *t =  localtime(&now);
	char buf[64];

	strftime(buf, sizeof(buf), "[%d/%m/%Y-%H:%M:%S]", t);
	return (std::string(buf));
}

void Tintin_reporter::log_info(const std::string &msg)
{
	file << timestamp() << " [INFO] - " << msg << std::endl;
}

void Tintin_reporter::log_user(const std::string &msg)
{
	file << timestamp() << " [LOG] - " << msg << std::endl;
}

void Tintin_reporter::log_error(const std::string &msg)
{
	file << timestamp() << " [ERROR] - " << msg << std::endl;
}



