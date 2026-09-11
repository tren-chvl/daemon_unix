#include "daemon.hpp"

int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4242);
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	connect(sock, (sockaddr*)&addr, sizeof(addr));
	while (true)
	{
		std::string msg;
		std::getline(std::cin, msg);

		std::string encrypted = xor_crypt(msg);
		encrypted = "XOR:" + encrypted;
		std::cout << "Encrypted : ";
		std::cout.write(encrypted.data(), encrypted.size());
		std::cout << std::endl;
		send(sock, encrypted.data(), encrypted.size(), 0);
		if (msg.rfind("cmd ", 0) == 0)
		{
			char buffer[2048];
			int n = recv(sock, buffer, sizeof(buffer), 0);
			if (n > 0)
			{
				std::string resp(buffer, n);
				resp = xor_decrypt(resp);
				std::cout << resp << std::endl;
			}
		}
		if (msg == "quit")
			break;
	}
	close(sock);
}
