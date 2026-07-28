<template>
  <div class="loading-spinner" :class="[size, overlay ? 'overlay' : '']" v-if="visible">
    <div class="spinner" :style="{ borderTopColor: color }"></div>
    <span v-if="text" class="spinner-text">{{ text }}</span>
  </div>
</template>

<script setup>
defineProps({
  visible: { type: Boolean, default: true },
  size: { type: String, default: 'md', validator: v => ['sm', 'md', 'lg'].includes(v) },
  color: { type: String, default: '#42b883' },
  text: { type: String, default: '' },
  overlay: { type: Boolean, default: false }
})
</script>

<style scoped>
.loading-spinner {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  gap: 0.75rem;
  font-family: Arial, sans-serif;
}
.loading-spinner.overlay {
  position: fixed;
  inset: 0;
  background: rgba(255,255,255,0.8);
  z-index: 9999;
}
.spinner {
  border: 3px solid #e0e0e0;
  border-radius: 50%;
  animation: spin 0.75s linear infinite;
}
.sm .spinner { width: 20px; height: 20px; border-width: 2px; }
.md .spinner { width: 36px; height: 36px; border-width: 3px; }
.lg .spinner { width: 52px; height: 52px; border-width: 4px; }
.spinner-text {
  color: #666;
  font-size: 0.9rem;
}
@keyframes spin {
  to { transform: rotate(360deg); }
}
</style>
