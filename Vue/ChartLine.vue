<template>
  <div class="chart-line">
    <h3 v-if="title">{{ title }}</h3>
    <svg :viewBox="`0 0 ${width} ${height}`" :width="width" :height="height" xmlns="http://www.w3.org/2000/svg">
      <line
        v-for="i in gridLines"
        :key="'grid-' + i"
        :x1="margin.left"
        :y1="yPos(i)"
        :x2="width - margin.right"
        :y2="yPos(i)"
        stroke="#eee"
        stroke-width="1"
      />
      <polyline
        :points="linePoints"
        fill="none"
        stroke="#42b883"
        stroke-width="2.5"
        stroke-linejoin="round"
        stroke-linecap="round"
      />
      <circle
        v-for="(pt, i) in points"
        :key="i"
        :cx="pt.x"
        :cy="pt.y"
        r="4"
        fill="white"
        stroke="#42b883"
        stroke-width="2"
      >
        <title>{{ labels[i] }}: {{ data[i] }}</title>
      </circle>
      <text
        v-for="(label, i) in labels"
        :key="'xlabel-' + i"
        :x="points[i].x"
        :y="height - margin.bottom + 16"
        text-anchor="middle"
        font-size="10"
        fill="#666"
      >
        {{ label }}
      </text>
      <text
        v-for="(pt, i) in points"
        :key="'val-' + i"
        :x="pt.x"
        :y="pt.y - 10"
        text-anchor="middle"
        font-size="10"
        fill="#333"
      >
        {{ data[i] }}
      </text>
    </svg>
  </div>
</template>

<script setup>
import { computed } from 'vue'

const props = defineProps({
  data: { type: Array, required: true },
  labels: { type: Array, required: true },
  title: { type: String, default: '' },
  width: { type: Number, default: 400 },
  height: { type: Number, default: 220 }
})

const margin = { top: 20, right: 20, bottom: 40, left: 20 }
const gridLines = 5

const maxVal = computed(() => Math.max(...props.data, 1))
const chartH = computed(() => props.height - margin.top - margin.bottom)
const chartW = computed(() => props.width - margin.left - margin.right)

const points = computed(() =>
  props.data.map((v, i) => ({
    x: margin.left + (chartW.value / (props.data.length - 1 || 1)) * i,
    y: margin.top + chartH.value * (1 - v / maxVal.value)
  }))
)

const linePoints = computed(() => points.value.map(p => `${p.x},${p.y}`).join(' '))

const yPos = (i) => margin.top + (chartH.value / gridLines) * (gridLines - i)
</script>

<style scoped>
.chart-line {
  font-family: Arial, sans-serif;
}
.chart-line h3 {
  margin: 0 0 0.5rem;
  font-size: 1rem;
  color: #2c3e50;
}
.chart-line svg {
  display: block;
}
</style>
