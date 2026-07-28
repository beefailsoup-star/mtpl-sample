<template>
  <div class="radio-button-group">
    <label
      v-for="option in options"
      :key="option.value"
      class="radio-item"
      :class="{ selected: modelValue === option.value, disabled: option.disabled }"
    >
      <input
        type="radio"
        :value="option.value"
        :checked="modelValue === option.value"
        :disabled="option.disabled"
        @change="select(option.value)"
      />
      <span class="radio-circle"></span>
      <span class="radio-label">{{ option.label }}</span>
    </label>
  </div>
</template>

<script setup>
defineProps({
  options: { type: Array, required: true },
  modelValue: { type: [String, Number], default: '' }
})

const emit = defineEmits(['update:modelValue'])

const select = (value) => emit('update:modelValue', value)
</script>

<style scoped>
.radio-button-group {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  font-family: Arial, sans-serif;
}
.radio-item {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  cursor: pointer;
  padding: 0.35rem 0;
}
.radio-item.disabled {
  opacity: 0.5;
  cursor: not-allowed;
}
.radio-item input {
  position: absolute;
  opacity: 0;
  width: 0;
  height: 0;
}
.radio-circle {
  width: 18px;
  height: 18px;
  border: 2px solid #ccc;
  border-radius: 50%;
  position: relative;
  flex-shrink: 0;
  transition: border-color 0.2s;
}
.radio-circle::after {
  content: '';
  position: absolute;
  top: 3px;
  left: 3px;
  width: 8px;
  height: 8px;
  border-radius: 50%;
  background: #42b883;
  transform: scale(0);
  transition: transform 0.2s;
}
.radio-item.selected .radio-circle {
  border-color: #42b883;
}
.radio-item.selected .radio-circle::after {
  transform: scale(1);
}
.radio-label {
  font-size: 0.95rem;
  color: #333;
}
</style>
