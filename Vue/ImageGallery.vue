<template>
  <div class="image-gallery">
    <div class="grid">
      <div
        v-for="(img, index) in images"
        :key="index"
        class="thumb"
        @click="openLightbox(index)"
      >
        <img :src="img.thumbnail" :alt="img.alt" loading="lazy" />
      </div>
    </div>
    <Transition name="lightbox">
      <div v-if="lightboxOpen" class="lightbox-overlay" @click.self="closeLightbox">
        <button class="nav prev" @click="prevImage">&lsaquo;</button>
        <img :src="images[activeIndex].full" :alt="images[activeIndex].alt" />
        <button class="nav next" @click="nextImage">&rsaquo;</button>
        <button class="close-lb" @click="closeLightbox">&times;</button>
        <div class="caption">{{ images[activeIndex].alt }}</div>
      </div>
    </Transition>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const props = defineProps({
  images: {
    type: Array,
    default: () => [
      { thumbnail: 'https://picsum.photos/200/200?random=1', full: 'https://picsum.photos/800/600?random=1', alt: 'Image 1' },
      { thumbnail: 'https://picsum.photos/200/200?random=2', full: 'https://picsum.photos/800/600?random=2', alt: 'Image 2' },
      { thumbnail: 'https://picsum.photos/200/200?random=3', full: 'https://picsum.photos/800/600?random=3', alt: 'Image 3' },
      { thumbnail: 'https://picsum.photos/200/200?random=4', full: 'https://picsum.photos/800/600?random=4', alt: 'Image 4' }
    ]
  }
})

const lightboxOpen = ref(false)
const activeIndex = ref(0)

const openLightbox = (index) => {
  activeIndex.value = index
  lightboxOpen.value = true
}

const closeLightbox = () => { lightboxOpen.value = false }

const prevImage = () => {
  activeIndex.value = (activeIndex.value - 1 + props.images.length) % props.images.length
}

const nextImage = () => {
  activeIndex.value = (activeIndex.value + 1) % props.images.length
}
</script>

<style scoped>
.grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(150px, 1fr));
  gap: 0.75rem;
}
.thumb {
  cursor: pointer;
  border-radius: 8px;
  overflow: hidden;
  aspect-ratio: 1;
}
.thumb img {
  width: 100%;
  height: 100%;
  object-fit: cover;
  transition: transform 0.2s;
}
.thumb:hover img {
  transform: scale(1.08);
}
.lightbox-overlay {
  position: fixed;
  inset: 0;
  background: rgba(0,0,0,0.9);
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 2000;
}
.lightbox-overlay img {
  max-width: 85vw;
  max-height: 80vh;
  border-radius: 6px;
  box-shadow: 0 4px 20px rgba(0,0,0,0.5);
}
.nav {
  position: absolute;
  top: 50%;
  transform: translateY(-50%);
  background: rgba(255,255,255,0.15);
  color: white;
  border: none;
  font-size: 2.5rem;
  padding: 0.5rem 1rem;
  cursor: pointer;
  border-radius: 4px;
}
.nav:hover { background: rgba(255,255,255,0.3); }
.prev { left: 1rem; }
.next { right: 1rem; }
.close-lb {
  position: absolute;
  top: 1rem;
  right: 1.5rem;
  background: none;
  border: none;
  color: white;
  font-size: 2.5rem;
  cursor: pointer;
}
.caption {
  position: absolute;
  bottom: 1.5rem;
  color: white;
  font-size: 1rem;
  font-family: Arial, sans-serif;
}
.lightbox-enter-active, .lightbox-leave-active {
  transition: opacity 0.25s ease;
}
.lightbox-enter-from, .lightbox-leave-to {
  opacity: 0;
}
</style>
