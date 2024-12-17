<template>
  <div class="button-container">
    <button class="button button1" @click="publish('1')" role="button">ON</button>
    <button class="button button2" @click="publish('0')" role="button">OFF</button>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import client from './ConnectionForm.vue'
import logMessages from './ConnectionForm.vue'

const topic = ref('esp/led');

// Publikowanie wiadomości
function publish(message: string) {
  if (!client || !client.isConnected()) {
    logMessages.value.push("Klient nie jest połączony.");
    return;
  }

  if (!message) {
    logMessages.value.push("Wiadomość jest pusta.");
    return;
  }

  const topicName = topic.value || "default/topic";
  client.send(topicName, message);
  logMessages.value.push(`Wiadomość wysłana do tematu ${topicName}`);
}
</script>

<style scoped>
.button-container {
  display: flex;
  justify-content: center;
  align-items: center;
}

.button {
  background-color: #04AA6D;
  border: none;
  color: white;
  padding: 16px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 8px 10%;
  transition-duration: 0.4s;
  cursor: pointer;
}
.button1 {
  background-color: #04aa6d49;
  color: black;
  border: 2px solid #04AA6D;
}
.button2 {
  background-color: #aa040442;
  color: black;
  border: 2px solid #aa0404;
}
.button:hover {
  background-color: #04AA6D;
  color: white;
}
.button2:hover {
  background-color: #aa0404;
  color: white;
}
</style>
