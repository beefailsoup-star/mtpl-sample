<template>
  <header class="navbar-header">
    <div class="brand">
      <slot name="brand">
        <span class="logo">&#9670;</span>
        <span class="app-name">{{ appName }}</span>
      </slot>
    </div>
    <nav class="nav-links">
      <slot name="links">
        <a v-for="link in links" :key="link.label" :href="link.href" class="nav-link">
          {{ link.label }}
        </a>
      </slot>
    </nav>
    <div class="actions">
      <slot name="actions" />
    </div>
    <button class="hamburger" @click="mobileOpen = !mobileOpen" aria-label="Menu">
      <span></span><span></span><span></span>
    </button>
    <Transition name="mobile">
      <div v-if="mobileOpen" class="mobile-menu">
        <slot name="mobile-links">
          <a v-for="link in links" :key="link.label" :href="link.href" class="nav-link">
            {{ link.label }}
          </a>
        </slot>
      </div>
    </Transition>
  </header>
</template>

<script setup>
import { ref } from 'vue'

defineProps({
  appName: { type: String, default: 'MyApp' },
  links: {
    type: Array,
    default: () => [
      { label: 'Home', href: '/' },
      { label: 'About', href: '/about' },
      { label: 'Contact', href: '/contact' }
    ]
  }
})

const mobileOpen = ref(false)
</script>

<style scoped>
.navbar-header {
  display: flex;
  align-items: center;
  padding: 0 1.5rem;
  height: 60px;
  background: #2c3e50;
  color: white;
  font-family: Arial, sans-serif;
  position: relative;
}
.brand {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  margin-right: 2rem;
}
.logo {
  font-size: 1.5rem;
  color: #42b883;
}
.app-name {
  font-weight: bold;
  font-size: 1.1rem;
}
.nav-links {
  display: flex;
  gap: 1rem;
  flex: 1;
}
.nav-link {
  color: rgba(255,255,255,0.8);
  text-decoration: none;
  font-size: 0.9rem;
  padding: 0.25rem 0.5rem;
}
.nav-link:hover {
  color: white;
}
.actions {
  display: flex;
  align-items: center;
  gap: 0.5rem;
}
.hamburger {
  display: none;
  flex-direction: column;
  gap: 4px;
  background: none;
  border: none;
  cursor: pointer;
  padding: 0.4rem;
}
.hamburger span {
  display: block;
  width: 22px;
  height: 2px;
  background: white;
  border-radius: 2px;
}
.mobile-menu {
  display: none;
  position: absolute;
  top: 60px;
  left: 0;
  right: 0;
  background: #2c3e50;
  padding: 1rem;
  flex-direction: column;
  gap: 0.5rem;
}
@media (max-width: 768px) {
  .nav-links, .actions { display: none; }
  .hamburger { display: flex; }
  .mobile-menu { display: flex; }
}
.mobile-enter-active, .mobile-leave-active {
  transition: all 0.25s ease;
}
.mobile-enter-from, .mobile-leave-to {
  opacity: 0;
  transform: translateY(-10px);
}
</style>
