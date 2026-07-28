function linearSearch(arr, target) {
  for (let i = 0; i < arr.length; i++) {
    if (arr[i] === target) return i;
  }
  return -1;
}

function binarySearch(arr, target) {
  const sorted = [...arr].sort((a, b) => a - b);
  let left = 0;
  let right = sorted.length - 1;
  while (left <= right) {
    const mid = Math.floor((left + right) / 2);
    if (sorted[mid] === target) return mid;
    if (sorted[mid] < target) left = mid + 1;
    else right = mid - 1;
  }
  return -1;
}

function interpolationSearch(arr, target) {
  const sorted = [...arr].sort((a, b) => a - b);
  let low = 0;
  let high = sorted.length - 1;
  while (low <= high && target >= sorted[low] && target <= sorted[high]) {
    const pos = low + Math.floor(((target - sorted[low]) * (high - low)) / (sorted[high] - sorted[low]));
    if (sorted[pos] === target) return pos;
    if (sorted[pos] < target) low = pos + 1;
    else high = pos - 1;
  }
  return -1;
}

function jumpSearch(arr, target) {
  const sorted = [...arr].sort((a, b) => a - b);
  const n = sorted.length;
  const step = Math.floor(Math.sqrt(n));
  let prev = 0;
  while (sorted[Math.min(step, n) - 1] < target) {
    prev = step;
    if (prev >= n) return -1;
  }
  for (let i = prev; i < Math.min(step + prev, n); i++) {
    if (sorted[i] === target) return i;
  }
  return -1;
}

module.exports = { linearSearch, binarySearch, interpolationSearch, jumpSearch };
