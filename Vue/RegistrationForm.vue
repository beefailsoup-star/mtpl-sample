<template>
  <form class="registration-form" @submit.prevent="handleSubmit">
    <h2>Create Account</h2>
    <div class="field">
      <label for="fullname">Full Name</label>
      <input id="fullname" v-model="fullname" placeholder="John Smith" />
      <span v-if="errors.fullname" class="error">{{ errors.fullname }}</span>
    </div>
    <div class="field">
      <label for="reg-email">Email</label>
      <input id="reg-email" v-model="email" type="email" placeholder="you@example.com" />
      <span v-if="errors.email" class="error">{{ errors.email }}</span>
    </div>
    <div class="field">
      <label for="reg-password">Password</label>
      <input id="reg-password" v-model="password" type="password" placeholder="••••••••" />
      <span v-if="errors.password" class="error">{{ errors.password }}</span>
    </div>
    <div class="field">
      <label for="confirm-password">Confirm Password</label>
      <input id="confirm-password" v-model="confirmPassword" type="password" placeholder="••••••••" />
      <span v-if="errors.confirm" class="error">{{ errors.confirm }}</span>
    </div>
    <button type="submit" :disabled="loading">
      {{ loading ? 'Creating account...' : 'Register' }}
    </button>
  </form>
</template>

<script setup>
import { reactive, ref } from 'vue'

const fullname = ref('')
const email = ref('')
const password = ref('')
const confirmPassword = ref('')
const loading = ref(false)
const errors = reactive({ fullname: '', email: '', password: '', confirm: '' })

const emit = defineEmits(['register'])

const validate = () => {
  errors.fullname = ''
  errors.email = ''
  errors.password = ''
  errors.confirm = ''
  let valid = true
  if (!fullname.value.trim()) {
    errors.fullname = 'Name is required'
    valid = false
  }
  if (!email.value) {
    errors.email = 'Email is required'
    valid = false
  } else if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email.value)) {
    errors.email = 'Invalid email'
    valid = false
  }
  if (!password.value) {
    errors.password = 'Password is required'
    valid = false
  } else if (password.value.length < 8) {
    errors.password = 'Minimum 8 characters'
    valid = false
  }
  if (password.value !== confirmPassword.value) {
    errors.confirm = 'Passwords do not match'
    valid = false
  }
  return valid
}

const handleSubmit = async () => {
  if (!validate()) return
  loading.value = true
  await new Promise(r => setTimeout(r, 1500))
  loading.value = false
  emit('register', { fullname: fullname.value, email: email.value })
}
</script>

<style scoped>
.registration-form {
  max-width: 400px;
  margin: 0 auto;
  padding: 2rem;
  border-radius: 8px;
  box-shadow: 0 2px 10px rgba(0,0,0,0.08);
  font-family: Arial, sans-serif;
}
.registration-form h2 {
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
  display: block;
  margin-top: 0.15rem;
}
button {
  width: 100%;
  padding: 0.65rem;
  background: #42b883;
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
