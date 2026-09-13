#include "daemon.hpp"

bool handle_auth(const std::string &msg, bool &auth, int client, Tintin_reporter &log)
{
	if (auth)
		return true;
	if (msg.rfind("AUTH ", 0) == 0)
	{
		std::string tmp = msg.substr(5);
		if (tmp == "marc974")
		{
			auth = true;
			log.log_info("Matt_daemon: client authenticated.");
			std::string resp = "Authentication successful.\n";
			std::string encrypt = xor_crypt(resp);
			send(client, encrypt.data(), encrypt.size(), 0);
			return true;
		}
		else
		{
			log.log_error("Matt_daemon: authentication failed.");
			std::string resp = "Authentication failed.\n";
			std::string encrypt = xor_crypt(resp);
			send(client, encrypt.data(), encrypt.size(), 0);
			close(client);
			return false;
		}
	}
	log.log_error("Matt_daemon: client not authenticated.");
	std::string resp = "Please authenticate using: AUTH <user> <password>\n";
	std::string encrypt = xor_crypt(resp);
	send(client, encrypt.data(), encrypt.size(), 0);
	return true;
}
