<template>
  <div class="color-picker">
    <label>{{ label }}</label>
    <div class="picker-row">
      <input type="color" :value="modelValue" @input="updateColor" />
      <input
        type="text"
        :value="modelValue"
        @input="updateFromText"
        maxlength="7"
        class="hex-input"
      />
      <div class="swatch" :style="{ background: modelValue }"></div>
    </div>
  </div>
</template>

<script setup>
const props = defineProps({
  modelValue: { type: String, default: '#42b883' },
  label: { type: String, default: 'Pick a color' }
})

const emit = defineEmits(['update:modelValue'])

const updateColor = (e) => emit('update:modelValue', e.target.value)

const updateFromText = (e) => {
  let val = e.target.value
  if (/^#[0-9a-fA-F]{0,6}$/.test(val)) {
    if (val.length === 7) {
      emit('update:modelValue', val)
    }
  }
}
</script>

<style scoped>
.color-picker {
  font-family: Arial, sans-serif;
}
.color-picker label {
  display: block;
  margin-bottom: 0.4rem;
  font-weight: 600;
  color: #34495e;
}
.picker-row {
  display: flex;
  align-items: center;
  gap: 0.75rem;
}
.picker-row input[type="color"] {
  width: 42px;
  height: 42px;
  border: none;
  padding: 2px;
  cursor: pointer;
  border-radius: 6px;
}
.hex-input {
  width: 90px;
  padding: 0.45rem;
  border: 1px solid #ccc;
  border-radius: 4px;
  font-family: monospace;
  font-size: 0.95rem;
  text-align: center;
}
.swatch {
  width: 36px;
  height: 36px;
  border-radius: 6px;
  border: 1px solid #ddd;
}
</style>
