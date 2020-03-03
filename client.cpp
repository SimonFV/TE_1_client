
#include "mainwindow.h"
int sock;
string send_ver(string first, string last);
void close_sock();

/**
 * @brief Funcion que crea el socket cliente y lo conecta al servidor
 * @return Informacion del grafo
 */
string run_client(){
    /**
     * @note Crea el socket
     */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        return "error";
    }
    /**
     * @note Struct con la informacion del server
     */
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    /**
     * @note Intenta conectar con el servidor
     */
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if(connectRes == -1){
        return "error";
    }

    char buf[4096];
    string server_s;
    /**
     * @note Espera por respuesta
     */
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    if (bytesReceived == -1){
        server_s = "error";
    }else{
        server_s = string(buf, bytesReceived);
    }

    return server_s;
}

/**
 * @brief Solicita al servidor la ruta mas optima entre dos vertices
 * @param first Vertice inicial
 * @param last Vertice final
 * @return Ruta optima
 */
string send_ver(string first, string last){
    char buf[4096];
    string userInput = first+","+last+",";
    /**
     * @note Se envia al server
     */
    int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
    if(sendRes == -1){
        return "No se pudo enviar el mensaje\n";
    }
    /**
     * @note Espera por respuesta
     */
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    if (bytesReceived == -1){
        return "Error al recibir respuesta del servidor.";
    }else{
        /**
         * @note Retorna la respuesta
         */
        return string(buf, bytesReceived);
    }
}

/**
 * @brief Cierra el socket cliente
 */
void close_sock(){
    close(sock);
}
