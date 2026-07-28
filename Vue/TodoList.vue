<template>
  <div class="todo-list">
    <h2>Todo List</h2>
    <div class="input-group">
      <input v-model="newTodo" @keyup.enter="addTodo" placeholder="Add a new todo..." />
      <button @click="addTodo" :disabled="!newTodo.trim()">Add</button>
    </div>
    <p v-if="todos.length === 0" class="empty">No todos yet. Add one above!</p>
    <TransitionGroup name="list" tag="ul">
      <TodoItem
        v-for="todo in todos"
        :key="todo.id"
        :todo="todo"
        @delete="deleteTodo"
      />
    </TransitionGroup>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import TodoItem from './TodoItem.vue'

const newTodo = ref('')
const todos = ref([])
let nextId = 1

const addTodo = () => {
  const text = newTodo.value.trim()
  if (!text) return
  todos.value.push({ id: nextId++, text, done: false })
  newTodo.value = ''
}

const deleteTodo = (id) => {
  todos.value = todos.value.filter(t => t.id !== id)
}
</script>

<style scoped>
.todo-list {
  max-width: 500px;
  margin: 0 auto;
  padding: 1.5rem;
  font-family: Arial, sans-serif;
}
.input-group {
  display: flex;
  gap: 0.5rem;
  margin-bottom: 1rem;
}
.input-group input {
  flex: 1;
  padding: 0.5rem;
  border: 1px solid #ccc;
  border-radius: 4px;
  font-size: 1rem;
}
.input-group button {
  padding: 0.5rem 1rem;
  background: #42b883;
  color: white;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}
.empty {
  color: #999;
  text-align: center;
}
.list-enter-active, .list-leave-active {
  transition: all 0.3s ease;
}
.list-enter-from, .list-leave-to {
  opacity: 0;
  transform: translateX(30px);
}
</style>
