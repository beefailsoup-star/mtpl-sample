<template>
  <aside class="sidebar-menu">
    <nav>
      <ul>
        <li v-for="item in items" :key="item.label">
          <div
            class="menu-item"
            :class="{ active: item.active, collapsed: item.children && !item.expanded }"
            @click="toggleItem(item)"
          >
            <span class="icon">{{ item.icon }}</span>
            <span class="label">{{ item.label }}</span>
            <span v-if="item.children" class="chevron">{{ item.expanded ? '▼' : '▶' }}</span>
          </div>
          <Transition name="sub">
            <ul v-if="item.children && item.expanded" class="sub-menu">
              <li v-for="child in item.children" :key="child.label">
                <div class="menu-item sub" :class="{ active: child.active }" @click="child.onClick">
                  <span class="label">{{ child.label }}</span>
                </div>
              </li>
            </ul>
          </Transition>
        </li>
      </ul>
    </nav>
  </aside>
</template>

<script setup>
defineProps({
  items: {
    type: Array,
    required: true
  }
})

const toggleItem = (item) => {
  if (item.children) {
    item.expanded = !item.expanded
  } else if (item.onClick) {
    item.onClick()
  }
}
</script>

<style scoped>
.sidebar-menu {
  width: 240px;
  background: #2c3e50;
  color: white;
  font-family: Arial, sans-serif;
  border-radius: 8px;
  overflow: hidden;
}
.sidebar-menu ul {
  list-style: none;
  padding: 0;
  margin: 0;
}
.menu-item {
  display: flex;
  align-items: center;
  padding: 0.7rem 1rem;
  cursor: pointer;
  transition: background 0.15s;
  gap: 0.5rem;
  user-select: none;
}
.menu-item:hover {
  background: rgba(255,255,255,0.08);
}
.menu-item.active {
  background: #42b883;
  color: white;
}
.menu-item .icon {
  width: 1.4rem;
  text-align: center;
}
.menu-item .label {
  flex: 1;
  font-size: 0.9rem;
}
.chevron {
  font-size: 0.65rem;
  opacity: 0.7;
}
.sub-menu {
  background: rgba(0,0,0,0.15);
}
.sub-menu .menu-item {
  padding-left: 2.5rem;
}
.sub-enter-active, .sub-leave-active {
  transition: all 0.2s ease;
  overflow: hidden;
}
.sub-enter-from, .sub-leave-to {
  max-height: 0;
  opacity: 0;
}
</style>
