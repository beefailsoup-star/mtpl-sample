<template>
  <div class="hello-world">
    <h1>{{ greeting }}</h1>
    <p>{{ description }}</p>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const greeting = ref('Hello, Vue 3!')
const description = ref('This is a single-file component using the Composition API.')
</script>

<style scoped>
.hello-world {
  text-align: center;
  padding: 2rem;
  font-family: Arial, sans-serif;
}
.hello-world h1 {
  color: #42b883;
  font-size: 2.5rem;
}
.hello-world p {
  color: #35495e;
  font-size: 1.1rem;
}
</style>
