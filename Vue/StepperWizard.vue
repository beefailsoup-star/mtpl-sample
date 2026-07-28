<template>
  <div class="stepper-wizard">
    <div class="steps-indicator">
      <div
        v-for="(step, i) in steps"
        :key="i"
        class="step"
        :class="{ active: i === currentStep, completed: i < currentStep }"
        @click="goToStep(i)"
      >
        <div class="step-circle">
          <span v-if="i < currentStep">&#10003;</span>
          <span v-else>{{ i + 1 }}</span>
        </div>
        <span class="step-label">{{ step }}</span>
      </div>
    </div>
    <div class="step-content">
      <slot :currentStep="currentStep" />
    </div>
    <div class="step-actions">
      <button :disabled="currentStep === 0" @click="prevStep" class="btn-outline">Back</button>
      <button v-if="currentStep < steps.length - 1" @click="nextStep" class="btn-primary">Next</button>
      <button v-else @click="finish" class="btn-primary">Finish</button>
    </div>
  </div>
</template>

<script setup>
import { ref, provide } from 'vue'

const props = defineProps({
  steps: { type: Array, required: true }
})

const emit = defineEmits(['finish'])

const currentStep = ref(0)

provide('currentStep', currentStep)

const goToStep = (i) => {
  if (i <= currentStep.value) currentStep.value = i
}

const nextStep = () => {
  if (currentStep.value < props.steps.length - 1) currentStep.value++
}

const prevStep = () => {
  if (currentStep.value > 0) currentStep.value--
}

const finish = () => emit('finish')
</script>

<style scoped>
.stepper-wizard {
  font-family: Arial, sans-serif;
  max-width: 600px;
  margin: 0 auto;
}
.steps-indicator {
  display: flex;
  justify-content: space-between;
  margin-bottom: 2rem;
  position: relative;
}
.steps-indicator::before {
  content: '';
  position: absolute;
  top: 20px;
  left: 30px;
  right: 30px;
  height: 2px;
  background: #e0e0e0;
  z-index: 0;
}
.step {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 0.5rem;
  cursor: pointer;
  position: relative;
  z-index: 1;
}
.step-circle {
  width: 40px;
  height: 40px;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  font-weight: bold;
  font-size: 0.9rem;
  background: #e0e0e0;
  color: #999;
  transition: all 0.2s;
}
.step.active .step-circle {
  background: #42b883;
  color: white;
}
.step.completed .step-circle {
  background: #42b883;
  color: white;
}
.step-label {
  font-size: 0.8rem;
  color: #666;
}
.step.active .step-label {
  color: #42b883;
  font-weight: 600;
}
.step-content {
  min-height: 150px;
  padding: 1rem 0;
}
.step-actions {
  display: flex;
  justify-content: space-between;
  padding-top: 1rem;
  border-top: 1px solid #eee;
}
.btn-primary, .btn-outline {
  padding: 0.5rem 1.5rem;
  border-radius: 6px;
  font-size: 0.9rem;
  cursor: pointer;
  font-family: inherit;
}
.btn-primary {
  background: #42b883;
  color: white;
  border: none;
}
.btn-primary:disabled {
  opacity: 0.5;
  cursor: not-allowed;
}
.btn-outline {
  background: white;
  color: #666;
  border: 1px solid #ccc;
}
.btn-outline:disabled {
  opacity: 0.4;
  cursor: not-allowed;
}
</style>
