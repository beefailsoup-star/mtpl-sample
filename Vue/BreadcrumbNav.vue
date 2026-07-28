<template>
  <nav aria-label="Breadcrumb" class="breadcrumb-nav">
    <ol>
      <li v-for="(crumb, index) in items" :key="index">
        <router-link v-if="crumb.to && index < items.length - 1" :to="crumb.to">
          {{ crumb.label }}
        </router-link>
        <span v-else-if="index < items.length - 1" class="crumb-link" @click="crumb.onClick">
          {{ crumb.label }}
        </span>
        <span v-else class="current">{{ crumb.label }}</span>
        <span v-if="index < items.length - 1" class="separator">/</span>
      </li>
    </ol>
  </nav>
</template>

<script setup>
defineProps({
  items: {
    type: Array,
    required: true
  }
})
</script>

<style scoped>
.breadcrumb-nav ol {
  display: flex;
  align-items: center;
  list-style: none;
  padding: 0;
  margin: 0;
  gap: 0.25rem;
  font-family: Arial, sans-serif;
  font-size: 0.9rem;
}
.breadcrumb-nav li {
  display: flex;
  align-items: center;
  gap: 0.25rem;
}
.crumb-link {
  color: #42b883;
  cursor: pointer;
  text-decoration: none;
}
.crumb-link:hover {
  text-decoration: underline;
}
.current {
  color: #999;
  font-weight: 500;
}
.separator {
  color: #ccc;
  margin: 0 0.15rem;
}
</style>
