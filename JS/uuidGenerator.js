const crypto = require('crypto');

function uuidv4() {
  return crypto.randomUUID();
}

function uuidv7() {
  const now = Date.now();
  const timeHex = now.toString(16).padStart(12, '0');
  const randomChars = crypto.randomBytes(10).toString('hex');
  const version = '7';
  const variant = '8';
  return `${timeHex.slice(0, 8)}-${timeHex.slice(8, 12)}-${version}${randomChars.slice(0, 3)}-${variant}${randomChars.slice(3, 7)}-${randomChars.slice(7, 19)}`;
}

function isValidUUID(str) {
  if (typeof str !== 'string') return false;
  return /^[0-9a-f]{8}-[0-9a-f]{4}-[1-8][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i.test(str);
}

module.exports = { uuidv4, uuidv7, isValidUUID };
