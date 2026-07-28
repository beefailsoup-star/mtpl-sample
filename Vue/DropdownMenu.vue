<template>
  <div class="dropdown-menu" ref="dropdownRef">
    <button class="trigger" @click="open = !open">
      {{ selected ? selected.label : placeholder }}
      <span class="arrow" :class="{ up: open }">&#9660;</span>
    </button>
    <Transition name="fade">
      <ul v-if="open" class="menu">
        <li
          v-for="option in options"
          :key="option.value"
          :class="{ active: selected?.value === option.value }"
          @click="select(option)"
        >
          {{ option.label }}
        </li>
      </ul>
    </Transition>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted } from 'vue'

const props = defineProps({
  options: { type: Array, required: true },
  placeholder: { type: String, default: 'Select an option' },
  modelValue: { type: Object, default: null }
})

const emit = defineEmits(['update:modelValue'])

const open = ref(false)
const selected = ref(props.modelValue)
const dropdownRef = ref(null)

const select = (option) => {
  selected.value = option
  emit('update:modelValue', option)
  open.value = false
}

const onClickOutside = (e) => {
  if (dropdownRef.value && !dropdownRef.value.contains(e.target)) {
    open.value = false
  }
}

onMounted(() => document.addEventListener('click', onClickOutside))
onUnmounted(() => document.removeEventListener('click', onClickOutside))
</script>

<style scoped>
.dropdown-menu {
  position: relative;
  font-family: Arial, sans-serif;
}
.trigger {
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 0.5rem;
  padding: 0.5rem 1rem;
  border: 1px solid #ccc;
  border-radius: 6px;
  background: white;
  cursor: pointer;
  min-width: 180px;
  font-size: 0.95rem;
}
.arrow {
  font-size: 0.7rem;
  transition: transform 0.2s;
}
.arrow.up {
  transform: rotate(180deg);
}
.menu {
  position: absolute;
  top: 100%;
  left: 0;
  right: 0;
  margin-top: 4px;
  background: white;
  border: 1px solid #ddd;
  border-radius: 6px;
  box-shadow: 0 4px 12px rgba(0,0,0,0.1);
  list-style: none;
  padding: 0.25rem 0;
  z-index: 100;
}
.menu li {
  padding: 0.5rem 1rem;
  cursor: pointer;
  font-size: 0.95rem;
}
.menu li:hover, .menu li.active {
  background: #f0faf5;
  color: #42b883;
}
.fade-enter-active, .fade-leave-active {
  transition: opacity 0.15s ease;
}
.fade-enter-from, .fade-leave-to {
  opacity: 0;
}
</style>
