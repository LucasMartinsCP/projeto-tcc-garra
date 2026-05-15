const ip = "192.168.4.1"; // IP da ESP32 em modo Access Point
const statusDiv = document.getElementById("status");
let bloqueado = false; // Evita comandos simultâneos

function sendCommand(endpoint) {
  if (bloqueado) return;
  bloqueado = true;

  fetch(`http://${ip}/${endpoint}`, { method: "POST" })
    .then(res => {
      if (res.ok) {
        statusDiv.textContent = `Comando enviado: ${endpoint}`;
      } else {
        statusDiv.textContent = `Erro ao enviar comando: ${endpoint}`;
      }
    })
    .catch(() => {
      statusDiv.textContent = "Erro: não conectado à ESP32";
    })
    .finally(() => {
      // Libera novos comandos após 300ms
      setTimeout(() => bloqueado = false, 300);
    });
}

// Mapeamento de botões de movimento
document.getElementById("btnFrente").addEventListener("mousedown", () => sendCommand("Xaumentar"));
document.getElementById("btnFrente").addEventListener("mouseup", () => sendCommand("parar"));

document.getElementById("btnTras").addEventListener("mousedown", () => sendCommand("Xdiminuir"));
document.getElementById("btnTras").addEventListener("mouseup", () => sendCommand("parar"));

document.getElementById("btnEsquerda").addEventListener("mousedown", () => sendCommand("Ydiminuir"));
document.getElementById("btnEsquerda").addEventListener("mouseup", () => sendCommand("parar"));

document.getElementById("btnDireita").addEventListener("mousedown", () => sendCommand("Yaumentar"));
document.getElementById("btnDireita").addEventListener("mouseup", () => sendCommand("parar"));

// Controle do eixo Z
document.getElementById("btnSubir").addEventListener("mousedown", () => sendCommand("Zsubir"));
document.getElementById("btnSubir").addEventListener("mouseup", () => sendCommand("parar"));

document.getElementById("btnDescer").addEventListener("mousedown", () => sendCommand("Zdescer"));
document.getElementById("btnDescer").addEventListener("mouseup", () => sendCommand("parar"));

// Garra (ação única por clique)
document.getElementById("btnAbrir").addEventListener("click", () => sendCommand("garraAbrir"));
document.getElementById("btnFechar").addEventListener("click", () => sendCommand("garraFechar"));

// Parar geral
document.getElementById("btnParar").addEventListener("click", () => sendCommand("parar"));

// Atualiza status a cada 2 segundos
setInterval(() => {
  fetch(`http://${ip}/status`)
    .then(res => res.text())
    .then(text => (statusDiv.textContent = `Status: ${text}`))
    .catch(() => (statusDiv.textContent = "Status: desconectado"));
}, 2000);