
#include "mainwindow.h"
int sock;
string send_ver(string first, string last);
void close_sock();

string run_client(){
    //Crea el socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        return "ERROR al crear el socket";
    }
    //struct con la info del server
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //Conecta con el server
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if(connectRes == -1){
        return "ERROR al crear el socket";
    }

    char buf[4096];
    string server_s;
    //Espera por respuesta
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    if (bytesReceived == -1){
        server_s = "ERROR al recibir respuesta del servidor";
    }else{
        //Muestra la respuesta por consola
        //cout << "Srvr>"<<string(buf, bytesReceived)<<"\n";
        server_s = string(buf, bytesReceived);
    }

    return server_s;
}

string send_ver(string first, string last){
    char buf[4096];
    string userInput = first+","+last;
    //Se envia al server
    int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
    if(sendRes == -1){
        return "No se pudo enviar el mensaje\n";
    }
    //Espera por respuesta
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    if (bytesReceived == -1){
        return "Error al recibir respuesta del servidor.";
    }else{
        //Retorna la respuesta
        return string(buf, bytesReceived);
    }
}

void close_sock(){
    close(sock);
}
