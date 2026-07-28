<template>
  <div v-show="activeTab.value === index" class="tab-panel" role="tabpanel">
    <slot />
  </div>
</template>

<script setup>
import { inject, getCurrentInstance, onMounted } from 'vue'

const props = defineProps({
  title: { type: String, required: true }
})

const registerTab = inject('registerTab')
const activeTab = inject('activeTab')

const instance = getCurrentInstance()
const index = instance.vnode.key ?? 0

onMounted(() => {
  registerTab(props.title)
})
</script>

<style scoped>
.tab-panel {
  animation: fadeIn 0.2s ease;
}
@keyframes fadeIn {
  from { opacity: 0; }
  to { opacity: 1; }
}
</style>
