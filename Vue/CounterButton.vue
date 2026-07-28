<template>
  <div class="counter-button">
    <span class="count">Count: {{ count }}</span>
    <button class="btn" @click="increment">Increment</button>
    <button class="btn btn-secondary" @click="reset">Reset</button>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const count = ref(0)
const increment = () => count.value++
const reset = () => count.value = 0
</script>

<style scoped>
.counter-button {
  display: flex;
  align-items: center;
  gap: 1rem;
  padding: 1rem;
}
.count {
  font-size: 1.5rem;
  font-weight: bold;
  min-width: 6rem;
}
.btn {
  padding: 0.5rem 1.5rem;
  border: none;
  border-radius: 6px;
  background: #42b883;
  color: white;
  cursor: pointer;
  font-size: 1rem;
}
.btn-secondary {
  background: #6c757d;
}
.btn:hover {
  opacity: 0.85;
}
</style>
