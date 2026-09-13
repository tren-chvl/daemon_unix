#include "daemon.hpp"

int connect_daemon()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		return -1;
	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4242);
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	if (connect(sock, (sockaddr *)&addr, sizeof(addr)) < 0)
	{
		close(sock);
		return -1;
	}
	return sock;
}


int main()
{
	int sock = connect_daemon();
	if (sock < 0)
	{
		std::cerr << "Cannot connect to Matt_daemon\n";
		return 1;
	}
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	WINDOW *output = newwin(rows - 3, cols, 0, 0);
	WINDOW *input  = newwin(3, cols, rows - 3, 0);
	scrollok(output, TRUE);
	box(output, 0, 0);
	box(input, 0, 0);
	mvwprintw(output, 1, 2, "Ben_AFK connected to Matt_daemon");
	wrefresh(output);
	wrefresh(input);
	char buffer[2048];
	while (true)
	{
		werase(input);
		box(input, 0, 0);
		mvwprintw(input, 1, 2, "> ");
		wrefresh(input);
		char line[512];
		wgetnstr(input, line, sizeof(line) - 1);
		std::string msg(line);
		if (msg == "exit")
			break;

		std::string encrypted = xor_crypt(msg);
		std::string to_send = "XOR:" + encrypted;
		send(sock, to_send.data(), to_send.size(), 0);
		int n = recv(sock, buffer, sizeof(buffer), 0);
		if (n <= 0)
		{
			wprintw(output, "\nDisconnected from daemon.");
			wrefresh(output);
			break;
		}
		std::string resp(buffer, n);
		if (resp.rfind("XOR:", 0) == 0)
			resp = xor_decrypt(resp.substr(4));
		wprintw(output, "\nDaemon: %s", resp.c_str());
		wrefresh(output);
	}
	delwin(output);
	delwin(input);
	endwin();
	close(sock);
	return 0;
}
