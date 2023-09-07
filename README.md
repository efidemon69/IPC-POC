# Intercoms Hook
Intercoms Hook is a C++ project that demonstrates inter-process communication (IPC) between a console application and a DLL, this project consists of two main components:

**The server:** The server is a simple console application that provides an interface which listen for DLL requests and displays them once its sent.

**The DLL (client):** The dll once injected in a process will etablish a communication with the server and send requests to it.



**1. Console App (Server)**
- Listens for incoming requests.
- Logs received messages along with timestamps.
- Measures the time taken to process each request. (LATER)

**2. Client (DLL)**
- Designed for injection into a target process.
- Allocate a console to post custom requests. **(SOON)**
- Prompts the user for input to send messages to the server. **(SOON)**
- Communicates with the server using sockets and sends messages.

# Usage
- Build the server and DLL projects separately.
- Inject the DLL into any process (feel free to use any injector)
- The server console will display received messages along with timestamps and the time taken for each request.
- The DLL will allocate a console in the target process and prompt the user for input to send messages to the server.

# Dependencies
- winsock2.h
- ws2_32.lib **(Make sure to include it or project wont build)**

# Contributing
Feel free to edit the code and ask for pull requests.

# Credits
[WinSocket documentation](https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API)
