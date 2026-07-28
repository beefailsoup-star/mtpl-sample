<template>
  <div class="slider-input">
    <label v-if="label" class="slider-label">{{ label }}</label>
    <div class="slider-row">
      <span class="min-label">{{ min }}</span>
      <input
        type="range"
        :min="min"
        :max="max"
        :step="step"
        :value="modelValue"
        @input="update"
        class="range"
      />
      <span class="max-label">{{ max }}</span>
    </div>
    <div class="value-display">
      <span class="value">{{ formatValue(modelValue) }}</span>
    </div>
  </div>
</template>

<script setup>
const props = defineProps({
  modelValue: { type: Number, default: 50 },
  label: { type: String, default: '' },
  min: { type: Number, default: 0 },
  max: { type: Number, default: 100 },
  step: { type: Number, default: 1 },
  format: { type: Function, default: null }
})

const emit = defineEmits(['update:modelValue'])

const update = (e) => emit('update:modelValue', Number(e.target.value))

const formatValue = (v) => props.format ? props.format(v) : v
</script>

<style scoped>
.slider-input {
  font-family: Arial, sans-serif;
  max-width: 320px;
}
.slider-label {
  display: block;
  margin-bottom: 0.5rem;
  font-weight: 600;
  color: #34495e;
  font-size: 0.9rem;
}
.slider-row {
  display: flex;
  align-items: center;
  gap: 0.75rem;
}
.min-label, .max-label {
  font-size: 0.8rem;
  color: #999;
  min-width: 2rem;
}
.range {
  flex: 1;
  -webkit-appearance: none;
  appearance: none;
  height: 6px;
  background: #e0e0e0;
  border-radius: 3px;
  outline: none;
}
.range::-webkit-slider-thumb {
  -webkit-appearance: none;
  width: 18px;
  height: 18px;
  background: #42b883;
  border-radius: 50%;
  cursor: pointer;
  transition: transform 0.1s;
}
.range::-webkit-slider-thumb:hover {
  transform: scale(1.15);
}
.value-display {
  margin-top: 0.5rem;
  text-align: center;
}
.value {
  display: inline-block;
  padding: 0.2rem 0.75rem;
  background: #f0faf5;
  color: #2e7d32;
  border-radius: 4px;
  font-size: 0.85rem;
  font-weight: 600;
}
</style>
