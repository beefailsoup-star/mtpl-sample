<template>
  <div class="data-table">
    <table>
      <thead>
        <tr>
          <th
            v-for="col in columns"
            :key="col.key"
            @click="sortBy(col.key)"
            :class="{ sortable: col.sortable, sorted: sortKey === col.key }"
          >
            {{ col.label }}
            <span v-if="col.sortable" class="sort-indicator">
              {{ sortKey === col.key ? (sortOrder === 'asc' ? '▲' : '▼') : '⇅' }}
            </span>
          </th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="(row, i) in sortedData" :key="i">
          <td v-for="col in columns" :key="col.key">
            {{ row[col.key] }}
          </td>
        </tr>
        <tr v-if="sortedData.length === 0">
          <td :colspan="columns.length" class="empty">No data available</td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script setup>
import { ref, computed } from 'vue'

const props = defineProps({
  columns: { type: Array, required: true },
  data: { type: Array, required: true }
})

const sortKey = ref('')
const sortOrder = ref('asc')

const sortedData = computed(() => {
  if (!sortKey.value) return props.data
  return [...props.data].sort((a, b) => {
    const valA = a[sortKey.value]
    const valB = b[sortKey.value]
    const mul = sortOrder.value === 'asc' ? 1 : -1
    if (valA < valB) return -1 * mul
    if (valA > valB) return 1 * mul
    return 0
  })
})

const sortBy = (key) => {
  const col = props.columns.find(c => c.key === key)
  if (!col?.sortable) return
  if (sortKey.value === key) {
    sortOrder.value = sortOrder.value === 'asc' ? 'desc' : 'asc'
  } else {
    sortKey.value = key
    sortOrder.value = 'asc'
  }
}
</script>

<style scoped>
.data-table {
  overflow-x: auto;
  font-family: Arial, sans-serif;
}
table {
  width: 100%;
  border-collapse: collapse;
}
th, td {
  padding: 0.65rem 0.85rem;
  text-align: left;
  border-bottom: 1px solid #e0e0e0;
  font-size: 0.9rem;
}
th {
  background: #f8f9fa;
  font-weight: 600;
  color: #495057;
  user-select: none;
}
th.sortable {
  cursor: pointer;
}
th.sortable:hover {
  background: #e9ecef;
}
th.sorted {
  color: #42b883;
}
.sort-indicator {
  margin-left: 0.3rem;
  font-size: 0.75rem;
  opacity: 0.6;
}
tr:hover td {
  background: #f8fbfa;
}
.empty {
  text-align: center;
  color: #999;
  padding: 2rem;
}
</style>
