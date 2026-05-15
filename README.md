# Sistema IoT para Controle de Máquina de Garra com ESP32

Projeto de TCC desenvolvido para o curso de Ciência da Computação pelo Instituto Federal do Paraná - Campus Pinhais com foco na modernização de uma máquina de garra convencional por meio de tecnologias IoT.

O sistema utiliza uma ESP32 como núcleo de controle e comunicação, permitindo o acionamento remoto da máquina através de um aplicativo móvel desenvolvido em React Native e uma interface web integrada.

---

## Funcionalidades

- Controle remoto da máquina via Wi-Fi
- Aplicativo móvel em React Native
- Comunicação HTTP REST
- Controle de motores DC com módulos L298N
- Sensores de fim de curso para proteção mecânica
- Sistema automático de jogada
- Geração de relatórios em CSV com LittleFS
- Operação em rede local utilizando ESP32 em modo Access Point

---

## Arquitetura do Sistema

```text
Aplicativo React Native / Interface Web
                 ↓
             HTTP REST
                 ↓
               ESP32
                 ↓
        Módulos L298N
                 ↓
       Motores e Sensores
```

---

## Tecnologias Utilizadas

### Hardware
- ESP32
- Motores DC
- L298N
- Sensores de fim de curso
- Sensor infravermelho
- Fonte 12V

### Software
- React Native
- TypeScript
- JavaScript
- HTML/CSS
- Arduino IDE
- LittleFS
  
---

## Aplicativo Mobile

O aplicativo foi desenvolvido utilizando React Native CLI com TypeScript.

A interface permite:
- movimentação nos eixos X e Y;
- controle da garra;
- execução automática da jogada;
- envio contínuo de comandos HTTP para a ESP32.

---

## Firmware ESP32

O firmware implementa:
- servidor HTTP embarcado;
- endpoints REST;
- controle dos motores;
- leitura dos sensores;
- proteção contra colisões;
- armazenamento de relatórios utilizando LittleFS.

---

## Relatórios e Monitoramento

Cada jogada é registrada automaticamente em um arquivo CSV contendo:
- identificador da jogada;
- data e horário;
- duração;
- resultado da captura.

---

## Resultados

Os testes apresentaram:
- baixa latência (< 50 ms);
- operação estável;
- alta confiabilidade;
- resposta em tempo real;
- proteção mecânica eficiente.

---

## Demonstração

O vídeo a seguir é uma demonstração do dispositivo (ainda não completo) funcionando em ambiente de teste.

[![Vídeo Demonstração](https://img.youtube.com/vi/watch?v=ewuswKGMqTA/0.jpg)](https://youtu.be/ewuswKGMqTA)

---

## Trabalhos Futuros

- integração com Firebase/AWS IoT;
- dashboards em nuvem;
- joystick contínuo;
- visão computacional;
- controle PID;
- sistema de autoteste.

---

## Autores

- Lucas de Oliveira Martins
- André Luis Grein
