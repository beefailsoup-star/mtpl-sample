const htmlEntities = {
  '&': '&amp;',
  '<': '&lt;',
  '>': '&gt;',
  '"': '&quot;',
  "'": '&#39;',
  '/': '&#x2F;'
};

const reverseEntities = {};
for (const [char, entity] of Object.entries(htmlEntities)) {
  reverseEntities[entity] = char;
}

function encode(str) {
  if (typeof str !== 'string') return '';
  return str.replace(/[&<>"'/]/g, ch => htmlEntities[ch] || ch);
}

function encodeAttr(str) {
  if (typeof str !== 'string') return '';
  return str.replace(/[&<>"'/]/g, ch => htmlEntities[ch] || ch);
}

function stripHTML(str) {
  if (typeof str !== 'string') return '';
  return str.replace(/<[^>]*>/g, '');
}

function decode(str) {
  if (typeof str !== 'string') return '';
  return str.replace(/&(?:amp|lt|gt|quot|#39|#x2F);/g, entity => reverseEntities[entity] || entity);
}

module.exports = { encode, decode, encodeAttr, stripHTML };
