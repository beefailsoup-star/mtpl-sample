<template>
  <span class="badge-label" :class="[variant, size]">
    <slot>{{ text }}</slot>
  </span>
</template>

<script setup>
defineProps({
  text: { type: String, default: 'Badge' },
  variant: {
    type: String,
    default: 'default',
    validator: (v) => ['default', 'primary', 'success', 'warning', 'danger', 'info'].includes(v)
  },
  size: {
    type: String,
    default: 'md',
    validator: (v) => ['sm', 'md', 'lg'].includes(v)
  }
})
</script>

<style scoped>
.badge-label {
  display: inline-flex;
  align-items: center;
  font-weight: 600;
  border-radius: 999px;
  white-space: nowrap;
  font-family: Arial, sans-serif;
}
.sm { padding: 0.15rem 0.5rem; font-size: 0.7rem; }
.md { padding: 0.25rem 0.7rem; font-size: 0.8rem; }
.lg { padding: 0.35rem 0.9rem; font-size: 0.9rem; }
.default { background: #e9ecef; color: #495057; }
.primary { background: #d4edda; color: #155724; }
.success { background: #d4edda; color: #155724; }
.warning { background: #fff3cd; color: #856404; }
.danger { background: #f8d7da; color: #721c24; }
.info { background: #d1ecf1; color: #0c5460; }
</style>
