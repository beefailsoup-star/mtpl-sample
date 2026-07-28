<template>
  <div class="chart-bar">
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
      <rect
        v-for="(bar, i) in normalizedData"
        :key="i"
        :x="barX(i)"
        :y="barY(bar)"
        :width="barWidth"
        :height="barHeight(bar)"
        :fill="bar.color || '#42b883'"
        rx="3"
      >
        <title>{{ labels[i] }}: {{ data[i] }}</title>
      </rect>
      <text
        v-for="(label, i) in labels"
        :key="'label-' + i"
        :x="barX(i) + barWidth / 2"
        :y="height - margin.bottom + 16"
        text-anchor="middle"
        font-size="10"
        fill="#666"
      >
        {{ label }}
      </text>
      <text
        v-for="(bar, i) in normalizedData"
        :key="'val-' + i"
        :x="barX(i) + barWidth / 2"
        :y="barY(bar) - 5"
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
  height: { type: Number, default: 250 }
})

const margin = { top: 20, right: 20, bottom: 40, left: 20 }
const gridLines = 5

const maxVal = computed(() => Math.max(...props.data, 1))
const chartH = computed(() => props.height - margin.top - margin.bottom)
const chartW = computed(() => props.width - margin.left - margin.right)

const normalizedData = computed(() =>
  props.data.map((v, i) => ({
    value: v / maxVal.value,
    color: undefined
  }))
)

const barWidth = computed(() => Math.max(8, chartW.value / props.data.length * 0.6))

const yPos = (i) => margin.top + (chartH.value / gridLines) * (gridLines - i)

const barX = (i) => margin.left + (chartW.value / props.data.length) * i + (chartW.value / props.data.length - barWidth.value) / 2

const barY = (bar) => margin.top + chartH.value * (1 - bar.value)

const barHeight = (bar) => chartH.value * bar.value
</script>

<style scoped>
.chart-bar {
  font-family: Arial, sans-serif;
}
.chart-bar h3 {
  margin: 0 0 0.5rem;
  font-size: 1rem;
  color: #2c3e50;
}
.chart-bar svg {
  display: block;
}
</style>
