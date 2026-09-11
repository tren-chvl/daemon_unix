#include "daemon.hpp"


static const std::string XOR_KEY = "matt_daemon_key";

std::string xor_crypt(const std::string &input)
{
	std::string out = input;
	for (size_t i = 0; i < input.size(); i++)
		out[i] = input[i] ^ XOR_KEY[i % XOR_KEY.size()];
	return out;
}