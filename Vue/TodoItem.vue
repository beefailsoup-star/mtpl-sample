<template>
  <li class="todo-item" :class="{ completed: todo.done }">
    <input type="checkbox" v-model="todo.done" />
    <span class="text" :class="{ 'line-through': todo.done }">{{ todo.text }}</span>
    <button class="delete-btn" @click="$emit('delete', todo.id)">&times;</button>
  </li>
</template>

<script setup>
defineProps({
  todo: {
    type: Object,
    required: true
  }
})

defineEmits(['delete'])
</script>

<style scoped>
.todo-item {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  padding: 0.5rem 0.75rem;
  border-bottom: 1px solid #eee;
  list-style: none;
}
.todo-item:hover {
  background: #f9f9f9;
}
.text {
  flex: 1;
  font-size: 1rem;
}
.line-through {
  text-decoration: line-through;
  color: #999;
}
.delete-btn {
  background: none;
  border: none;
  color: #e74c3c;
  font-size: 1.3rem;
  cursor: pointer;
  padding: 0 0.25rem;
}
.delete-btn:hover {
  color: #c0392b;
}
</style>
