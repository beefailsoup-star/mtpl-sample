<template>
  <div class="error-boundary">
    <slot v-if="!hasError" />
    <div v-else class="error-ui">
      <div class="error-icon">&#9888;</div>
      <h2>Something went wrong</h2>
      <p>{{ errorMessage }}</p>
      <button class="retry-btn" @click="reset">Try Again</button>
    </div>
  </div>
</template>

<script setup>
import { ref, onErrorCaptured } from 'vue'

const props = defineProps({
  errorMessage: { type: String, default: 'An unexpected error occurred. Please try again.' }
})

const hasError = ref(false)

onErrorCaptured((err, instance, info) => {
  hasError.value = true
  console.error('ErrorBoundary caught:', err, info)
  return false
})

const reset = () => {
  hasError.value = false
}
</script>

<style scoped>
.error-boundary {
  font-family: Arial, sans-serif;
}
.error-ui {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  padding: 3rem 2rem;
  text-align: center;
  background: #fff5f5;
  border: 1px solid #fecaca;
  border-radius: 12px;
}
.error-icon {
  font-size: 3rem;
  margin-bottom: 0.5rem;
}
.error-ui h2 {
  margin: 0 0 0.5rem;
  color: #991b1b;
  font-size: 1.3rem;
}
.error-ui p {
  margin: 0 0 1.25rem;
  color: #b91c1c;
  font-size: 0.95rem;
  max-width: 400px;
}
.retry-btn {
  padding: 0.5rem 1.5rem;
  background: #dc2626;
  color: white;
  border: none;
  border-radius: 6px;
  cursor: pointer;
  font-size: 0.9rem;
  font-family: inherit;
}
.retry-btn:hover {
  background: #b91c1c;
}
</style>
