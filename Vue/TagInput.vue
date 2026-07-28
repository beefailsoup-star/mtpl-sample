<template>
  <div class="tag-input" :class="{ focused: isFocused }">
    <div class="tags">
      <span v-for="(tag, i) in tags" :key="i" class="tag">
        {{ tag }}
        <button class="tag-remove" @click="removeTag(i)">&times;</button>
      </span>
      <input
        ref="inputRef"
        v-model="input"
        :placeholder="tags.length ? '' : placeholder"
        @keydown.prevent="onKeydown"
        @focus="isFocused = true"
        @blur="onBlur"
        class="tag-input-field"
      />
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const props = defineProps({
  modelValue: { type: Array, default: () => [] },
  placeholder: { type: String, default: 'Type and press Enter...' },
  maxTags: { type: Number, default: 0 }
})

const emit = defineEmits(['update:modelValue'])

const tags = ref([...props.modelValue])
const input = ref('')
const isFocused = ref(false)
const inputRef = ref(null)

const addTag = (tag) => {
  const t = tag.trim()
  if (!t) return
  if (tags.value.includes(t)) return
  if (props.maxTags && tags.value.length >= props.maxTags) return
  tags.value.push(t)
  emit('update:modelValue', [...tags.value])
}

const removeTag = (i) => {
  tags.value.splice(i, 1)
  emit('update:modelValue', [...tags.value])
}

const onKeydown = (e) => {
  if (e.key === 'Enter') {
    addTag(input.value)
    input.value = ''
  } else if (e.key === 'Backspace' && !input.value && tags.value.length) {
    removeTag(tags.value.length - 1)
  } else if (e.key === ',' || e.key === ';') {
    addTag(input.value.slice(0, -1))
    input.value = ''
  }
}

const onBlur = () => {
  isFocused.value = false
  if (input.value) {
    addTag(input.value)
    input.value = ''
  }
}
</script>

<style scoped>
.tag-input {
  border: 1px solid #ccc;
  border-radius: 6px;
  padding: 0.4rem 0.5rem;
  font-family: Arial, sans-serif;
  transition: border-color 0.2s;
}
.tag-input.focused {
  border-color: #42b883;
  box-shadow: 0 0 0 2px rgba(66,184,131,0.12);
}
.tags {
  display: flex;
  flex-wrap: wrap;
  gap: 0.3rem;
  align-items: center;
}
.tag {
  display: inline-flex;
  align-items: center;
  gap: 0.25rem;
  background: #e8f5e9;
  color: #2e7d32;
  padding: 0.2rem 0.5rem;
  border-radius: 4px;
  font-size: 0.85rem;
}
.tag-remove {
  background: none;
  border: none;
  cursor: pointer;
  font-size: 1rem;
  color: #2e7d32;
  line-height: 1;
  padding: 0;
}
.tag-remove:hover {
  color: #c62828;
}
.tag-input-field {
  border: none;
  outline: none;
  flex: 1;
  min-width: 80px;
  font-size: 0.95rem;
  padding: 0.2rem 0.25rem;
  background: transparent;
}
</style>
