#include "includes.hpp"

/*

    IPC-SERVER: this one is used to receive and handle requests coming from our client (DLL)
    name: interproc communications (IPC)
    author: @vfunc

    description: This is a simple IPC POC made using winsockets which demonstrate how to use winsockets to etablish an inter communication between a server (console app) 
    and a dll (client), i'm not responsible for any bad usages i made this for educational purposes only.
    if you have for plan to re-use this, a credit would be appreciated <3
    Warning! in this actual state, IPc is not secured !! you have to secure your network / encrypt your sockets or anyone with a minimum IQ could easily grab the infos from them.

*/

auto main() -> VOID
{
    std::cout << "\n\n";
    SetConsoleTitleA("IPC SERVER");

    // winsock init
    WSADATA w_data;
    if ( WSAStartup( MAKEWORD( 2, 2 ), &w_data ) != 0)
        std::cerr << "  [-] WSAStartup failed." << std::endl;

    // creating a temporary socket to receive requests
    SOCKET serverSocket = socket( AF_INET, SOCK_STREAM, 0 );
    if (serverSocket == INVALID_SOCKET)
        std::cerr << "  [-] Failed to create socket." << std::endl;

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons( PROTOCOL_PORT ); // port set from includes.hpp
    server_address.sin_addr.s_addr = INADDR_ANY;

    if ( bind( serverSocket, ( struct sockaddr* )&server_address, sizeof( server_address )) == SOCKET_ERROR )
    {
        std::cerr << "  [-] Bind failed." << std::endl;
        closesocket( serverSocket );
        WSACleanup( );
    }

    if ( listen( serverSocket, SOMAXCONN) == SOCKET_ERROR )
    {
        std::cerr << "  [-] Listen failed." << std::endl;
        closesocket( serverSocket );
        WSACleanup( );
    }

    std::cout << "  [~] Listening for requests..." << std::endl;

    // accept incoming connections and handle requests
    while ( true ) 
    {
        SOCKET clientSocket = accept( serverSocket, nullptr, nullptr );
        if ( clientSocket == INVALID_SOCKET )
        {
            std::cerr << "[-] Accept failed." << std::endl;
            continue;
        }

        // receive and process the requests sent from our dll
        char buffer[1024];
        int bytesRead = recv( clientSocket, buffer, sizeof( buffer ), 0);
        if ( bytesRead > 0 ) 
        {
            buffer[bytesRead] = '\0';

            std::string message(buffer);

            // ill setup chrono later
            auto start = std::chrono::high_resolution_clock::now();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            std::cout << "  [+] Received: " << message << " from DLL (request took: " << duration.count() << "ms)" << std::endl;
        }

        closesocket( clientSocket );
    }

    closesocket( serverSocket );
    WSACleanup( );
}