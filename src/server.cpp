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
			int n = recv(client, buffer, sizeof(buffer) - 1, 0);
			if (n <= 0)
				break;
			buffer[n] = '\0';
			std::string msg(buffer);
			msg = xor_crypt(msg);
			msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());
			msg.erase(std::remove(msg.begin(), msg.end(), '\r'), msg.end());
			if (msg == "quit\n" || msg == "quit")
			{
				log.log_info("Matt_daemon: Request quit.");
				close(client);
				close(sockfd);
				return;
			}
			log.log_user("User input: " + msg);
		}
		close(client);
	}
	close(sockfd);
}


