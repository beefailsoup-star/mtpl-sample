<template>
  <div class="date-range-picker">
    <div class="field-group">
      <label>{{ startLabel }}</label>
      <input type="date" :value="startDate" @input="updateStart" :max="endDate" />
    </div>
    <span class="separator">to</span>
    <div class="field-group">
      <label>{{ endLabel }}</label>
      <input type="date" :value="endDate" @input="updateEnd" :min="startDate" />
    </div>
  </div>
</template>

<script setup>
const props = defineProps({
  startDate: { type: String, default: '' },
  endDate: { type: String, default: '' },
  startLabel: { type: String, default: 'Start Date' },
  endLabel: { type: String, default: 'End Date' }
})

const emit = defineEmits(['update:startDate', 'update:endDate'])

const updateStart = (e) => emit('update:startDate', e.target.value)
const updateEnd = (e) => emit('update:endDate', e.target.value)
</script>

<style scoped>
.date-range-picker {
  display: flex;
  align-items: flex-end;
  gap: 0.75rem;
  font-family: Arial, sans-serif;
  flex-wrap: wrap;
}
.field-group {
  display: flex;
  flex-direction: column;
}
.field-group label {
  font-size: 0.85rem;
  font-weight: 600;
  color: #555;
  margin-bottom: 0.25rem;
}
.field-group input {
  padding: 0.5rem;
  border: 1px solid #ccc;
  border-radius: 4px;
  font-size: 0.95rem;
}
.separator {
  padding-bottom: 0.5rem;
  font-size: 0.9rem;
  color: #999;
}
</style>
