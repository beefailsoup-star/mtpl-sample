function hashString(str, seed) {
  let hash = seed;
  for (let i = 0; i < str.length; i++) {
    hash = ((hash << 5) - hash) + str.charCodeAt(i);
    hash = hash & hash;
  }
  return Math.abs(hash);
}

class BloomFilter {
  constructor(size = 512, hashCount = 3) {
    this.size = size;
    this.hashCount = hashCount;
    this.bitArray = new Array(size).fill(0);
  }

  _getHashes(value) {
    const str = String(value);
    const seeds = [];
    for (let i = 0; i < this.hashCount; i++) {
      seeds.push(hashString(str, i * 31 + 7) % this.size);
    }
    return seeds;
  }

  add(value) {
    const hashes = this._getHashes(value);
    for (const hash of hashes) {
      this.bitArray[hash] = 1;
    }
    return this;
  }

  has(value) {
    const hashes = this._getHashes(value);
    for (const hash of hashes) {
      if (this.bitArray[hash] === 0) return false;
    }
    return true;
  }

  clear() {
    this.bitArray.fill(0);
    return this;
  }
}

module.exports = { BloomFilter };
