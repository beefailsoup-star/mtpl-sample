<template>
  <div class="autocomplete-input" ref="wrapperRef">
    <input
      v-model="query"
      type="text"
      :placeholder="placeholder"
      @input="onInput"
      @focus="open = true"
      @keydown.down.prevent="highlightNext"
      @keydown.up.prevent="highlightPrev"
      @keydown.enter.prevent="selectHighlighted"
      @keydown.esc="open = false"
    />
    <Transition name="dropdown">
      <ul v-if="open && filtered.length" class="suggestions">
        <li
          v-for="(item, i) in filtered"
          :key="i"
          :class="{ highlighted: i === highlightIndex }"
          @click="select(item)"
          @mouseenter="highlightIndex = i"
        >
          <slot name="item" :item="item">
            {{ item }}
          </slot>
        </li>
      </ul>
    </Transition>
  </div>
</template>

<script setup>
import { ref, computed, onMounted, onUnmounted } from 'vue'

const props = defineProps({
  items: { type: Array, required: true },
  placeholder: { type: String, default: 'Type to search...' }
})

const emit = defineEmits(['select'])

const query = ref('')
const open = ref(false)
const highlightIndex = ref(-1)
const wrapperRef = ref(null)

const filtered = computed(() => {
  if (!query.value) return props.items
  const q = query.value.toLowerCase()
  return props.items.filter(item => item.toLowerCase().includes(q))
})

const onInput = () => {
  open.value = true
  highlightIndex.value = -1
}

const highlightNext = () => {
  if (highlightIndex.value < filtered.value.length - 1) highlightIndex.value++
}

const highlightPrev = () => {
  if (highlightIndex.value > 0) highlightIndex.value--
}

const selectHighlighted = () => {
  if (highlightIndex.value >= 0 && filtered.value[highlightIndex.value]) {
    select(filtered.value[highlightIndex.value])
  }
}

const select = (item) => {
  query.value = item
  open.value = false
  emit('select', item)
}

const onClickOutside = (e) => {
  if (wrapperRef.value && !wrapperRef.value.contains(e.target)) {
    open.value = false
  }
}

onMounted(() => document.addEventListener('click', onClickOutside))
onUnmounted(() => document.removeEventListener('click', onClickOutside))
</script>

<style scoped>
.autocomplete-input {
  position: relative;
  font-family: Arial, sans-serif;
}
.autocomplete-input input {
  width: 100%;
  padding: 0.55rem 0.75rem;
  border: 1px solid #ccc;
  border-radius: 6px;
  font-size: 0.95rem;
  box-sizing: border-box;
  transition: border-color 0.2s;
}
.autocomplete-input input:focus {
  outline: none;
  border-color: #42b883;
  box-shadow: 0 0 0 2px rgba(66,184,131,0.12);
}
.suggestions {
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
  z-index: 200;
  max-height: 200px;
  overflow-y: auto;
}
.suggestions li {
  padding: 0.5rem 0.75rem;
  cursor: pointer;
  font-size: 0.9rem;
}
.suggestions li:hover, .suggestions li.highlighted {
  background: #f0faf5;
  color: #42b883;
}
.dropdown-enter-active, .dropdown-leave-active {
  transition: opacity 0.15s ease;
}
.dropdown-enter-from, .dropdown-leave-to {
  opacity: 0;
}
</style>
