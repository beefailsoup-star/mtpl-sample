<template>
  <div class="chart-pie">
    <h3 v-if="title">{{ title }}</h3>
    <svg :viewBox="`0 0 ${size} ${size}`" :width="size" :height="size" xmlns="http://www.w3.org/2000/svg">
      <g :transform="`translate(${size/2}, ${size/2})`">
        <path
          v-for="(slice, i) in slices"
          :key="i"
          :d="slice.path"
          :fill="slice.color"
          stroke="white"
          stroke-width="2"
        >
          <title>{{ slice.label }}: {{ slice.value }} ({{ slice.percent }}%)</title>
        </path>
      </g>
    </svg>
    <div class="legend">
      <div v-for="(slice, i) in slices" :key="'legend-' + i" class="legend-item">
        <span class="legend-dot" :style="{ background: slice.color }"></span>
        <span class="legend-label">{{ slice.label }} ({{ slice.percent }}%)</span>
      </div>
    </div>
  </div>
</template>

<script setup>
import { computed } from 'vue'

const props = defineProps({
  data: { type: Array, required: true },
  labels: { type: Array, required: true },
  title: { type: String, default: '' },
  size: { type: Number, default: 250 },
  colors: { type: Array, default: () => ['#42b883', '#3498db', '#f39c12', '#e74c3c', '#9b59b6', '#1abc9c'] }
})

const total = computed(() => props.data.reduce((a, b) => a + b, 0))

const slices = computed(() => {
  let startAngle = 0
  return props.data.map((value, i) => {
    const percent = total.value ? Math.round((value / total.value) * 100) : 0
    const angle = total.value ? (value / total.value) * 360 : 0
    const endAngle = startAngle + angle
    const startRad = (startAngle - 90) * Math.PI / 180
    const endRad = (endAngle - 90) * Math.PI / 180
    const r = props.size / 3
    const x1 = r * Math.cos(startRad)
    const y1 = r * Math.sin(startRad)
    const x2 = r * Math.cos(endRad)
    const y2 = r * Math.sin(endRad)
    const largeArc = angle > 180 ? 1 : 0
    const path = value === total.value
      ? `M 0 0 L ${r} 0 A ${r} ${r} 0 1 1 ${-r} 0 A ${r} ${r} 0 1 1 ${r} 0 Z`
      : `M 0 0 L ${x1} ${y1} A ${r} ${r} 0 ${largeArc} 1 ${x2} ${y2} Z`
    startAngle = endAngle
    return { value, label: props.labels[i], percent, path, color: props.colors[i % props.colors.length] }
  })
})
</script>

<style scoped>
.chart-pie {
  display: inline-flex;
  flex-direction: column;
  align-items: center;
  font-family: Arial, sans-serif;
}
.chart-pie h3 {
  margin: 0 0 0.5rem;
  font-size: 1rem;
  color: #2c3e50;
}
.legend {
  display: flex;
  flex-wrap: wrap;
  gap: 0.3rem 0.75rem;
  margin-top: 0.5rem;
}
.legend-item {
  display: flex;
  align-items: center;
  gap: 0.25rem;
}
.legend-dot {
  width: 10px;
  height: 10px;
  border-radius: 50%;
  flex-shrink: 0;
}
.legend-label {
  font-size: 0.8rem;
  color: #555;
}
</style>
