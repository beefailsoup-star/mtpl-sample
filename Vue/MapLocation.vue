<template>
  <div class="map-location">
    <div class="map-placeholder">
      <div class="map-inner">
        <div class="map-pin">&#128205;</div>
        <p v-if="address">{{ address }}</p>
        <p v-else class="hint">Map placeholder</p>
        <p class="coords" v-if="latitude && longitude">
          {{ latitude.toFixed(4) }}, {{ longitude.toFixed(4) }}
        </p>
        <slot name="actions">
          <a
            v-if="latitude && longitude"
            :href="`https://www.openstreetmap.org/?mlat=${latitude}&mlon=${longitude}&zoom=14`"
            target="_blank"
            class="map-link"
          >
            Open in OpenStreetMap
          </a>
        </slot>
      </div>
    </div>
  </div>
</template>

<script setup>
defineProps({
  latitude: { type: Number, default: null },
  longitude: { type: Number, default: null },
  address: { type: String, default: '' },
  zoom: { type: Number, default: 14 }
})
</script>

<style scoped>
.map-location {
  font-family: Arial, sans-serif;
}
.map-placeholder {
  background: #f0f4f8;
  border: 2px dashed #cbd5e1;
  border-radius: 12px;
  min-height: 200px;
  display: flex;
  align-items: center;
  justify-content: center;
}
.map-inner {
  text-align: center;
  padding: 1.5rem;
}
.map-pin {
  font-size: 2.5rem;
  margin-bottom: 0.25rem;
}
.hint {
  color: #94a3b8;
  font-size: 1.1rem;
  margin: 0;
}
.coords {
  color: #64748b;
  font-size: 0.85rem;
  margin: 0.5rem 0;
  font-family: monospace;
}
.map-link {
  display: inline-block;
  margin-top: 0.5rem;
  padding: 0.4rem 1rem;
  background: #42b883;
  color: white;
  border-radius: 6px;
  text-decoration: none;
  font-size: 0.85rem;
}
.map-link:hover {
  opacity: 0.85;
}
</style>
