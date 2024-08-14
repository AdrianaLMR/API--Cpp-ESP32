# API / C++ / ESP32

## Descrição

Este projeto demonstra como usar o **ESP32** com **C++** para criar uma API simples que realiza as seguintes funções:

- Conecta o ESP32 a uma rede Wi-Fi.
- Inicializa um servidor web que responde a requisições HTTP.
- Exibe uma página HTML personalizada com informações e estilo ajustado para uma melhor visualização.

## Funcionalidades

- **Conexão Wi-Fi**: Configura a conexão do ESP32 à rede Wi-Fi e monitora o status da conexão.
- **Servidor Web**: Responde a requisições HTTP com uma página HTML estilizada.
- **HTML e CSS**: Apresenta uma página web com títulos e listas estilizadas para uma visualização clara e profissional.

## Destaques Técnicos

- **Biblioteca `WiFi.h`**: Utilizada para conectar o ESP32 à rede Wi-Fi.
- **Servidor Web**: Implementação de um servidor web básico para responder com conteúdo HTML.
- **Estilização com CSS**: Design da página HTML para melhorar a aparência e a experiência do usuário.

## Instruções de Uso

1. **Configuração do Ambiente**:
   - Instale a IDE Arduino ou PlatformIO.
   - Adicione a biblioteca `WiFi.h` ao seu ambiente de desenvolvimento.

2. **Configuração do Projeto**:
   - Abra o projeto na IDE.
   - Substitua os valores das variáveis `ssid` e `password` pelo nome e senha da sua rede Wi-Fi.

3. **Upload para o ESP32**:
   - Conecte o ESP32 ao computador.
   - Selecione a porta correta na IDE e faça o upload do código para o ESP32.

4. **Testar o Servidor Web**:
   - Abra o Monitor Serial para verificar o IP atribuído ao ESP32.
   - Acesse o IP do ESP32 no seu navegador para visualizar a página HTML exibida.

## Exemplo de Código

```cpp
#include <WiFi.h> // Inclui a biblioteca para conectar o ESP32 a redes Wi-Fi.

// Armazena nome e senha da rede Wi-Fi para conectar o ESP32
const char* ssid = "Internet2.4"; // Nome da rede Wi-Fi
const char* password = "Senha2.4"; // Senha da rede Wi-Fi

// Inicializa o servidor
WiFiServer server(80); // Cria um objeto de servidor que escuta na porta 80.

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com a taxa de 9600 bauds
  WiFi.begin(ssid, password); // Conecta à rede Wi-Fi

  // Aguarda até que o ESP32 esteja conectado à rede Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); // Espera 1 segundo antes de tentar novamente
    Serial.print("."); // Indica que está tentando conectar
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Imprime o IP do ESP32

  server.begin(); // Inicializa o servidor
}

void loop() {
  WiFiClient client = server.available(); // Verifica se há um cliente conectado

  if (client) { // Se um cliente está conectado
    Serial.println("New Client");
    String currentLine = ""; // Armazena a linha atual do pedido HTTP

    while (client.connected()) { // Enquanto o cliente estiver conectado
      if (client.available()) { // Se há dados disponíveis do cliente
        char c = client.read(); // Lê um caractere do cliente

        if (c == '\n') { // Se o caractere lido é uma nova linha
          if (currentLine.length() == 0) { // Se a linha está vazia (fim do pedido HTTP)
            // Envia a resposta HTTP ao cliente
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html lang=\"en\">");
            client.println("<head>");
            client.println("  <meta charset=\"UTF-8\">");
            client.println("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("  <title>ESP32 Web Server</title>");
            client.println("  <style>");
            client.println("    body {");
            client.println("      font-family: Arial, sans-serif;");
            client.println("      text-align: center;");
            client.println("      margin: 0;");
            client.println("      padding: 0;");
            client.println("      background-color: #e0f7fa;");
            client.println("    }");
            client.println("    h1 {");
            client.println("      color: #004d40;");
            client.println("    }");
            client.println("    p {");
            client.println("      font-size: 18px;");
            client.println("      font-weight: bold;");
            client.println("      font-style: italic;");
            client.println("    }");
            client.println("  </style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Bem vindo ao primeiro projeto com ESP32</h1>");
            client.println("<p>Hello, World!</p>");
            client.println("</body>");
            client.println("</html>");
            break; // Sai do loop de leitura do cliente
          } else {
            currentLine = ""; // Limpa a linha atual se não estiver vazia
          }
        } else if (c != '\r') {
          currentLine += c; // Adiciona o caractere à linha atual
        }
      }
    }

    client.stop(); // Fecha a conexão com o cliente
    Serial.println("Client Disconnected"); // Mensagem indicando que o cliente foi desconectado
  }
}
