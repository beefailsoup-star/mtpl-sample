<template>
  <div class="audio-player">
    <div class="player-bar">
      <button class="ctrl-btn" @click="togglePlay">
        {{ playing ? '⏸' : '▶' }}
      </button>
      <div class="track-info">
        <span class="track-name">{{ trackName }}</span>
        <span class="artist">{{ artist }}</span>
      </div>
      <div class="progress-wrap" @click="seek">
        <div class="progress-track">
          <div class="progress-fill" :style="{ width: progress + '%' }"></div>
        </div>
      </div>
      <span class="time-display">{{ formatTime(currentTime) }} / {{ formatTime(duration) }}</span>
      <button class="ctrl-btn" @click="toggleMute">
        {{ muted ? '🔇' : '🔊' }}
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
    </div>
    <audio
      ref="audioRef"
      :src="src"
      @timeupdate="onTimeUpdate"
      @loadedmetadata="onLoaded"
      @ended="playing = false"
      @play="playing = true"
      @pause="playing = false"
    ></audio>
  </div>
</template>

<script setup>
import { ref, computed } from 'vue'

const props = defineProps({
  src: { type: String, required: true },
  trackName: { type: String, default: 'Unknown Track' },
  artist: { type: String, default: 'Unknown Artist' }
})

const audioRef = ref(null)
const playing = ref(false)
const currentTime = ref(0)
const duration = ref(0)
const volume = ref(1)
const muted = ref(false)

const progress = computed(() => duration.value ? (currentTime.value / duration.value) * 100 : 0)

const togglePlay = () => {
  const a = audioRef.value
  if (!a) return
  a.paused ? a.play() : a.pause()
}

const toggleMute = () => {
  const a = audioRef.value
  if (!a) return
  a.muted = !a.muted
  muted.value = a.muted
}

const setVolume = (e) => {
  const a = audioRef.value
  if (!a) return
  a.volume = Number(e.target.value)
  volume.value = a.volume
}

const seek = (e) => {
  const a = audioRef.value
  if (!a) return
  const rect = e.currentTarget.getBoundingClientRect()
  const pos = (e.clientX - rect.left) / rect.width
  a.currentTime = pos * duration.value
}

const onTimeUpdate = () => {
  const a = audioRef.value
  if (a) currentTime.value = a.currentTime
}

const onLoaded = () => {
  const a = audioRef.value
  if (a) duration.value = a.duration
}

const formatTime = (t) => {
  if (!t || isNaN(t)) return '0:00'
  const m = Math.floor(t / 60)
  const s = Math.floor(t % 60)
  return `${m}:${s.toString().padStart(2, '0')}`
}
</script>

<style scoped>
.audio-player {
  background: #f8f9fa;
  border-radius: 10px;
  padding: 0.75rem 1rem;
  font-family: Arial, sans-serif;
  border: 1px solid #e0e0e0;
  max-width: 500px;
}
.player-bar {
  display: flex;
  align-items: center;
  gap: 0.75rem;
}
.ctrl-btn {
  background: none;
  border: none;
  font-size: 1.3rem;
  cursor: pointer;
  color: #2c3e50;
  padding: 0;
}
.ctrl-btn:hover {
  color: #42b883;
}
.track-info {
  display: flex;
  flex-direction: column;
  min-width: 100px;
}
.track-name {
  font-size: 0.9rem;
  font-weight: 600;
  color: #2c3e50;
}
.artist {
  font-size: 0.75rem;
  color: #999;
}
.progress-wrap {
  flex: 1;
  cursor: pointer;
  height: 6px;
  display: flex;
  align-items: center;
}
.progress-track {
  width: 100%;
  height: 5px;
  background: #e0e0e0;
  border-radius: 3px;
  overflow: hidden;
}
.progress-fill {
  height: 100%;
  background: #42b883;
  border-radius: 3px;
  transition: width 0.1s;
}
.time-display {
  font-size: 0.75rem;
  color: #999;
  white-space: nowrap;
  font-family: monospace;
}
.volume-slider {
  width: 60px;
  accent-color: #42b883;
}
</style>
