//
//  ServerSide.cpp
//  
//
//  Created by Ma7MouD on 4/15/17.
//
//

#include "unp.h"
using namespace std;
int main() {
    /* ---------- INITIALIZING VARIABLES ---------- */
    int client, server;
    int portNum = 2351;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    struct sockaddr_in server_addr, client_addr;
    socklen_t size;
    int pid;
    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/ /* --------------- socket() function ------------------*/
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0)
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    
    cout << "\n=> Socket server has been created..." << endl;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);
    
    /* ---------- BINDING THE SOCKET ---------- */ /* ---------------- bind() ---------------- */
    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
    }
    
    cout << "=> Looking for clients..." << endl;
    
    /* ------------- LISTENING CALL ------------- */ /* ---------------- listen() ---------------- */
    listen(client, 1);
    size = sizeof(client_addr);
    /* ------------- ACCEPTING CLIENTS ------------- */ /* ----------------- listen() ------------------- */
    //int clientCount = 1;
    pid = fork();
    
    while (1)
    {
        if(pid < 0)
        {
            cout << "ERROR IN FORK" << endl;
        }
        
        if (pid == 0 || pid > 0)
        {
            server = accept(client, (struct sockaddr *)&client_addr, &size);
            // first check if it is valid or not
            if (server < 0)
            cout << "=> Error on accepting..." << endl;
            
            strcpy(buffer, "=> Server connected...\n");
            write(server, buffer, bufsize);
            cout << "=> Connected with the client #" << pid << ", you are good to go..." << endl;
            cout << "\n=> Enter # to end the connection\n" << endl;
            
            do {
                cout << "Client: ";
                do {
                    read(server, buffer, bufsize);
                    cout << buffer << " ";
                    if (*buffer == '#') {
                        *buffer = '*';
                        goto terminate;
                        //return 0;
                        //isExit = true;
                    }
                } while (*buffer != '*');
                cout << "\nServer: ";
                do {
                    cin >> buffer;
                    write(server, buffer, bufsize);
                    if (*buffer == '#') {
                        write(server, buffer, bufsize);
                        *buffer = '*';
                        return 0;
                        //isExit = true;
                    }
                } while (*buffer != '*');
            } while (!isExit);
        }
    }
    
    terminate:
        /* ---------------- CLOSE CALL ------------- */
        /* ----------------- close() --------------- */
        // inet_ntoa converts packet data to IP, which was taken from client
    cout << "\n\n=> Connection terminated with IP " << inet_ntoa(server_addr.sin_addr);
    close(server);
    cout << "\nGoodbye..." << endl;
    isExit = false;
    exit(1);
    close(client);
    return 0;
}
