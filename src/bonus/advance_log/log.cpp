#include "daemon.hpp"


void Tintin_reporter::ensure_archive_dir()
{
	mkdir("/var/log/matt_daemon/archive", 0755);
}


bool Tintin_reporter::is_log_too_big(const char *path)
{
	struct stat st{};
	if (stat(path, &st) == -1)
		return false;
	const off_t max_size = 1 * 1024 * 1024;
	return st.st_size >= max_size;
}

void Tintin_reporter::rotate_log()
{
	const char *log_path = "/var/log/matt_daemon.log";
	if (!is_log_too_big(log_path))
		return;
	std::time_t t = std::time(nullptr);
	std::tm tm{};
	localtime_r(&t, &tm);
	std::ostringstream oss;
	oss << "/var/log/matt_daemon/archive/matt_daemon_" << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".log";
	std::string archive_path = oss.str();
	rename(log_path, archive_path.c_str());
}