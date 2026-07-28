<template>
  <div class="star-rating" :title="`${modelValue} out of ${maxStars} stars`">
    <span
      v-for="star in maxStars"
      :key="star"
      class="star"
      :class="{ filled: star <= modelValue, half: star - 0.5 === modelValue }"
      @click="setRating(star)"
      @mouseenter="hovered = star"
      @mouseleave="hovered = 0"
    >
      {{ star <= (hovered || modelValue) ? '\u2605' : '\u2606' }}
    </span>
    <span v-if="showValue" class="value">{{ modelValue }} / {{ maxStars }}</span>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const props = defineProps({
  modelValue: { type: Number, default: 0 },
  maxStars: { type: Number, default: 5 },
  showValue: { type: Boolean, default: false }
})

const emit = defineEmits(['update:modelValue'])

const hovered = ref(0)

const setRating = (star) => emit('update:modelValue', star === props.modelValue ? 0 : star)
</script>

<style scoped>
.star-rating {
  display: inline-flex;
  align-items: center;
  gap: 0.15rem;
  font-family: Arial, sans-serif;
}
.star {
  font-size: 1.6rem;
  cursor: pointer;
  color: #ddd;
  transition: color 0.15s, transform 0.1s;
  user-select: none;
}
.star:hover {
  transform: scale(1.2);
}
.star.filled, .star.half {
  color: #f1c40f;
}
.value {
  margin-left: 0.5rem;
  font-size: 0.85rem;
  color: #888;
}
</style>
