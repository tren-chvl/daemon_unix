#include "daemon.hpp"

void remote_shell(const std::string &msg, int client, Tintin_reporter &log)
{
	std::string command = msg.substr(4);
	command.erase(std::remove(command.begin(), command.end(), '\n'), command.end());
	command.erase(std::remove(command.begin(), command.end(), '\r'), command.end());
	std::string full_cmd = command + " 2>&1";
	FILE *fp = popen(full_cmd.c_str(), "r");
	if (!fp)
	{
		std::string err = "Command failed: " + command + "\n";
		std::string encrypted = xor_crypt(err);
		std::string to_send = "XOR:" + encrypted;
		send(client, to_send.data(), to_send.size(), 0);
		return;
	}
	char outbuf[1024];
	std::string output;
	while (fgets(outbuf, sizeof(outbuf), fp))
		output += outbuf;
	pclose(fp);
	if (output.empty())
		output = "No output.\n";
	std::string encrypted = xor_crypt(output);
	std::string to_send = "XOR:" + encrypted;
	send(client, to_send.data(), to_send.size(), 0);
	log.log_user("Executed command: " + command);
}


