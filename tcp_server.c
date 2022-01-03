#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main(){

  // Criando uma string que guarda os
  // dados que mandamos para os clientes
  char server_message[256] = "Conexão com o servidor efetuada!";

  // Criando uma variável inteira que guarda
  // o valor de retorno da chamado do nosso socket
  int server_socket;
  // Criando o socket do servidor
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Definindo o endenreço do servidor
  // que chamamos de server_address
  struct sockaddr_in server_address;
  
  // sin_family vai permanecer como AF_INET (IPv4)
  server_address.sin_family = AF_INET;
  // A porta vai ser a mesma do client (7777)
  server_address.sin_port = htons(7777);
  // Junto com o endereço (INADDR_ANY), qualquer
  // endereço ip da nossa máquina local
  server_address.sin_addr.s_addr = INADDR_ANY;
  
  // bind(ligar/vincular...) o socket com nosso IP e porta específicas
  bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  // Escutando conexões
  // backlog:
  // A quantidade de conexões
  // que podem 'esperar' por esse socket,
  // pode ser qualquer número que seja pelo
  // menos 1
  listen(server_socket, 5);

  // Criando um inteiro que guarda o socket do cliente
  int client_socket;

  // O client_socket vai ser igual ao
  // resultado da função accept
  // Após aceitar a conexão, nós teremos 
  // um socket que nos permite manipular qualquer
  // coisa no lado do cliente (two-way connection)
  // Os 2 ultimos parâmetros do accept são estruturas
  // que contém o endereço da conexão do client e o
  // tamanho do endereço do cliente (saber de onde o cliente
  // está se conectando)
  client_socket = accept(server_socket, NULL, NULL);
  
  // Enviando dados para o socket do cliente
  // 1 o socket onde estamos enviando dados,
  // 2 os dados que mandamos para o socket do cliente,
  // 3 e o tamanho da mensagem
  send(client_socket, server_message, sizeof(server_message), 0);

  // Fechando o socket
  close(server_socket);

  return 0;
}
