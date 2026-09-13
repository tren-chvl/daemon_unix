# 🧿 Matt_daemon — UNIX Daemon

<p align="center">
  <img src="assets/daemon_better.gif" width="400" alt="Matt_daemon demonstration">
</p>

<p align="center">
  <strong>A UNIX daemon built from scratch in C++.</strong><br>
  <sub>Background processes • TCP networking • Logging • Authentication • Remote interaction</sub>
</p>

<br>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-111111?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/UNIX-111111?style=for-the-badge&logo=linux&logoColor=white" alt="UNIX">
  <img src="https://img.shields.io/badge/TCP-111111?style=for-the-badge" alt="TCP">
  <img src="https://img.shields.io/badge/Daemon-111111?style=for-the-badge" alt="Daemon">
  <img src="https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white" alt="42">
</p>

---

## 📖 About

**Matt_daemon** is a UNIX daemon written in **C++** as part of the 42 curriculum.

The objective of this project is to understand how background services work on UNIX systems, from process creation and daemonisation to network communication and resource management.

The daemon runs in the background, listens on **TCP port `4242`**, accepts multiple clients, records activity in a dedicated log file and ensures that only one instance is running at a time.

The project also includes the bonus features, extending the daemon into a more complete client/server system.

> **A small UNIX service, built from the ground up.**

---

## ✨ Features

### Mandatory

| Feature | Description |
|---|---|
| 🧩 Daemonisation | Background execution using UNIX process management |
| 🔒 Single instance | Exclusive lock file with `flock()` |
| 📡 TCP server | Listening on port `4242` |
| 👥 Client management | Up to 3 simultaneous clients |
| 📝 Logging | Centralised `Tintin_reporter` logging system |
| 🛡️ Signal handling | Interception and clean shutdown |
| ❌ Quit command | Stop the daemon through a client request |
| 🗂️ Log storage | Persistent logs under `/var/log/matt_daemon/` |
| 🔑 Root privileges | Execution with the required permissions |

---

## ⭐ Bonus

### 🔐 Encrypted client — `Ben_AFK`

A dedicated client communicates with the daemon through an encrypted protocol.

```text
┌──────────────────────┐
│       Ben_AFK        │
│       Client         │
└──────────┬───────────┘
           │
           │ Encrypted TCP
           ▼
┌──────────────────────┐
│     Matt_daemon      │
│       Server         │
└──────────────────────┘
```

Features:

- XOR encrypted communication
- Client/server interaction
- Authentication support
- Protected message exchange

---

### 🐚 Remote Shell

The client can interact with the daemon through a remote shell.

```bash
shell
ls -la
whoami
exit
```

> Remote shell functionality should only be used in a controlled environment.

---

### 🖥️ Graphical Client

A graphical client provides an alternative interface for interacting with the daemon.

```text
┌─────────────────────────────┐
│          Ben_AFK            │
│                             │
│  ┌───────────────────────┐  │
│  │      Connection       │  │
│  └───────────────────────┘  │
│                             │
│  ┌───────────────────────┐  │
│  │    Authentication     │  │
│  └───────────────────────┘  │
│                             │
│  ┌───────────────────────┐  │
│  │       Messages        │  │
│  └───────────────────────┘  │
│                             │
│  ┌───────────────────────┐  │
│  │      Remote Shell     │  │
│  └───────────────────────┘  │
└─────────────────────────────┘
```

---

### 🗄️ Log Archival

Older logs are automatically moved to an archive directory.

```text
/var/log/matt_daemon/
│
├── matt_daemon.log
│
└── archive/
    ├── matt_daemon.log.1
    ├── matt_daemon.log.2
    └── ...
```

---

### 🔑 Authentication

Clients authenticate before accessing protected functionality.

```text
Client
  │
  │ Authentication
  ▼
Matt_daemon
  │
  ├── ❌ Invalid credentials
  │
  └── ✅ Authenticated
           │
           ▼
      Command access
```

---

### 🔒 Advanced Encryption

The project also includes advanced cryptographic mechanisms.

```text
Client
  │
  │ Encrypt
  ▼
Encrypted message
  │
  │ TCP :4242
  ▼
Matt_daemon
  │
  │ Decrypt
  ▼
Original message
```

---

## 🧠 Architecture

```text
                         ┌─────────────────────┐
                         │       Ben_AFK       │
                         │        Client       │
                         └──────────┬──────────┘
                                    │
                                    │ TCP :4242
                                    ▼
                         ┌─────────────────────┐
                         │     Matt_daemon     │
                         │        Server       │
                         └──────────┬──────────┘
                                    │
                    ┌───────────────┼───────────────┐
                    │               │               │
                    ▼               ▼               ▼
               Client 1         Client 2         Client 3
                    │               │               │
                    └───────────────┼───────────────┘
                                    │
                                    ▼
                         ┌─────────────────────┐
                         │   Tintin_reporter  │
                         │       Logger       │
                         └──────────┬──────────┘
                                    │
                                    ▼
                         /var/log/matt_daemon/
```

---

## ⚙️ Daemon lifecycle

```text
Start program
      │
      ▼
Check root privileges
      │
      ▼
Create lock file
      │
      ▼
Create TCP socket
      │
      ▼
Bind port 4242
      │
      ▼
Daemonise process
      │
      ▼
Accept clients
      │
      ▼
Process messages
      │
      ▼
Log actions
      │
      ▼
Check for quit command
      │
      ▼
Clean shutdown
```

---

## 🌐 Networking

The daemon listens on:

