<template>
  <div class="user-profile">
    <div class="avatar">
      <img :src="user.avatar" :alt="user.name" />
    </div>
    <div class="info">
      <h2>{{ user.name }}</h2>
      <p class="email">{{ user.email }}</p>
      <p class="bio">{{ user.bio }}</p>
    </div>
    <div class="stats">
      <div class="stat">
        <strong>{{ user.posts }}</strong>
        <span>Posts</span>
      </div>
      <div class="stat">
        <strong>{{ user.followers }}</strong>
        <span>Followers</span>
      </div>
      <div class="stat">
        <strong>{{ user.following }}</strong>
        <span>Following</span>
      </div>
    </div>
  </div>
</template>

<script setup>
defineProps({
  user: {
    type: Object,
    default: () => ({
      name: 'Jane Doe',
      email: 'jane@example.com',
      bio: 'Full-stack developer passionate about Vue.js.',
      avatar: 'https://i.pravatar.cc/120',
      posts: 42,
      followers: 128,
      following: 85
    })
  }
})
</script>

<style scoped>
.user-profile {
  max-width: 350px;
  border-radius: 12px;
  box-shadow: 0 2px 12px rgba(0, 0, 0, 0.1);
  padding: 2rem;
  text-align: center;
  font-family: Arial, sans-serif;
}
.avatar img {
  width: 100px;
  height: 100px;
  border-radius: 50%;
  object-fit: cover;
  border: 3px solid #42b883;
}
.info h2 {
  margin: 0.75rem 0 0.25rem;
  color: #2c3e50;
}
.email {
  color: #7f8c8d;
  font-size: 0.9rem;
}
.bio {
  color: #555;
  font-size: 0.95rem;
  margin: 0.75rem 0;
}
.stats {
  display: flex;
  justify-content: space-around;
  border-top: 1px solid #eee;
  padding-top: 1rem;
  margin-top: 0.5rem;
}
.stat {
  display: flex;
  flex-direction: column;
}
.stat strong {
  font-size: 1.2rem;
  color: #2c3e50;
}
.stat span {
  font-size: 0.8rem;
  color: #7f8c8d;
}
</style>
