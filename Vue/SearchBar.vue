<template>
  <div class="search-bar">
    <span class="icon">&#128269;</span>
    <input
      v-model="query"
      type="text"
      :placeholder="placeholder"
      @input="onInput"
    />
    <button v-if="query" class="clear" @click="clear">&times;</button>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const props = defineProps({
  placeholder: {
    type: String,
    default: 'Search...'
  },
  debounce: {
    type: Number,
    default: 300
  }
})

const emit = defineEmits(['search'])

const query = ref('')
let timer = null

const onInput = () => {
  clearTimeout(timer)
  timer = setTimeout(() => {
    emit('search', query.value)
  }, props.debounce)
}

const clear = () => {
  query.value = ''
  emit('search', '')
}
</script>

<style scoped>
.search-bar {
  display: flex;
  align-items: center;
  border: 1px solid #ccc;
  border-radius: 24px;
  padding: 0.4rem 1rem;
  background: white;
  max-width: 320px;
}
.search-bar:focus-within {
  border-color: #42b883;
  box-shadow: 0 0 0 2px rgba(66,184,131,0.15);
}
.icon {
  margin-right: 0.5rem;
  font-size: 1rem;
}
input {
  flex: 1;
  border: none;
  outline: none;
  font-size: 0.95rem;
  background: transparent;
}
.clear {
  background: none;
  border: none;
  font-size: 1.2rem;
  cursor: pointer;
  color: #999;
  line-height: 1;
}
.clear:hover {
  color: #e74c3c;
}
</style>
