<template>
  <div class="checkbox-group">
    <label
      v-for="option in options"
      :key="option.value"
      class="checkbox-item"
      :class="{ checked: isChecked(option.value), disabled: option.disabled }"
    >
      <input
        type="checkbox"
        :value="option.value"
        :checked="isChecked(option.value)"
        :disabled="option.disabled"
        @change="toggle(option.value)"
      />
      <span class="checkbox-box">
        <span v-if="isChecked(option.value)" class="checkmark">&#10003;</span>
      </span>
      <span class="checkbox-label">{{ option.label }}</span>
    </label>
  </div>
</template>

<script setup>
const props = defineProps({
  options: { type: Array, required: true },
  modelValue: { type: Array, default: () => [] }
})

const emit = defineEmits(['update:modelValue'])

const isChecked = (value) => props.modelValue.includes(value)

const toggle = (value) => {
  const updated = isChecked(value)
    ? props.modelValue.filter(v => v !== value)
    : [...props.modelValue, value]
  emit('update:modelValue', updated)
}
</script>

<style scoped>
.checkbox-group {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  font-family: Arial, sans-serif;
}
.checkbox-item {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  cursor: pointer;
  padding: 0.3rem 0;
}
.checkbox-item.disabled {
  opacity: 0.5;
  cursor: not-allowed;
}
.checkbox-item input {
  position: absolute;
  opacity: 0;
  width: 0;
  height: 0;
}
.checkbox-box {
  width: 20px;
  height: 20px;
  border: 2px solid #ccc;
  border-radius: 4px;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-shrink: 0;
  transition: all 0.2s;
}
.checkbox-item.checked .checkbox-box {
  background: #42b883;
  border-color: #42b883;
}
.checkmark {
  color: white;
  font-size: 0.75rem;
  font-weight: bold;
}
.checkbox-label {
  font-size: 0.95rem;
  color: #333;
}
</style>
