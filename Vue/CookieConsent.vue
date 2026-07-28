<template>
  <Transition name="banner">
    <div v-if="visible" class="cookie-consent">
      <div class="cookie-content">
        <p>
          We use cookies to improve your experience. By continuing, you agree to our
          <a href="/privacy">Privacy Policy</a>.
        </p>
        <div class="cookie-actions">
          <button class="btn-accept" @click="accept">Accept All</button>
          <button class="btn-decline" @click="decline">Decline</button>
        </div>
      </div>
    </div>
  </Transition>
</template>

<script setup>
import { ref, onMounted } from 'vue'

const visible = ref(false)

const emit = defineEmits(['accept', 'decline'])

onMounted(() => {
  const consent = localStorage.getItem('cookie-consent')
  if (!consent) {
    visible.value = true
  }
})

const accept = () => {
  localStorage.setItem('cookie-consent', 'accepted')
  visible.value = false
  emit('accept')
}

const decline = () => {
  localStorage.setItem('cookie-consent', 'declined')
  visible.value = false
  emit('decline')
}
</script>

<style scoped>
.cookie-consent {
  position: fixed;
  bottom: 0;
  left: 0;
  right: 0;
  background: #2c3e50;
  color: white;
  padding: 1rem 1.5rem;
  z-index: 5000;
  box-shadow: 0 -2px 12px rgba(0,0,0,0.15);
  font-family: Arial, sans-serif;
}
.cookie-content {
  max-width: 800px;
  margin: 0 auto;
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 1.5rem;
  flex-wrap: wrap;
}
.cookie-content p {
  margin: 0;
  font-size: 0.9rem;
  flex: 1;
}
.cookie-content a {
  color: #42b883;
  text-decoration: underline;
}
.cookie-actions {
  display: flex;
  gap: 0.5rem;
  flex-shrink: 0;
}
.btn-accept, .btn-decline {
  padding: 0.45rem 1.25rem;
  border: none;
  border-radius: 6px;
  cursor: pointer;
  font-size: 0.85rem;
  font-family: inherit;
}
.btn-accept {
  background: #42b883;
  color: white;
}
.btn-accept:hover {
  opacity: 0.85;
}
.btn-decline {
  background: transparent;
  color: #ccc;
  border: 1px solid #666;
}
.btn-decline:hover {
  background: rgba(255,255,255,0.08);
}
.banner-enter-active, .banner-leave-active {
  transition: transform 0.3s ease, opacity 0.3s ease;
}
.banner-enter-from, .banner-leave-to {
  transform: translateY(100%);
  opacity: 0;
}
</style>
