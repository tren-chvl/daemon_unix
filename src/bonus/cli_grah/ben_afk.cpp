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
	echo();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	WINDOW *output_border = newwin(rows - 4, cols, 0, 0);
	box(output_border, 0, 0);
	wattron(output_border, COLOR_PAIR(1));
	mvwprintw(output_border, 1, 2, "Ben_AFK connected to Matt_daemon");
	wattroff(output_border, COLOR_PAIR(1));
	wrefresh(output_border);
	WINDOW *output = derwin(output_border, rows - 6, cols - 2, 2, 1);
	scrollok(output, TRUE);
	WINDOW *input = newwin(4, cols, rows - 4, 0);
	box(input, 0, 0);
	wrefresh(input);
	char buffer[2048];
	while (true)
	{
		werase(input);
		box(input, 0, 0);
		wattron(input, COLOR_PAIR(3));
		mvwprintw(input, 1, 2, "> ");
		wattroff(input, COLOR_PAIR(3));
		wrefresh(input);
		char line[512];
		wgetnstr(input, line, sizeof(line) - 1);
		std::string msg(line);
		if (msg == "exit")
			break;
		std::string encrypted = xor_crypt(msg);
		std::string to_send = "XOR:" + encrypted;
		send(sock, to_send.data(), to_send.size(), 0);
		ssize_t n = recv(sock, buffer, sizeof(buffer), 0);
		if (n <= 0)
		{
			wattron(output, COLOR_PAIR(4));
			wprintw(output, "\nDisconnected from daemon.");
			wattroff(output, COLOR_PAIR(4));
			wrefresh(output);
			break;
		}
		std::string resp(buffer, n);
		// if (resp.rfind("XOR:", 0) == 0)
 		//    resp = xor_decrypt(resp.substr(4));
		wattron(output, COLOR_PAIR(2));
		wprintw(output, "\nDaemon: %s", resp.c_str());
		wattroff(output, COLOR_PAIR(2));
		wrefresh(output);
		box(output_border, 0, 0);
		wattron(output_border, COLOR_PAIR(1));
		mvwprintw(output_border, 1, 2, "Ben_AFK connected to Matt_daemon");
		wattroff(output_border, COLOR_PAIR(1));
		wrefresh(output_border);
	}
	delwin(output);
	delwin(output_border);
	delwin(input);
	endwin();
	close(sock);
	return 0;
}
