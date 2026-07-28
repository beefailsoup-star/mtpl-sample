<template>
  <div class="skeleton-loader" :class="variant">
    <div v-if="variant === 'card'" class="skeleton-card">
      <div class="skeleton-image skeleton-anim"></div>
      <div class="skeleton-text-group">
        <div class="skeleton-line skeleton-anim w-80"></div>
        <div class="skeleton-line skeleton-anim w-60"></div>
        <div class="skeleton-line skeleton-anim w-40"></div>
      </div>
    </div>
    <div v-else-if="variant === 'list'" class="skeleton-list">
      <div v-for="i in rows" :key="i" class="skeleton-row">
        <div class="skeleton-avatar skeleton-anim"></div>
        <div class="skeleton-text-group">
          <div class="skeleton-line skeleton-anim w-70"></div>
          <div class="skeleton-line skeleton-anim w-50"></div>
        </div>
      </div>
    </div>
    <div v-else class="skeleton-text">
      <div v-for="i in lines" :key="i" class="skeleton-line skeleton-anim" :class="'w-' + [100,90,80,70,60][i % 5]"></div>
    </div>
  </div>
</template>

<script setup>
defineProps({
  variant: { type: String, default: 'text', validator: v => ['text', 'card', 'list'].includes(v) },
  lines: { type: Number, default: 3 },
  rows: { type: Number, default: 3 }
})
</script>

<style scoped>
.skeleton-anim {
  background: linear-gradient(90deg, #f0f0f0 25%, #e0e0e0 50%, #f0f0f0 75%);
  background-size: 200% 100%;
  animation: shimmer 1.5s infinite;
  border-radius: 4px;
}
@keyframes shimmer {
  0% { background-position: 200% 0; }
  100% { background-position: -200% 0; }
}
.skeleton-card { padding: 1rem; }
.skeleton-image {
  width: 100%;
  height: 150px;
  margin-bottom: 1rem;
  border-radius: 8px;
}
.skeleton-text-group { display: flex; flex-direction: column; gap: 0.5rem; }
.skeleton-line { height: 14px; }
.skeleton-list { display: flex; flex-direction: column; gap: 1rem; }
.skeleton-row { display: flex; gap: 0.75rem; align-items: center; }
.skeleton-avatar { width: 40px; height: 40px; border-radius: 50%; flex-shrink: 0; }
.skeleton-text { display: flex; flex-direction: column; gap: 0.6rem; padding: 1rem; }
.w-100 { width: 100%; }
.w-90 { width: 90%; }
.w-80 { width: 80%; }
.w-70 { width: 70%; }
.w-60 { width: 60%; }
.w-50 { width: 50%; }
.w-40 { width: 40%; }
</style>
