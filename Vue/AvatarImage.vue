<template>
  <div class="avatar-image" :style="{ width: size + 'px', height: size + 'px' }">
    <img
      v-if="!imgError"
      :src="src"
      :alt="alt"
      @error="imgError = true"
      :style="{ width: size + 'px', height: size + 'px' }"
    />
    <div v-else class="avatar-fallback" :style="{ fontSize: (size * 0.4) + 'px' }">
      {{ initials }}
    </div>
  </div>
</template>

<script setup>
import { ref, computed } from 'vue'

const props = defineProps({
  src: { type: String, default: '' },
  alt: { type: String, default: 'Avatar' },
  name: { type: String, default: '?' },
  size: { type: Number, default: 48 }
})

const imgError = ref(false)

const initials = computed(() => {
  return props.name
    .split(' ')
    .map(w => w[0])
    .join('')
    .toUpperCase()
    .slice(0, 2) || '?'
})
</script>

<style scoped>
.avatar-image {
  display: inline-flex;
  border-radius: 50%;
  overflow: hidden;
  flex-shrink: 0;
}
.avatar-image img {
  object-fit: cover;
  display: block;
}
.avatar-fallback {
  width: 100%;
  height: 100%;
  display: flex;
  align-items: center;
  justify-content: center;
  background: #42b883;
  color: white;
  font-weight: bold;
  font-family: Arial, sans-serif;
  user-select: none;
}
</style>
