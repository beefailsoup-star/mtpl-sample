<template>
  <div class="video-player">
    <div class="video-wrapper" ref="wrapperRef">
      <video
        ref="videoRef"
        :src="src"
        :poster="poster"
        @timeupdate="onTimeUpdate"
        @loadedmetadata="onLoaded"
        @ended="playing = false"
        @play="playing = true"
        @pause="playing = false"
      ></video>
      <div class="controls" v-if="showControls">
        <button class="ctrl-btn" @click="togglePlay">
          {{ playing ? '⏸' : '▶' }}
        </button>
        <div class="progress-bar" @click="seek">
          <div class="progress-fill" :style="{ width: progress + '%' }"></div>
        </div>
        <span class="time">{{ formatTime(currentTime) }} / {{ formatTime(duration) }}</span>
        <button class="ctrl-btn" @click="toggleMute">
          {{ muted ? '🔇' : (volume > 0.5 ? '🔊' : '🔉') }}
        </button>
        <input
          type="range"
          min="0"
          max="1"
          step="0.05"
          :value="volume"
          @input="setVolume"
          class="volume-slider"
        />
        <button class="ctrl-btn" @click="toggleFullscreen">⛶</button>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, computed } from 'vue'

const props = defineProps({
  src: { type: String, required: true },
  poster: { type: String, default: '' },
  showControls: { type: Boolean, default: true }
})

const videoRef = ref(null)
const wrapperRef = ref(null)
const playing = ref(false)
const currentTime = ref(0)
const duration = ref(0)
const volume = ref(1)
const muted = ref(false)

const progress = computed(() => duration.value ? (currentTime.value / duration.value) * 100 : 0)

const togglePlay = () => {
  const v = videoRef.value
  if (!v) return
  v.paused ? v.play() : v.pause()
}

const toggleMute = () => {
  const v = videoRef.value
  if (!v) return
  v.muted = !v.muted
  muted.value = v.muted
}

const setVolume = (e) => {
  const v = videoRef.value
  if (!v) return
  v.volume = Number(e.target.value)
  volume.value = v.volume
}

const seek = (e) => {
  const v = videoRef.value
  if (!v) return
  const rect = e.currentTarget.getBoundingClientRect()
  const pos = (e.clientX - rect.left) / rect.width
  v.currentTime = pos * duration.value
}

const toggleFullscreen = () => {
  const el = wrapperRef.value
  if (!document.fullscreenElement) {
    el?.requestFullscreen()
  } else {
    document.exitFullscreen()
  }
}

const onTimeUpdate = () => {
  const v = videoRef.value
  if (v) currentTime.value = v.currentTime
}

const onLoaded = () => {
  const v = videoRef.value
  if (v) duration.value = v.duration
}

const formatTime = (t) => {
  if (!t || isNaN(t)) return '0:00'
  const m = Math.floor(t / 60)
  const s = Math.floor(t % 60)
  return `${m}:${s.toString().padStart(2, '0')}`
}
</script>

<style scoped>
.video-player {
  font-family: Arial, sans-serif;
  max-width: 640px;
  border-radius: 8px;
  overflow: hidden;
  background: #000;
}
.video-wrapper {
  position: relative;
}
.video-wrapper video {
  width: 100%;
  display: block;
}
.controls {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  padding: 0.5rem 0.75rem;
  background: rgba(0,0,0,0.75);
  color: white;
}
.ctrl-btn {
  background: none;
  border: none;
  color: white;
  font-size: 1.1rem;
  cursor: pointer;
  padding: 0.2rem;
}
.progress-bar {
  flex: 1;
  height: 5px;
  background: rgba(255,255,255,0.25);
  border-radius: 3px;
  cursor: pointer;
  position: relative;
}
.progress-fill {
  height: 100%;
  background: #42b883;
  border-radius: 3px;
  transition: width 0.1s;
}
.time {
  font-size: 0.8rem;
  white-space: nowrap;
  opacity: 0.8;
}
.volume-slider {
  width: 60px;
  accent-color: #42b883;
}
</style>
