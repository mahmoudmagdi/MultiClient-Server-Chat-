//
//  ClientSide.cpp
//  
//
//  Created by Ma7MouD on 4/15/17.
//
//
#include "unp.h"

int main()
{
    int client;
    int portNum = 2351; // NOTE that the port number is same for both client and server
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char* ip = "127.0.0.1";
    struct sockaddr_in server_addr;
    client = socket(AF_INET, SOCK_STREAM, 0);
    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/ /* --------------- socket() function ------------------*/
    
    if (client < 0)
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    
    cout << "\n=> Socket client has been created..." << endl;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);
    /* ---------- CONNECTING THE SOCKET ---------- */
    /* ---------------- connect() ---------------- */
    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> Connection to the server port number: " << portNum << endl;
    cout << "=> Awaiting confirmation from the server..." << endl; //line 40
    read(client, buffer, bufsize);
    cout << "=> Connection confirmed, you are good to go...";
    cout << "\n\n=> Enter # to end the connection\n" << endl;
    // Once it reaches here, the client can write a message first.
    do {
        cout << "Client: ";
        
        do {
            cin >> buffer;
            write(client, buffer, bufsize);
            if (*buffer == '#')
            {
                goto terminate;
                //write(client, buffer, bufsize);
                //*buffer = '*';
                //return 0;
                //isExit = true;
            }
        } while (*buffer != 42);
        cout << "Server: ";
        do {
            read(client, buffer, bufsize);
            cout << buffer << " ";
            if (*buffer == '#')
            {
                goto terminate;
                //*buffer = '*';
                //return 0;
                //isExit = true;
            }
        } while (*buffer != 42); 
        cout << endl;
    } while (!isExit);
    /* ---------------- CLOSE CALL ------------- */ /* ----------------- close() --------------- */
    
terminate:
    cout << "\n=> Connection terminated.\nGoodbye...\n";
    close(client);
    return 0; 
}
