<template>
  <div class="input-container">
    <div class="form-group">
      <input id="host" v-model="host" placeholder="Adres IP" class="input-field" />
    </div>
    <div class="form-group">
      <input id="port" v-model="port" type="number" placeholder="Port" min="0" max="65535" class="input-field" />
    </div>
    <div class="form-group">
      <input id="username" v-model="username" placeholder="Użytkownik" class="input-field" />
    </div>
    <div class="form-group">
      <input id="password" v-model="password" type="password" placeholder="Hasło" class="input-field" />
    </div>
    <button class="connect-button" @click="startConnect">Połącz</button>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import Paho from "paho-mqtt";

const host = ref('');
const port = ref('');
const username = ref('');
const password = ref('');
const topic = ref('esp/led');
const logMessages = ref<string[]>([]);

let client: Paho.Client | null = null;

interface ConnectionLostResponse {
  errorCode: number;
}

// Funkcja do rozpoczęcia połączenia MQTT
function startConnect() {
  const clientID = "clientID-" + Math.random().toString(36).substr(2, 9);

  if (!host.value || !port.value) {
    logMessages.value.push("Host lub port są puste. Proszę je uzupełnić.");
    return;
  }

  logMessages.value.push(`Connecting to ${host.value} on port ${port.value}`);
  client = new Paho.Client(host.value, Number(port.value), clientID);

  client.onConnectionLost = onConnectionLost;
  client.onMessageArrived = onMessageArrived;

  client.connect({
    onSuccess: onConnect,
    userName: username.value,
    password: password.value,
  });
}

// Obsługa utraty połączenia
function onConnectionLost(responseObject: ConnectionLostResponse) {
  logMessages.value.push("ERROR: Stracono połączenie");
  if (responseObject.errorCode !== 0) {
    // Handle the error code here
  }
}

// Obsługa odebrania wiadomości
function onMessageArrived(mqttMessage: globalThis.Paho.MQTT.Message) {
  logMessages.value.push(`Topic: ${mqttMessage.destinationName} | Message: ${mqttMessage.payloadString}`);
}

// Subskrypcja na temat po połączeniu
function onConnect() {
  if (!topic.value) {
    logMessages.value.push("Brak tematu do subskrypcji.");
    return;
  }
  logMessages.value.push(`Subscribing to topic ${topic.value}`);
  client?.subscribe(topic.value);
}
</script>

<style scoped>
.input-container {
  display: flex;
  gap: 5px;
  align-items: center;
  justify-content: center;
  margin: 20px 0;
  flex-wrap: wrap;
}

.form-group {
  flex: 1 1 auto;
  margin: 5px;
}

.input-field {
  width: 100%;
  padding: 5px;
  border: 1px solid #ccc;
  border-radius: 5px;
  font-size: 14px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  transition: border-color 0.3s, box-shadow 0.3s;
}

.input-field:focus {
  outline: none;
  border-color: #4CAF50;
  box-shadow: 0 2px 6px rgba(76, 175, 80, 0.4);
}

.connect-button {
  background-color: #4CAF50;
  color: white;
  border: none;
  padding: 10px 20px;
  font-size: 14px;
  border-radius: 5px;
  cursor: pointer;
  transition: background-color 0.3s, box-shadow 0.3s;
}

.connect-button:hover {
  background-color: #45a049;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.2);
}

.connect-button:active {
  background-color: #3e8e41;
}
</style>
