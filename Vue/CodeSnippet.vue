<template>
  <div class="code-snippet">
    <div class="code-header">
      <span class="lang">{{ language }}</span>
      <button class="copy-btn" @click="copyCode">
        {{ copied ? 'Copied!' : 'Copy' }}
      </button>
    </div>
    <pre><code :class="'language-' + language">{{ code }}</code></pre>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const props = defineProps({
  code: { type: String, required: true },
  language: { type: String, default: 'javascript' }
})

const copied = ref(false)

const copyCode = async () => {
  try {
    await navigator.clipboard.writeText(props.code)
    copied.value = true
    setTimeout(() => { copied.value = false }, 2000)
  } catch {
    const ta = document.createElement('textarea')
    ta.value = props.code
    document.body.appendChild(ta)
    ta.select()
    document.execCommand('copy')
    document.body.removeChild(ta)
    copied.value = true
    setTimeout(() => { copied.value = false }, 2000)
  }
}
</script>

<style scoped>
.code-snippet {
  border-radius: 8px;
  overflow: hidden;
  background: #1e1e1e;
  font-family: 'Consolas', 'Courier New', monospace;
  font-size: 0.85rem;
  margin: 0.5rem 0;
}
.code-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0.45rem 0.75rem;
  background: #2d2d2d;
  color: #ccc;
}
.lang {
  font-size: 0.75rem;
  text-transform: uppercase;
  color: #999;
}
.copy-btn {
  padding: 0.2rem 0.6rem;
  font-size: 0.75rem;
  background: #3c3c3c;
  color: #ccc;
  border: 1px solid #555;
  border-radius: 4px;
  cursor: pointer;
  font-family: inherit;
}
.copy-btn:hover {
  background: #555;
}
pre {
  margin: 0;
  padding: 1rem;
  overflow-x: auto;
  color: #d4d4d4;
}
code {
  font-family: inherit;
}
</style>
