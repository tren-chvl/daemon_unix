#include "daemon.hpp"

bool is_hex_string(const std::string &s)
{
	if (s.empty() || s.size() % 2 != 0)
		return false;
	for (char c : s)
	{
		if (!std::isxdigit(static_cast<unsigned char>(c)))
			return false;
	}
	return true;
}


int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("socket");
		return 1;
	}
	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4242);
	if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0)
	{
		perror("inet_pton");
		close(sock);
		return 1;
	}
	if (connect(sock, (sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("connect");
		close(sock);
		return 1;
	}
	char buffer[2048];
	while (true)
	{
		std::string msg;
		if (!std::getline(std::cin, msg))
			break;
		if (msg.empty())
			continue;
		std::string encrypted = "XOR:" + xor_crypt(msg);
		std::cout << "Encrypted : " << encrypted << std::endl;
		ssize_t sent = send(sock, encrypted.data(), encrypted.size(), 0);
		if (sent <= 0)
		{
			perror("send");
			break;
		}
		memset(buffer, 0, sizeof(buffer));
		ssize_t n = recv(sock, buffer, sizeof(buffer), 0);
		if (n <= 0)
		{
			if (n == 0)
				std::cerr << "Server disconnected." << std::endl;
			else
				perror("recv");
			break;
		}
		std::string resp(buffer, n);
		size_t pos = 0;
		while ((pos = resp.find("XOR:", pos)) != std::string::npos)
		{
			size_t next = resp.find("XOR:", pos + 4);
			std::string encrypted_resp;
			if (next == std::string::npos)
				encrypted_resp = resp.substr(pos + 4);
			else
				encrypted_resp = resp.substr(pos + 4, next - (pos + 4));
			if (is_hex_string(encrypted_resp))
				std::cout << xor_decrypt(encrypted_resp) << std::endl;
			else
				std::cerr << "Invalid XOR response." << std::endl;
			if (next == std::string::npos)
				break;
			pos = next;	
		}
		if (msg == "quit")
			break;
	}
	close(sock);
	return 0;
}