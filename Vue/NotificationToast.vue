<template>
  <Teleport to="body">
    <TransitionGroup name="toast" tag="div" class="toast-container">
      <div
        v-for="notification in notifications"
        :key="notification.id"
        class="toast"
        :class="notification.type"
      >
        <span class="toast-msg">{{ notification.message }}</span>
        <button class="toast-close" @click="dismiss(notification.id)">&times;</button>
      </div>
    </TransitionGroup>
  </Teleport>
</template>

<script setup>
import { ref } from 'vue'

const notifications = ref([])
let nextId = 1

const add = (message, type = 'info', duration = 4000) => {
  const id = nextId++
  notifications.value.push({ id, message, type })
  if (duration > 0) {
    setTimeout(() => dismiss(id), duration)
  }
}

const dismiss = (id) => {
  notifications.value = notifications.value.filter(n => n.id !== id)
}

defineExpose({ add, dismiss })
</script>

<style scoped>
.toast-container {
  position: fixed;
  top: 1rem;
  right: 1rem;
  z-index: 3000;
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  max-width: 360px;
}
.toast {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 0.85rem 1rem;
  border-radius: 8px;
  color: white;
  font-family: Arial, sans-serif;
  font-size: 0.95rem;
  box-shadow: 0 4px 12px rgba(0,0,0,0.15);
}
.toast.info { background: #3498db; }
.toast.success { background: #2ecc71; }
.toast.warning { background: #f39c12; }
.toast.error { background: #e74c3c; }
.toast-msg { flex: 1; }
.toast-close {
  background: none;
  border: none;
  color: rgba(255,255,255,0.8);
  font-size: 1.2rem;
  cursor: pointer;
  margin-left: 0.75rem;
}
.toast-enter-active, .toast-leave-active {
  transition: all 0.3s ease;
}
.toast-enter-from {
  opacity: 0;
  transform: translateX(100%);
}
.toast-leave-to {
  opacity: 0;
  transform: translateX(100%);
}
</style>
