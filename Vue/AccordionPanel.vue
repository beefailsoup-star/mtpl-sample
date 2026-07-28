<template>
  <div class="accordion-panel" :class="{ open: isOpen }">
    <button class="accordion-header" @click="toggle">
      <span>{{ title }}</span>
      <span class="icon">{{ isOpen ? '−' : '+' }}</span>
    </button>
    <Transition name="accordion" @enter="onEnter" @leave="onLeave">
      <div v-show="isOpen" class="accordion-body" ref="bodyRef">
        <div class="accordion-content">
          <slot />
        </div>
      </div>
    </Transition>
  </div>
</template>

<script setup>
import { ref } from 'vue'

defineProps({
  title: { type: String, required: true }
})

const isOpen = ref(false)
const bodyRef = ref(null)

const toggle = () => { isOpen.value = !isOpen.value }

const onEnter = (el) => {
  el.style.height = 'auto'
  const h = el.scrollHeight
  el.style.height = '0px'
  requestAnimationFrame(() => {
    el.style.height = h + 'px'
  })
}

const onLeave = (el) => {
  el.style.height = el.scrollHeight + 'px'
  requestAnimationFrame(() => {
    el.style.height = '0px'
  })
}
</script>

<style scoped>
.accordion-panel {
  border: 1px solid #ddd;
  border-radius: 6px;
  margin-bottom: 0.5rem;
  overflow: hidden;
}
.accordion-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  width: 100%;
  padding: 0.85rem 1rem;
  background: #f9f9f9;
  border: none;
  cursor: pointer;
  font-size: 1rem;
  color: #2c3e50;
  text-align: left;
}
.accordion-header:hover {
  background: #f0faf5;
}
.icon {
  font-size: 1.2rem;
  font-weight: bold;
  color: #42b883;
}
.accordion-body {
  overflow: hidden;
  transition: height 0.3s ease;
}
.accordion-content {
  padding: 1rem;
  border-top: 1px solid #eee;
}
.accordion-enter-active, .accordion-leave-active {
  transition: height 0.3s ease;
}
</style>
