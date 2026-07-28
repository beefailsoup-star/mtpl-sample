<template>
  <footer class="footer-section">
    <div class="footer-content">
      <div class="footer-columns">
        <div class="footer-col">
          <slot name="brand">
            <h4>{{ brandName }}</h4>
            <p>{{ tagline }}</p>
          </slot>
        </div>
        <div v-for="(col, i) in columns" :key="i" class="footer-col">
          <h5>{{ col.title }}</h5>
          <ul>
            <li v-for="link in col.links" :key="link.label">
              <a :href="link.href">{{ link.label }}</a>
            </li>
          </ul>
        </div>
      </div>
      <div class="footer-bottom">
        <p>&copy; {{ year }} {{ brandName }}. All rights reserved.</p>
        <div class="social-links">
          <a v-for="social in socials" :key="social.label" :href="social.href" :title="social.label">
            {{ social.icon }}
          </a>
        </div>
      </div>
    </div>
  </footer>
</template>

<script setup>
defineProps({
  brandName: { type: String, default: 'MyApp' },
  tagline: { type: String, default: 'Building amazing experiences.' },
  columns: {
    type: Array,
    default: () => [
      {
        title: 'Product',
        links: [
          { label: 'Features', href: '#' },
          { label: 'Pricing', href: '#' },
          { label: 'Changelog', href: '#' }
        ]
      },
      {
        title: 'Company',
        links: [
          { label: 'About', href: '#' },
          { label: 'Blog', href: '#' },
          { label: 'Contact', href: '#' }
        ]
      },
      {
        title: 'Legal',
        links: [
          { label: 'Privacy', href: '#' },
          { label: 'Terms', href: '#' }
        ]
      }
    ]
  },
  socials: {
    type: Array,
    default: () => [
      { label: 'Twitter', href: '#', icon: '&#120143;' },
      { label: 'GitHub', href: '#', icon: '&#128190;' },
      { label: 'LinkedIn', href: '#', icon: '&#128100;' }
    ]
  }
})

const year = new Date().getFullYear()
</script>

<style scoped>
.footer-section {
  background: #2c3e50;
  color: #ccc;
  font-family: Arial, sans-serif;
  padding: 2.5rem 1.5rem 1.5rem;
}
.footer-content {
  max-width: 1000px;
  margin: 0 auto;
}
.footer-columns {
  display: flex;
  flex-wrap: wrap;
  gap: 2rem;
  justify-content: space-between;
}
.footer-col {
  flex: 1;
  min-width: 140px;
}
.footer-col h4 {
  color: white;
  margin: 0 0 0.5rem;
  font-size: 1.1rem;
}
.footer-col h5 {
  color: white;
  margin: 0 0 0.75rem;
  font-size: 0.9rem;
  text-transform: uppercase;
  letter-spacing: 0.5px;
}
.footer-col p {
  font-size: 0.85rem;
  margin: 0;
  color: #999;
}
.footer-col ul {
  list-style: none;
  padding: 0;
  margin: 0;
}
.footer-col li {
  margin-bottom: 0.35rem;
}
.footer-col a {
  color: #999;
  text-decoration: none;
  font-size: 0.85rem;
}
.footer-col a:hover {
  color: #42b883;
}
.footer-bottom {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-top: 2rem;
  padding-top: 1.25rem;
  border-top: 1px solid rgba(255,255,255,0.08);
  font-size: 0.8rem;
}
.footer-bottom p {
  margin: 0;
  color: #777;
}
.social-links {
  display: flex;
  gap: 0.75rem;
}
.social-links a {
  color: #999;
  text-decoration: none;
  font-size: 1.1rem;
}
.social-links a:hover {
  color: #42b883;
}
</style>
