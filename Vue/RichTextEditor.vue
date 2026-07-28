<template>
  <div class="rich-text-editor">
    <div class="toolbar">
      <button @click="exec('bold')" title="Bold"><strong>B</strong></button>
      <button @click="exec('italic')" title="Italic"><em>I</em></button>
      <button @click="exec('underline')" title="Underline"><u>U</u></button>
      <span class="divider"></span>
      <button @click="exec('insertUnorderedList')" title="Bullet List">&#8226;</button>
      <button @click="exec('insertOrderedList')" title="Numbered List">1.</button>
      <span class="divider"></span>
      <button @click="exec('formatBlock', 'h2')" title="Heading">H2</button>
      <button @click="exec('formatBlock', 'p')" title="Paragraph">P</button>
      <span class="divider"></span>
      <button @click="exec('undo')" title="Undo">&#8630;</button>
      <button @click="exec('redo')" title="Redo">&#8631;</button>
    </div>
    <div
      ref="editorRef"
      class="editor-content"
      contenteditable="true"
      @input="onInput"
      @paste="onPaste"
      v-html="modelValue"
    ></div>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const props = defineProps({
  modelValue: { type: String, default: '' }
})

const emit = defineEmits(['update:modelValue'])
const editorRef = ref(null)

const exec = (command, value = null) => {
  document.execCommand(command, false, value)
  editorRef.value?.focus()
  emitContent()
}

const onInput = () => emitContent()

const onPaste = (e) => {
  e.preventDefault()
  const text = e.clipboardData.getData('text/plain')
  document.execCommand('insertText', false, text)
}

const emitContent = () => {
  emit('update:modelValue', editorRef.value?.innerHTML || '')
}
</script>

<style scoped>
.rich-text-editor {
  border: 1px solid #ccc;
  border-radius: 8px;
  overflow: hidden;
  font-family: Arial, sans-serif;
}
.toolbar {
  display: flex;
  flex-wrap: wrap;
  gap: 0.15rem;
  padding: 0.4rem 0.5rem;
  background: #f9f9f9;
  border-bottom: 1px solid #eee;
}
.toolbar button {
  padding: 0.25rem 0.55rem;
  border: 1px solid transparent;
  background: none;
  cursor: pointer;
  border-radius: 3px;
  font-size: 0.85rem;
}
.toolbar button:hover {
  background: #e9ecef;
  border-color: #ccc;
}
.divider {
  width: 1px;
  background: #ddd;
  margin: 0 0.2rem;
}
.editor-content {
  min-height: 150px;
  padding: 0.75rem;
  outline: none;
  line-height: 1.5;
}
.editor-content:focus {
  box-shadow: inset 0 0 0 1px #42b883;
}
</style>
