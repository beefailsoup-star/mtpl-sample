<template>
  <div
    class="file-uploader"
    :class="{ dragover: isDragover }"
    @dragover.prevent="isDragover = true"
    @dragleave.prevent="isDragover = false"
    @drop.prevent="onDrop"
  >
    <div class="upload-area">
      <span class="icon">&#128206;</span>
      <p v-if="!files.length">Drag & drop files here or click to browse</p>
      <p v-else>{{ files.length }} file(s) selected</p>
      <input ref="inputRef" type="file" multiple @change="onFileSelect" />
      <button class="browse-btn" @click="$refs.inputRef.click()">Browse Files</button>
    </div>
    <ul v-if="files.length" class="file-list">
      <li v-for="(file, i) in files" :key="i">
        <span>{{ file.name }}</span>
        <span class="size">{{ (file.size / 1024).toFixed(1) }} KB</span>
        <button class="remove" @click="removeFile(i)">&times;</button>
      </li>
    </ul>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const files = ref([])
const isDragover = ref(false)
const inputRef = ref(null)

const emit = defineEmits(['files-change'])

const addFiles = (incoming) => {
  for (const file of incoming) {
    if (!files.value.some(f => f.name === file.name && f.size === file.size)) {
      files.value.push(file)
    }
  }
  emit('files-change', files.value)
}

const onDrop = (e) => {
  isDragover.value = false
  if (e.dataTransfer?.files) addFiles(e.dataTransfer.files)
}

const onFileSelect = (e) => {
  if (e.target?.files) addFiles(e.target.files)
  if (inputRef.value) inputRef.value.value = ''
}

const removeFile = (index) => {
  files.value.splice(index, 1)
  emit('files-change', files.value)
}
</script>

<style scoped>
.file-uploader {
  border: 2px dashed #ccc;
  border-radius: 10px;
  padding: 2rem;
  text-align: center;
  font-family: Arial, sans-serif;
  transition: all 0.2s;
}
.file-uploader.dragover {
  border-color: #42b883;
  background: #f0faf5;
}
.upload-area {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 0.5rem;
}
.upload-area .icon {
  font-size: 2.5rem;
}
.upload-area p {
  color: #666;
  margin: 0;
}
.upload-area input[type="file"] {
  display: none;
}
.browse-btn {
  padding: 0.5rem 1.25rem;
  background: #42b883;
  color: white;
  border: none;
  border-radius: 6px;
  cursor: pointer;
  font-size: 0.9rem;
}
.browse-btn:hover {
  opacity: 0.85;
}
.file-list {
  list-style: none;
  padding: 0;
  margin: 1rem 0 0;
  text-align: left;
}
.file-list li {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  padding: 0.4rem 0.6rem;
  border-bottom: 1px solid #eee;
  font-size: 0.9rem;
}
.file-list li span:first-child {
  flex: 1;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
}
.size {
  color: #999;
  font-size: 0.8rem;
}
.remove {
  background: none;
  border: none;
  color: #e74c3c;
  cursor: pointer;
  font-size: 1.1rem;
}
</style>
