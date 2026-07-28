<template>
  <div class="timeline-list">
    <div v-for="(item, index) in items" :key="index" class="timeline-item">
      <div class="timeline-marker">
        <div class="dot" :class="item.type || 'default'"></div>
        <div v-if="index < items.length - 1" class="line"></div>
      </div>
      <div class="timeline-content">
        <div class="timeline-header">
          <span class="date">{{ item.date }}</span>
          <BadgeLabel v-if="item.badge" :text="item.badge" variant="primary" size="sm" />
        </div>
        <h4>{{ item.title }}</h4>
        <p v-if="item.description">{{ item.description }}</p>
      </div>
    </div>
  </div>
</template>

<script setup>
import BadgeLabel from './BadgeLabel.vue'

defineProps({
  items: {
    type: Array,
    required: true
  }
})
</script>

<style scoped>
.timeline-list {
  font-family: Arial, sans-serif;
  padding-left: 1rem;
}
.timeline-item {
  display: flex;
  gap: 1rem;
}
.timeline-marker {
  display: flex;
  flex-direction: column;
  align-items: center;
  min-width: 20px;
}
.dot {
  width: 14px;
  height: 14px;
  border-radius: 50%;
  flex-shrink: 0;
  margin-top: 4px;
}
.dot.default { background: #42b883; }
.dot.success { background: #2ecc71; }
.dot.warning { background: #f39c12; }
.dot.danger { background: #e74c3c; }
.dot.info { background: #3498db; }
.line {
  width: 2px;
  flex: 1;
  background: #e0e0e0;
  min-height: 20px;
}
.timeline-content {
  flex: 1;
  padding-bottom: 1.5rem;
}
.timeline-header {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  margin-bottom: 0.25rem;
}
.date {
  font-size: 0.8rem;
  color: #999;
}
.timeline-content h4 {
  margin: 0 0 0.25rem;
  color: #2c3e50;
  font-size: 1rem;
}
.timeline-content p {
  margin: 0;
  color: #666;
  font-size: 0.9rem;
}
</style>
