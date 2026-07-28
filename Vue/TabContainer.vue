<template>
  <div class="tab-container">
    <div class="tab-nav" role="tablist">
      <button
        v-for="(tab, index) in tabs"
        :key="tab"
        :class="['tab-btn', { active: activeTab === index }]"
        @click="activeTab = index"
        role="tab"
        :aria-selected="activeTab === index"
      >
        {{ tab }}
      </button>
    </div>
    <div class="tab-panels">
      <slot :activeTab="activeTab" />
    </div>
  </div>
</template>

<script setup>
import { ref, provide } from 'vue'

const tabs = ref([])
const activeTab = ref(0)

const registerTab = (title) => {
  if (!tabs.value.includes(title)) {
    tabs.value.push(title)
  }
}

provide('registerTab', registerTab)
provide('activeTab', activeTab)
</script>

<style scoped>
.tab-container {
  font-family: Arial, sans-serif;
  border: 1px solid #e0e0e0;
  border-radius: 8px;
  overflow: hidden;
}
.tab-nav {
  display: flex;
  background: #f5f5f5;
  border-bottom: 1px solid #e0e0e0;
}
.tab-btn {
  padding: 0.75rem 1.5rem;
  border: none;
  background: transparent;
  cursor: pointer;
  font-size: 0.95rem;
  color: #666;
  border-bottom: 2px solid transparent;
  transition: all 0.2s;
}
.tab-btn:hover {
  color: #42b883;
  background: #f0faf5;
}
.tab-btn.active {
  color: #42b883;
  border-bottom-color: #42b883;
  font-weight: 600;
}
.tab-panels {
  padding: 1.25rem;
}
</style>
