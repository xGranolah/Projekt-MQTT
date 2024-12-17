<template>
  <div id="colorPicker"></div>
</template>

<script setup lang="ts">
import { onMounted } from 'vue'
import iro from '@jaames/iro';
import  publish  from './ControlButtons.vue'

let colorPickerRef: iro.ColorPicker | null = null;

onMounted(() => {
  colorPickerRef = new iro.ColorPicker("#colorPicker", {width: 280, color: "rgb(255, 0, 0)", borderWidth: 1, borderColor: "#fff",});

  if (colorPickerRef) {
    colorPickerRef.on(["color:init", "color:change"], function(color) {
      const hex = color.hexString;
      new publish(hex);
    });
  }
});

</script>

<style scoped>
#colorPicker {
  display: flex;
  justify-content: center;
  align-items: center;
}
</style>
