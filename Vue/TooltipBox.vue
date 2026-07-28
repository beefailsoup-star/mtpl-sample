<template>
  <div class="tooltip-box" @mouseenter="show = true" @mouseleave="show = false">
    <slot />
    <Transition name="tooltip">
      <div v-if="show" class="tooltip" :class="position">
        {{ text }}
        <div class="arrow"></div>
      </div>
    </Transition>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const props = defineProps({
  text: { type: String, required: true },
  position: { type: String, default: 'top' }
})

const show = ref(false)
</script>

<style scoped>
.tooltip-box {
  position: relative;
  display: inline-block;
  cursor: pointer;
}
.tooltip {
  position: absolute;
  background: #333;
  color: white;
  padding: 0.4rem 0.75rem;
  border-radius: 4px;
  font-size: 0.8rem;
  white-space: nowrap;
  z-index: 500;
  pointer-events: none;
}
.tooltip .arrow {
  position: absolute;
  width: 0;
  height: 0;
  border: 5px solid transparent;
}
.tooltip.top {
  bottom: 100%;
  left: 50%;
  transform: translateX(-50%);
  margin-bottom: 6px;
}
.tooltip.top .arrow {
  top: 100%;
  left: 50%;
  margin-left: -5px;
  border-top-color: #333;
}
.tooltip.bottom {
  top: 100%;
  left: 50%;
  transform: translateX(-50%);
  margin-top: 6px;
}
.tooltip.bottom .arrow {
  bottom: 100%;
  left: 50%;
  margin-left: -5px;
  border-bottom-color: #333;
}
.tooltip.left {
  right: 100%;
  top: 50%;
  transform: translateY(-50%);
  margin-right: 6px;
}
.tooltip.left .arrow {
  left: 100%;
  top: 50%;
  margin-top: -5px;
  border-left-color: #333;
}
.tooltip.right {
  left: 100%;
  top: 50%;
  transform: translateY(-50%);
  margin-left: 6px;
}
.tooltip.right .arrow {
  right: 100%;
  top: 50%;
  margin-top: -5px;
  border-right-color: #333;
}
.tooltip-enter-active, .tooltip-leave-active {
  transition: opacity 0.15s ease;
}
.tooltip-enter-from, .tooltip-leave-to {
  opacity: 0;
}
</style>
