#include <WiFi.h>
#include <WebServer.h>

// ===== CONFIGURAÇÃO DO AP =====
const char* apSSID = "ClawMachine_AP";
const char* apPASS = "12345678";

// ===== SERVIDOR =====
WebServer server(80);

// ===== PINOS DOS MOTORES =====
#define MOTOR_X_FRENTE 26
#define MOTOR_Y_FRENTE 27
#define MOTOR_X_TRAS 33
#define MOTOR_Y_TRAS 32
#define MOTOR_Z 15
#define MOTOR_GARRA 16
#define enable1Pin 14
#define FDC_NEGATIVO_Y  14
#define FDC_POSITIVO_Y  14
#define FDC_NEGATIVO_X  14
#define FDC_POSITIVO_X  14
#define FDC_NEGATIVO_Z  14

const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;

// ===== ESTADOS =====
String direcaoAtiva = "";
bool garraAberta = true;

// ===== FUNÇÃO PARA ADICIONAR CABEÇALHOS CORS =====
void addCORS() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

// ===== HANDLER PARA REQUISIÇÕES OPTIONS =====
void handleOptions() {
  addCORS();
  server.send(204); // Sem conteúdo, apenas confirma o preflight
}

// ===== FUNÇÕES AUXILIARES =====
void pararTodos() {
  digitalWrite(MOTOR_X_FRENTE, LOW);
  digitalWrite(MOTOR_Y_FRENTE, LOW);
  digitalWrite(MOTOR_X_TRAS, LOW);
  digitalWrite(MOTOR_Y_TRAS, LOW);
  digitalWrite(MOTOR_Z, LOW);
  digitalWrite(MOTOR_GARRA, LOW);
  direcaoAtiva = "";
  Serial.println(">> Todos motores parados");
}

// ===== HANDLERS =====
void aumentarX() {
  pararTodos();
  digitalWrite(MOTOR_X_FRENTE, HIGH);
  digitalWrite(MOTOR_X_TRAS, LOW);
  direcaoAtiva = "X+";
  Serial.println("Movendo eixo X para frente");
  addCORS();
  server.send(200, "text/plain", "X aumentando");
}

void diminuirX() {
  pararTodos();
  digitalWrite(MOTOR_X_FRENTE, LOW);
  digitalWrite(MOTOR_X_TRAS, HIGH);
  direcaoAtiva = "X-";
  delay(500);
  Serial.println("Movendo eixo X para trás");
  addCORS();
  server.send(200, "text/plain", "X diminuindo");
}

void aumentarY() {
  pararTodos();
  digitalWrite(MOTOR_Y_FRENTE, HIGH);
  digitalWrite(MOTOR_Y_TRAS, LOW);
  direcaoAtiva = "Y+";
  Serial.println("Movendo eixo Y para direita");
  addCORS();
  server.send(200, "text/plain", "Y aumentando");
}

void diminuirY() {
  pararTodos();
  digitalWrite(MOTOR_Y_FRENTE, LOW);
  digitalWrite(MOTOR_Y_TRAS, HIGH);
  direcaoAtiva = "Y-";
  Serial.println("Movendo eixo Y para esquerda");
  addCORS();
  server.send(200, "text/plain", "Y diminuindo");
}

void subirGarra() {
  pararTodos();
  digitalWrite(MOTOR_Z, HIGH);
  direcaoAtiva = "Z+";
  Serial.println("Subindo garra");
  addCORS();
  server.send(200, "text/plain", "Subindo garra");
}

void descerGarra() {
  pararTodos();
  digitalWrite(MOTOR_Z, HIGH);
  direcaoAtiva = "Z-";
  Serial.println("Descendo garra");
  addCORS();
  server.send(200, "text/plain", "Descendo garra");
}

void abrirGarra() {
  pararTodos();
  digitalWrite(MOTOR_GARRA, HIGH);
  garraAberta = true;
  direcaoAtiva = "Garra abrindo";
  Serial.println("Abrindo garra");
  delay(1000);  // tempo para abrir
  digitalWrite(MOTOR_GARRA, LOW);
  direcaoAtiva = "";
  addCORS();
  server.send(200, "text/plain", "Garra aberta");
}

void fecharGarra() {
  pararTodos();
  digitalWrite(MOTOR_GARRA, HIGH);
  garraAberta = false;
  direcaoAtiva = "Garra fechando";
  Serial.println("Fechando garra");
  delay(1000);  // tempo para fechar
  digitalWrite(MOTOR_GARRA, LOW);
  direcaoAtiva = "";
  addCORS();
  server.send(200, "text/plain", "Garra fechada");
}

void parar() {
  pararTodos();
  addCORS();
  server.send(200, "text/plain", "Parado");
}

void status() {
  String s = "Ativo: " + direcaoAtiva + " | Garra: " + (garraAberta ? "aberta" : "fechada");
  addCORS();
  server.send(200, "text/plain", s);
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  // Configura pinos dos motores
  pinMode(MOTOR_X_FRENTE, OUTPUT);
  pinMode(MOTOR_Y_FRENTE, OUTPUT);
  pinMode(MOTOR_X_TRAS, OUTPUT);
  pinMode(MOTOR_Y_TRAS, OUTPUT);
  pinMode(MOTOR_Z, OUTPUT);
  pinMode(MOTOR_GARRA, OUTPUT);
  pinMode(FIM_DE_CURSO, INPUT_PULLUP);
  pararTodos();

    // configure LEDC PWM
  ledcAttachChannel(enable1Pin, freq, resolution, pwmChannel);

  // Cria o Access Point
  WiFi.softAP(apSSID, apPASS);
  Serial.print("Access Point ativo: ");
  Serial.println(WiFi.softAPIP());

  // Endpoints de controle
  server.on("/Xaumentar", HTTP_POST, aumentarX);
  server.on("/Xdiminuir", HTTP_POST, diminuirX);
  server.on("/Yaumentar", HTTP_POST, aumentarY);
  server.on("/Ydiminuir", HTTP_POST, diminuirY);
  server.on("/Zsubir", HTTP_POST, subirGarra);
  server.on("/Zdescer", HTTP_POST, descerGarra);
  server.on("/garraAbrir", HTTP_POST, abrirGarra);
  server.on("/garraFechar", HTTP_POST, fecharGarra);
  server.on("/parar", HTTP_POST, parar);
  server.on("/status", HTTP_GET, status);

  // ===== TRATAMENTO DE CORS (pré-voo OPTIONS) =====
  server.on("/Xaumentar", HTTP_OPTIONS, handleOptions);
  server.on("/Xdiminuir", HTTP_OPTIONS, handleOptions);
  server.on("/Yaumentar", HTTP_OPTIONS, handleOptions);
  server.on("/Ydiminuir", HTTP_OPTIONS, handleOptions);
  server.on("/Zsubir", HTTP_OPTIONS, handleOptions);
  server.on("/Zdescer", HTTP_OPTIONS, handleOptions);
  server.on("/garraAbrir", HTTP_OPTIONS, handleOptions);
  server.on("/garraFechar", HTTP_OPTIONS, handleOptions);
  server.on("/parar", HTTP_OPTIONS, handleOptions);
  server.on("/status", HTTP_OPTIONS, handleOptions);

  // Resposta padrão para endpoints inexistentes
  server.onNotFound([]() {
    addCORS();
    server.send(404, "text/plain", "Comando inválido");
  });

  server.begin();
  Serial.println("Servidor iniciado");
}

// ===== LOOP =====
void loop() {
  server.handleClient();
}