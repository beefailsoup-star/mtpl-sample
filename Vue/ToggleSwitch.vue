<template>
  <label class="toggle-switch" :class="{ disabled: disabled }">
    <input
      type="checkbox"
      :checked="modelValue"
      @change="toggle"
      :disabled="disabled"
    />
    <span class="slider" :class="size"></span>
    <span v-if="label" class="label-text">{{ label }}</span>
  </label>
</template>

<script setup>
const props = defineProps({
  modelValue: { type: Boolean, default: false },
  label: { type: String, default: '' },
  disabled: { type: Boolean, default: false },
  size: { type: String, default: 'md', validator: v => ['sm', 'md', 'lg'].includes(v) }
})

const emit = defineEmits(['update:modelValue'])

const toggle = (e) => emit('update:modelValue', e.target.checked)
</script>

<style scoped>
.toggle-switch {
  display: inline-flex;
  align-items: center;
  gap: 0.5rem;
  cursor: pointer;
  user-select: none;
}
.toggle-switch.disabled {
  opacity: 0.5;
  cursor: not-allowed;
}
.toggle-switch input {
  position: absolute;
  opacity: 0;
  width: 0;
  height: 0;
}
.slider {
  position: relative;
  background: #ccc;
  border-radius: 999px;
  transition: background 0.2s;
  flex-shrink: 0;
}
.slider::after {
  content: '';
  position: absolute;
  top: 2px;
  left: 2px;
  background: white;
  border-radius: 50%;
  transition: transform 0.2s;
}
.toggle-switch input:checked + .slider {
  background: #42b883;
}
.toggle-switch input:checked + .slider::after {
  transform: translateX(100%);
}
.sm .slider { width: 32px; height: 18px; }
.sm .slider::after { width: 14px; height: 14px; }
.md .slider { width: 42px; height: 24px; }
.md .slider::after { width: 20px; height: 20px; }
.lg .slider { width: 52px; height: 30px; }
.lg .slider::after { width: 26px; height: 26px; }
.label-text {
  font-size: 0.95rem;
  color: #333;
}
</style>
