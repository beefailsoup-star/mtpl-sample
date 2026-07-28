<template>
  <nav class="pagination" v-if="totalPages > 1">
    <button :disabled="currentPage === 1" @click="goTo(1)">&laquo;</button>
    <button :disabled="currentPage === 1" @click="goTo(currentPage - 1)">&lsaquo;</button>
    <button
      v-for="page in visiblePages"
      :key="page"
      :class="{ active: page === currentPage }"
      @click="goTo(page)"
    >
      {{ page }}
    </button>
    <button :disabled="currentPage === totalPages" @click="goTo(currentPage + 1)">&rsaquo;</button>
    <button :disabled="currentPage === totalPages" @click="goTo(totalPages)">&raquo;</button>
  </nav>
</template>

<script setup>
import { computed } from 'vue'

const props = defineProps({
  currentPage: { type: Number, default: 1 },
  totalPages: { type: Number, default: 1 }
})

const emit = defineEmits(['page-change'])

const visiblePages = computed(() => {
  const pages = []
  const maxVisible = 5
  let start = Math.max(1, props.currentPage - Math.floor(maxVisible / 2))
  let end = Math.min(props.totalPages, start + maxVisible - 1)
  if (end - start + 1 < maxVisible) {
    start = Math.max(1, end - maxVisible + 1)
  }
  for (let i = start; i <= end; i++) {
    pages.push(i)
  }
  return pages
})

const goTo = (page) => {
  if (page < 1 || page > props.totalPages || page === props.currentPage) return
  emit('page-change', page)
}
</script>

<style scoped>
.pagination {
  display: flex;
  align-items: center;
  gap: 0.25rem;
  font-family: Arial, sans-serif;
}
.pagination button {
  padding: 0.4rem 0.75rem;
  border: 1px solid #ddd;
  background: white;
  border-radius: 4px;
  cursor: pointer;
  font-size: 0.9rem;
  color: #333;
}
.pagination button:hover:not(:disabled):not(.active) {
  background: #f0f0f0;
}
.pagination button.active {
  background: #42b883;
  color: white;
  border-color: #42b883;
}
.pagination button:disabled {
  opacity: 0.4;
  cursor: not-allowed;
}
</style>
