export interface CacheEntry<T> {
  value: T;
  expiresAt: number;
}

export class CacheManager<T> {
  private store = new Map<string, CacheEntry<T>>();
  private defaultTTL: number;
  constructor(defaultTTLMs: number = 60000) { this.defaultTTL = defaultTTLMs; }
  set(key: string, value: T, ttlMs?: number): void {
    this.store.set(key, { value, expiresAt: Date.now() + (ttlMs ?? this.defaultTTL) });
  }
  get(key: string): T | null {
    const entry = this.store.get(key);
    if (!entry) return null;
    if (Date.now() > entry.expiresAt) { this.store.delete(key); return null; }
    return entry.value;
  }
  has(key: string): boolean { return this.get(key) !== null; }
  delete(key: string): boolean { return this.store.delete(key); }
  clear(): void { this.store.clear(); }
  g