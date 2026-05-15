import React, { useRef, useState } from "react";
import { View, StyleSheet, Text, Pressable } from "react-native";

const ip = "192.168.4.1"; // IP do Access Point da ESP32

export default function DPadScreen() {
  const lastCmd = useRef("");

  // Envia comando para ESP
  function send(cmd: string) {
    if (lastCmd.current === cmd) return;
    lastCmd.current = cmd;

    fetch(`http://${ip}/${cmd}`, { method: "POST" })
      .catch(() => {});
  }

  // Parar motores
  function stop() {
    lastCmd.current = "";
    fetch(`http://${ip}/parar`, { method: "POST" })
      .catch(() => {});
  }

  return (
    <View style={styles.container}>
      <Text style={styles.title}>Controle da Garra</Text>

      {/* D-PAD */}
      <View style={styles.dpad}>
        {/* CIMA = Zsubir */}
        <Pressable
          style={[styles.arrow, styles.up]}
          onPressIn={() => send("Xaumentar")}
          onPressOut={stop}
        >
          <Text style={styles.arrowText}>▵</Text>
        </Pressable>

        {/* ESQUERDA = Ydiminuir */}
        <Pressable
          style={[styles.arrow, styles.left]}
          onPressIn={() => send("Ydiminuir")}
          onPressOut={stop}
        >
          <Text style={styles.arrowText}>◃</Text>
        </Pressable>

        {/* DIREITA = Yaumentar */}
        <Pressable
          style={[styles.arrow, styles.right]}
          onPressIn={() => send("Yaumentar")}
          onPressOut={stop}
        >
          <Text style={styles.arrowText}>▹</Text>
        </Pressable>

        {/* BAIXO = Zdescer */}
        <Pressable
          style={[styles.arrow, styles.down]}
          onPressIn={() => send("Xdiminuir")}
          onPressOut={stop}
        >
          <Text style={styles.arrowText}>▿</Text>
        </Pressable>
      </View>

      {/* Movimento X */}
      <View style={styles.row}>
        <Pressable
          style={styles.xButton}
          onPressIn={() => send("fazerJogada")}
          onPressOut={stop}
        >
          <Text style={styles.buttonText}>Fazer Jogada</Text>
        </Pressable>
      </View>

      {/* Movimento X */}
      <View style={styles.row}>
        <Pressable
          style={styles.xButton}
          onPressIn={() => send("garraAbrir")}
          onPressOut={stop}
        >
          <Text style={styles.buttonText}>Abrir Garra</Text>
        </Pressable>
      </View>

      {/* Movimento X */}
      <View style={styles.row}>
        <Pressable
          style={styles.xButton}
          onPressIn={() => send("garraFechar")}
          onPressOut={stop}
        >
          <Text style={styles.buttonText}>Fechar Garra</Text>
        </Pressable>
      </View>

      {/* Parar */}
      <Pressable style={styles.stopButton} onPressIn={() => send("parar")} onPressOut={stop}>
        <Text style={styles.stopText}>PARAR</Text>
      </Pressable>
    </View>
  );
}

// ======================
//        ESTILOS
// ======================

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#111",
    alignItems: "center",
    justifyContent: "center",
    padding: 20,
  },

  title: {
    color: "white",
    fontSize: 28,
    marginBottom: 25,
  },

  dpad: {
    width: 200,
    height: 200,
    position: "relative",
    marginBottom: 40,
  },

  arrow: {
    backgroundColor: "#1e4468ff",
    width: 70,
    height: 70,
    borderRadius: 10,
    justifyContent: "center",
    alignItems: "center",
    position: "absolute",
  },

  arrowText: {
    color: "white",
    fontSize: 25,
    fontWeight: "bold",
  },

  up:   { top: 0, left: "50%", marginLeft: -35 },
  down: { bottom: 0, left: "50%", marginLeft: -35 },
  left: { left: 0, top: "50%", marginTop: -35 },
  right:{ right: 0, top: "50%", marginTop: -35 },

  row: {
    flexDirection: "row",
    gap: 20,
    marginBottom: 25,
  },

  xButton: {
    backgroundColor: "#369923ff",
    paddingVertical: 12,
    paddingHorizontal: 28,
    borderRadius: 10,
  },

  clawButton: {
    backgroundColor: "#666",
    paddingVertical: 12,
    paddingHorizontal: 25,
    borderRadius: 10,
  },

  buttonText: {
    color: "white",
    fontSize: 18,
  },

  stopButton: {
    backgroundColor: "red",
    paddingVertical: 14,
    paddingHorizontal: 45,
    borderRadius: 10,
    marginTop: 40,
  },

  stopText: {
    color: "white",
    fontSize: 20,
    fontWeight: "bold",
  },
});