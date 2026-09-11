#include "daemon.hpp"


Server::Server()
{
	sockfd = -1;
	for (int i = 0; i < 3; i++)
		clients[i] = -1;
}


Server::~Server()
{
	if (sockfd >= 0)
		close(sockfd);
}

bool is_xor_message(const std::string &msg)
{
    return msg.rfind("XOR:", 0) == 0;
}

void Server::run()
{
	struct sockaddr_in addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		return;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(4242);
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return;
	if (listen(sockfd, 3) < 0)
		return;
	Tintin_reporter log;
	while (true)
	{
		int client = accept(sockfd, NULL, NULL);
		if (client < 0)
			continue;
		char buffer[1024];
		while (true)
		{
			int n = recv(client, buffer, sizeof(buffer), 0);
			if (n <= 0)
				break;
			std::string msg(buffer, n);
			if (is_xor_message(msg))
				msg = xor_decrypt(msg.substr(4)); 
			log.log_user("User input: " + msg);
			if (msg.rfind("cmd ", 0) == 0)
			{
				remote_shell(msg, client, log);
				continue;
			}
			if (msg == "quit" || msg == "quit\n")
			{
				log.log_info("Matt_daemon: Client disconnected.");
				break;
			}
			log.log_error("Unknown command: " + msg);
			std::string resp = "Unknown command.\n";
			std::string encrypted = xor_crypt(resp);
			send(client, encrypted.data(), encrypted.size(), 0);
		}
		close(client);
	}
	close(sockfd);
}

