'use strict';

const dateHelpers = {
  formatDate(date, format = 'YYYY-MM-DD') {
    const d = date instanceof Date ? date : new Date(date);
    if (isNaN(d.getTime())) return 'Invalid Date';
    const pad = n => String(n).padStart(2, '0');
    const map = {
      YYYY: d.getFullYear(),
      MM: pad(d.getMonth() + 1),
      DD: pad(d.getDate()),
      HH: pad(d.getHours()),
      mm: pad(d.getMinutes()),
      ss: pad(d.getSeconds())
    };
    return format.replace(/YYYY|MM|DD|HH|mm|ss/g, match => map[match]);
  },

  daysBetween(date1, date2) {
    const d1 = date1 instanceof Date ? date1 : new Date(date1);
    const d2 = date2 instanceof Date ? date2 : new Date(date2);
    const msPerDay = 24 * 60 * 60 * 1000;
    return Math.round(Math.abs((d2 - d1) / msPerDay));
  },

  addDays(date, days) {
    const d = date instanceof Date ? new Date(date) : new Date(date);
    d.setDate(d.getDate() + days);
    return d;
  },

  isWeekend(date) {
    const d = date instanceof Date ? date : new Date(date);
    const day = d.getDay();
    return day === 0 || day === 6;
  },

  toRelativeTime(date) {
    const d = date instanceof Date ? date : new Date(date);
    const now = new Date();
    const diffMs = now - d;
    const absDiff = Math.abs(diffMs);
    const seconds = Math.floor(absDiff / 1000);
    const minutes = Math.floor(seconds / 60);
    const hours = Math.floor(minutes / 60);
    const days = Math.floor(hours / 24);
    const weeks = Math.floor(days / 7);
    const months = Math.floor(days / 30);
    const years = Math.floor(days / 365);

    const suffix = diffMs >= 0 ? 'ago' : 'from now';

    if (seconds < 60) return `${seconds} seconds ${suffix}`;
    if (minutes < 60) return `${minutes} minutes ${suffix}`;
    if (hours < 24) return `${hours} hours ${suffix}`;
    if (days < 7) return `${days} days ${suffix}`;
    if (weeks < 5) return `${weeks} weeks ${suffix}`;
    if (months < 12) return `${months} months ${suffix}`;
    return `${years} years ${suffix}`;
  }
};

module.exports = dateHelpers;
