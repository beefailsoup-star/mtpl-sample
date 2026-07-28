<template>
  <form class="login-form" @submit.prevent="handleSubmit">
    <h2>Login</h2>
    <div class="field">
      <label for="email">Email</label>
      <input id="email" v-model="email" type="email" placeholder="you@example.com" />
      <span v-if="errors.email" class="error">{{ errors.email }}</span>
    </div>
    <div class="field">
      <label for="password">Password</label>
      <input id="password" v-model="password" type="password" placeholder="••••••••" />
      <span v-if="errors.password" class="error">{{ errors.password }}</span>
    </div>
    <button type="submit" :disabled="loading">
      {{ loading ? 'Logging in...' : 'Login' }}
    </button>
  </form>
</template>

<script setup>
import { reactive, ref } from 'vue'

const email = ref('')
const password = ref('')
const loading = ref(false)
const errors = reactive({ email: '', password: '' })

const emit = defineEmits(['login'])

const validate = () => {
  errors.email = ''
  errors.password = ''
  let valid = true
  if (!email.value) {
    errors.email = 'Email is required'
    valid = false
  } else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email.value)) {
    errors.email = 'Invalid email format'
    valid = false
  }
  if (!password.value) {
    errors.password = 'Password is required'
    valid = false
  } else if (password.value.length < 6) {
    errors.password = 'Password must be at least 6 characters'
    valid = false
  }
  return valid
}

const handleSubmit = async () => {
  if (!validate()) return
  loading.value = true
  await new Promise(r => setTimeout(r, 1000))
  loading.value = false
  emit('login', { email: email.value, password: password.value })
}
</script>

<style scoped>
.login-form {
  max-width: 380px;
  margin: 0 auto;
  padding: 2rem;
  border-radius: 8px;
  box-shadow: 0 2px 10px rgba(0,0,0,0.08);
  font-family: Arial, sans-serif;
}
.login-form h2 {
  margin-bottom: 1.25rem;
  color: #2c3e50;
}
.field {
  margin-bottom: 1rem;
}
.field label {
  display: block;
  margin-bottom: 0.25rem;
  font-weight: 600;
  color: #34495e;
}
.field input {
  width: 100%;
  padding: 0.55rem;
  border: 1px solid #ccc;
  border-radius: 4px;
  font-size: 1rem;
  box-sizing: border-box;
}
.error {
  color: #e74c3c;
  font-size: 0.8rem;
  margin-top: 0.15rem;
  display: block;
}
button {
  width: 100%;
  padding: 0.6rem;
  background: #3498db;
  color: white;
  border: none;
  border-radius: 6px;
  font-size: 1rem;
  cursor: pointer;
}
button:disabled {
  opacity: 0.6;
  cursor: not-allowed;
}
</style>
