#include "daemon.hpp"

static const std::string XOR_KEY = "matt_daemon_key";

std::string xor_crypt(const std::string &input)
{
	std::string tmp;
	tmp.reserve(input.size());

	for (size_t i = 0; i < input.size(); i++)
		tmp.push_back(input[i] ^ XOR_KEY[i % XOR_KEY.size()]);
	std::ostringstream oss;
	for (unsigned char c : tmp)
		oss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
	return oss.str();
}

std::string xor_decrypt(const std::string &input)
{
	std::string tmp;
	if (input.size() % 2 != 0)
		return "";
	for (size_t i = 0; i < input.size(); i += 2)
	{
		std::string byte = input.substr(i, 2);
		if (!std::isxdigit(byte[0]) || !std::isxdigit(byte[1]))
			return "";
		unsigned char c = (unsigned char)std::stoi(byte, nullptr, 16);
		tmp.push_back(c);
	}
	std::string out;
	out.reserve(tmp.size());
	for (size_t i = 0; i < tmp.size(); i++)
		out.push_back(tmp[i] ^ XOR_KEY[i % XOR_KEY.size()]);
	return out;
}