```text
TCP :4242
```

The communication process is based on:

- `socket()`
- `bind()`
- `listen()`
- `accept()`
- `send()`
- `recv()`
- `close()`

The server supports up to **3 simultaneous clients**.

---

## 📝 Logging System

The project uses the following logging class:

```text
Tintin_reporter
```

Logs are stored in:

```text
/var/log/matt_daemon/matt_daemon.log
```

Example:

```text
[11/09/2026-10:15:15] [ INFO ] - Matt_daemon: Started.
[11/09/2026-10:15:15] [ INFO ] - Matt_daemon: Creating server.
[11/09/2026-10:15:15] [ INFO ] - Matt_daemon: Server created.
[11/09/2026-10:15:15] [ INFO ] - Matt_daemon: Entering Daemon mode.
[11/09/2026-10:15:15] [ INFO ] - Matt_daemon: Started. PID: 4242.
[11/09/2026-10:15:20] [ LOG ] - Matt_daemon: User input: hello
[11/09/2026-10:15:20] [ INFO ] - Matt_daemon: Request quit.
[11/09/2026-10:15:20] [ INFO ] - Matt_daemon: Quitting.
```

---

## 🔒 Single Instance Protection

Only one instance of the daemon can run at a time.

The lock file is created at:

```text
/var/lock/matt_daemon.lock
```

If another instance tries to start, the daemon refuses to launch.

Example error:

```text
Can't open :/var/lock/matt_daemon.lock
```

---

## 🛑 Signal Handling

The daemon intercepts supported signals and performs a clean shutdown.

Supported signals include:

- `SIGINT`
- `SIGTERM`
- `SIGHUP`

Example:

```bash
sudo kill -15 <PID>
```

The signal is logged:

```text
[ INFO ] - Matt_daemon: Signal handler.
[ INFO ] - Matt_daemon: Quitting.
```

During shutdown, the daemon:

1. Stops accepting new clients
2. Closes client sockets
3. Closes the server socket
4. Releases the lock file
5. Closes the log file
6. Exits cleanly

---

## 🚀 Installation

### Requirements

- Linux
- C++ compiler
- Make
- Root privileges

### Clone the repository

```bash
git clone https://github.com/tren-chvl/daemon_unix.git
cd daemon_unix
```

### Build the project

```bash
make
```

### Clean the project

```bash
make clean
make fclean
make re
```

---

## 💻 Usage

### Start the daemon

```bash
sudo ./Matt_daemon
```

### Check the running process

```bash
ps aux | grep Matt_daemon
```

### Check the listening port

```bash
sudo ss -lntp | grep 4242
```

### Connect using Netcat

```bash
nc localhost 4242
```

Then send messages:

```text
hello
test
quit
```

### Follow the logs

```bash
sudo tail -f /var/log/matt_daemon/matt_daemon.log
```

---

## 🧪 Testing

### Test the TCP connection

```bash
nc localhost 4242
```

### Test multiple clients

Open three terminals and connect to the daemon:

```bash
nc localhost 4242
```

The server accepts up to **3 simultaneous clients**.

### Test the lock file

Start the daemon twice:

```bash
sudo ./Matt_daemon
sudo ./Matt_daemon
```

The second instance must be rejected.

### Test the quit command

```text
quit
```

The daemon should stop and release its resources.

### Test signal handling

```bash
sudo kill -SIGTERM <PID>
```

The daemon should log the signal and exit cleanly.

---

## 📁 Project Structure

```text
daemon_unix/
│
├── Makefile
├── README.md
│
├── include/
│   └── ...
│
├── src/
│   ├── main.cpp
│   ├── daemon/
│   ├── server/
│   ├── client/
│   ├── logging/
│   ├── authentication/
│   └── ...
│
├── assets/
│   └── daemon_better.gif
│
└── ...
```

---

## 🧩 UNIX Concepts Used

| Function | Purpose |
|---|---|
| `fork()` | Create the daemon process |
| `setsid()` | Create a new session |
| `chdir()` | Change the working directory |
| `umask()` | Set file creation permissions |
| `flock()` | Prevent multiple daemon instances |
| `sigaction()` | Advanced signal handling |
| `socket()` | Create a network socket |
| `bind()` | Attach the socket to port `4242` |
| `listen()` | Wait for incoming connections |
| `accept()` | Accept clients |
| `send()` | Send data |
| `recv()` | Receive data |
| `close()` | Release file descriptors |

---

## 🧠 What I Learned

This project helped me understand:

- UNIX daemonisation
- Process management
- TCP networking
- Client/server architecture
- File descriptors
- Signal handling
- File locking
- Logging systems
- Authentication
- Encryption
- Remote communication
- Error handling
- Resource cleanup

---

## 📚 References

Useful UNIX manual pages:

```bash
man 2 fork
man 2 setsid
man 2 chdir
man 2 flock
man 2 socket
man 2 bind
man 2 listen
man 2 accept
man 2 recv
man 2 send
man 7 signal
```

---

## 🎓 42 Project

| Information | Value |
|---|---|
| Project | Matt_daemon |
| Category | UNIX |
| Language | C++ |
| Platform | Linux |
| Protocol | TCP |
| Port | `4242` |
| Maximum clients | `3` |
| Main executable | `Matt_daemon` |
| Bonus client | `Ben_AFK` |

---

## 👤 Author

**tren-chvl**

GitHub: [github.com/tren-chvl](https://github.com/tren-chvl)

Repository: [daemon_unix](https://github.com/tren-chvl/daemon_unix)
