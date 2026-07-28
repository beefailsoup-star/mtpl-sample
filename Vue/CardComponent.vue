<template>
  <div class="card-component" :class="{ 'card-hover': hoverable }">
    <div v-if="$slots.image || imageSrc" class="card-image">
      <slot name="image">
        <img :src="imageSrc" :alt="imageAlt" />
      </slot>
    </div>
    <div v-if="$slots.header || title" class="card-header">
      <slot name="header">
        <h3>{{ title }}</h3>
        <p v-if="subtitle" class="subtitle">{{ subtitle }}</p>
      </slot>
    </div>
    <div class="card-body">
      <slot />
    </div>
    <div v-if="$slots.footer" class="card-footer">
      <slot name="footer" />
    </div>
  </div>
</template>

<script setup>
defineProps({
  title: { type: String, default: '' },
  subtitle: { type: String, default: '' },
  imageSrc: { type: String, default: '' },
  imageAlt: { type: String, default: '' },
  hoverable: { type: Boolean, default: false }
})
</script>

<style scoped>
.card-component {
  background: white;
  border-radius: 10px;
  box-shadow: 0 2px 8px rgba(0,0,0,0.08);
  overflow: hidden;
  font-family: Arial, sans-serif;
  border: 1px solid #f0f0f0;
}
.card-hover {
  transition: box-shadow 0.2s, transform 0.2s;
  cursor: pointer;
}
.card-hover:hover {
  box-shadow: 0 6px 20px rgba(0,0,0,0.12);
  transform: translateY(-2px);
}
.card-image img {
  width: 100%;
  height: 180px;
  object-fit: cover;
  display: block;
}
.card-header {
  padding: 1rem 1.25rem 0;
}
.card-header h3 {
  margin: 0;
  color: #2c3e50;
  font-size: 1.15rem;
}
.subtitle {
  margin: 0.25rem 0 0;
  color: #999;
  font-size: 0.85rem;
}
.card-body {
  padding: 1rem 1.25rem;
  font-size: 0.95rem;
  color: #555;
}
.card-footer {
  padding: 0.85rem 1.25rem;
  border-top: 1px solid #f0f0f0;
  display: flex;
  align-items: center;
  gap: 0.5rem;
}
</style>
