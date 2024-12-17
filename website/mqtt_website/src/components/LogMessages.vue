<template>
  <div id="messages">
    <div v-for="message in logMessages" :key="message">{{ message }}</div>
  </div>
</template>

<script setup lang="ts">
import logMessages from './ConnectionForm.vue'
</script>

<style scoped>
#messages {
  height: 200px;
  overflow-y: auto;
  margin: 5px;
  background-color: rgba(0, 0, 0, 0.5);
  backdrop-filter: blur(10px);
  -webkit-backdrop-filter: blur(10px);
  border-radius: 10px;
  padding: 10px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.3);
}

#messages::-webkit-scrollbar {
  width: 8px;
}

#messages::-webkit-scrollbar-thumb {
  background-color: rgba(255, 255, 255, 0.6);
  border-radius: 4px;
}

#messages::-webkit-scrollbar-thumb:hover {
  background-color: rgba(255, 255, 255, 0.8);
}

#messages::-webkit-scrollbar-track {
  background-color: transparent;
}
</style>
