#include "framework.h"
#include "pch.h"

#define SERVER_PORT 1337 // edit the port from this
#pragma warning( disable : 4996 ) // lol

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
    UNREFERENCED_PARAMETER(hModule);
    UNREFERENCED_PARAMETER(lpReserved);

   if(ul_reason_for_call == DLL_PROCESS_ATTACH)
   {
        HMODULE module = GetModuleHandle(NULL);
        uintptr_t imagebase = reinterpret_cast<uintptr_t>(module);
       
        // winsock init
        WSADATA w_data;
        if ( WSAStartup( MAKEWORD( 2, 2 ), &w_data ) != 0 )
            std::cerr << "  [-] WSAStartup failed." << std::endl;

        // creating socket for comms
        SOCKET clientSocket = socket( AF_INET, SOCK_STREAM, 0 );
        if ( clientSocket == INVALID_SOCKET )
        {
            std::cerr << "  [-] Failed to create socket." << std::endl;
            WSACleanup( );
        }

        // etablishing a connection to our server
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons( SERVER_PORT ); // MAKE SURE TO USE THE SAME PORT AS THE SERVER'S ONE !!!
        serverAddr.sin_addr.s_addr = inet_addr( "127.0.0.1" ); // If you host the server on your pc then let it like that, but if you host it from a VPS, then put the ip of the vps.

        // shouldnt happen ngl unless the port is alr used
        if ( connect( clientSocket, ( struct sockaddr* )&serverAddr, sizeof( serverAddr )) == SOCKET_ERROR )
        {
            std::cerr << "  [-] Connect failed." << std::endl;
            closesocket( clientSocket );
            WSACleanup( );
        }

        std::string message = "Imagebase: " + std::to_string(imagebase);
        send(clientSocket, message.c_str(), message.size(), 0);

        /*
        // an advanced message system will be pushed later
        const char* message = "hello world from dll.";
        send( clientSocket, message, strlen( message ), 0 );*/

        closesocket( clientSocket );
        WSACleanup( );
    }

    return TRUE;
}
