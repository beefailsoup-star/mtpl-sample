<template>
  <div class="progress-bar">
    <div class="bar-track">
      <div
        class="bar-fill"
        :style="{ width: animatedValue + '%', background: color }"
      ></div>
    </div>
    <span v-if="showLabel" class="label">{{ animatedValue.toFixed(0) }}%</span>
  </div>
</template>

<script setup>
import { ref, watch } from 'vue'

const props = defineProps({
  value: { type: Number, default: 0 },
  color: { type: String, default: '#42b883' },
  showLabel: { type: Boolean, default: true },
  duration: { type: Number, default: 300 }
})

const animatedValue = ref(0)
let rafId = null

watch(() => props.value, (newVal) => {
  cancelAnimationFrame(rafId)
  const start = animatedValue.value
  const diff = newVal - start
  const startTime = performance.now()
  const animate = (now) => {
    const elapsed = now - startTime
    const progress = Math.min(elapsed / props.duration, 1)
    animatedValue.value = start + diff * easeOutCubic(progress)
    if (progress < 1) {
      rafId = requestAnimationFrame(animate)
    }
  }
  rafId = requestAnimationFrame(animate)
})

const easeOutCubic = (t) => 1 - Math.pow(1 - t, 3)
</script>

<style scoped>
.progress-bar {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  font-family: Arial, sans-serif;
}
.bar-track {
  flex: 1;
  height: 10px;
  background: #e9ecef;
  border-radius: 5px;
  overflow: hidden;
}
.bar-fill {
  height: 100%;
  border-radius: 5px;
  transition: width 0.1s linear;
}
.label {
  font-size: 0.85rem;
  font-weight: 600;
  color: #555;
  min-width: 3rem;
}
</style>
