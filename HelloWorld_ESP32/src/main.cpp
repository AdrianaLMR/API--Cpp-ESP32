#include <WiFi.h> // Inclui a biblioteca para conectar o ESP32 a redes Wi-Fi.

// Armazena nome e senha da rede Wi-Fi para conectar o ESP32
const char *ssid = "Nome da rede Wi-Fi";  // Nome da rede Wi-Fi (substitua pelo nome da sua rede Wi-Fi)
const char *password = "Senha da rede Wi-Fi"; // Senha da rede Wi-Fi (substitua pela senha da sua rede Wi-Fi)

// Inicializa o servidor
WiFiServer server(80); // Cria um objeto de servidor que escuta na porta 80.

// Inicializando e Usando o Wi-Fi e o Servidor
void setup()
{
  Serial.begin(9600);         // Inicializa a comunicação serial com a taxa de 9600 bauds
  WiFi.begin(ssid, password); // Conecta à rede Wi-Fi usando o nome e a senha fornecidos

  // Aguarda até que o ESP32 esteja conectado à rede Wi-Fi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);       // Espera 1 segundo antes de tentar novamente
    Serial.print("."); // Imprime um ponto no Monitor Serial para indicar que está tentando conectar
  }

  Serial.println("Connected to WiFi"); // Mensagem indicando que a conexão Wi-Fi foi bem-sucedida
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Imprime o IP do ESP32 na rede

  server.begin(); // Inicializa o servidor
}

// Manipula conexões de cliente
void loop()
{
  WiFiClient client = server.available(); // Verifica se há um cliente conectado ao servidor

  if (client)
  {                               // Se um cliente está conectado
    Serial.println("New Client"); // Mensagem indicando que um novo cliente se conectou
    String currentLine = "";      // Variável para armazenar a linha atual do pedido HTTP

    while (client.connected())
    { // Enquanto o cliente estiver conectado
      if (client.available())
      {                         // Se há dados disponíveis do cliente
        char c = client.read(); // Lê um caractere do cliente

        if (c == '\n')
        { // Se o caractere lido é uma nova linha
          if (currentLine.length() == 0)
          { // Se a linha atual está vazia (indicando o final do pedido HTTP)
            // Envia a resposta HTTP ao cliente
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println(); // Linha em branco para separar os cabeçalhos do corpo
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
            client.println("      background-color: #dce6f1;");
            client.println("    }");
            client.println("    h1 {");
            client.println("      color: #003366;");
            client.println("      font-size: 2em;");
            client.println("    }");
            client.println("    ul {");
            client.println("      list-style-type: none;");
            client.println("      padding: 0;");
            client.println("    }");
            client.println("    li {");
            client.println("      margin: 10px 0;");
            client.println("      color: #003366;");
            client.println("    }");
            client.println("    p {");
            client.println("      font-size: 1.5em;");
            client.println("      font-weight: bold;");
            client.println("      font-style: italic;");
            client.println("    }");
            client.println("  </style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Bem vindo ao primeiro projeto com ESP32</h1>");
            client.println("<h2>Passo a passo do projeto:</h2>");
            client.println("<ul>");
            client.println("  <li>Configuração do ambiente de desenvolvimento e instalação dos drivers necessários e prepara o espaço de trabalho para interagir com APIs.</li>");
            client.println("  <li>Configuração do programa/projeto no IDE, incluindo a criação e configuração do projeto e prepara o código para usar APIs específicas.</li>");
            client.println("  <li>Conexão do ESP32 ao computador e seleção da porta serial correta e estabelece comunicação e possibilita debugging.</li>");
            client.println("  <li>Envio do código para o ESP32 e verificação da comunicação serial e testa a implementação do código e da API.</li>");
            client.println("  <li>Teste do Resultado no Navegador Web, Acessando o IP do ESP32 para Ver a Página com 'Hello, World' e verifica a funcionalidade da API de servidor web.</li>");
            client.println("</ul>");
            client.println("<p>Hello, World!</p>");
            client.println("</body>");
            client.println("</html>");
            break; // Sai do loop de leitura do cliente
          }
          else
          {
            currentLine = ""; // Limpa a linha atual se não estiver vazia
          }
        }
        else if (c != '\r')
        {
          currentLine += c; // Adiciona o caractere à linha atual
        }
      }
    }

    client.stop();                         // Fecha a conexão com o cliente
    Serial.println("Client Disconnected"); // Mensagem indicando que o cliente foi desconectado
  }
}
