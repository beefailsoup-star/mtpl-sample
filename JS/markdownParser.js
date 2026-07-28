function renderBold(text) {
  return `<strong>${text}</strong>`;
}

function renderItalic(text) {
  return `<em>${text}</em>`;
}

function renderLink(text, url) {
  return `<a href="${url}">${text}</a>`;
}

function parseMarkdown(md) {
  if (typeof md !== 'string') return '';

  const lines = md.split('\n');
  const html = [];
  let inCodeBlock = false;
  let codeContent = [];

  for (let i = 0; i < lines.length; i++) {
    const line = lines[i];

    if (line.startsWith('```')) {
      if (inCodeBlock) {
        html.push(`<pre><code>${codeContent.join('\n')}</code></pre>`);
        codeContent = [];
      }
      inCodeBlock = !inCodeBlock;
      continue;
    }

    if (inCodeBlock) {
      codeContent.push(line.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;'));
      continue;
    }

    if (line.startsWith('### ')) {
      html.push(`<h3>${line.slice(4)}</h3>`);
    } else if (line.startsWith('## ')) {
      html.push(`<h2>${line.slice(3)}</h2>`);
    } else if (line.startsWith('# ')) {
      html.push(`<h1>${line.slice(2)}</h1>`);
    } else if (line.startsWith('- ') || line.startsWith('* ')) {
      html.push(`<li>${line.slice(2)}</li>`);
    } else if (line.trim() === '') {
      html.push('');
    } else {
      let processed = line.replace(/\*\*(.+?)\*\*/g, '<strong>$1</strong>');
      processed = processed.replace(/\*(.+?)\*/g, '<em>$1</em>');
      processed = processed.replace(/\[(.+?)\]\((.+?)\)/g, '<a href="$2">$1</a>');
      html.push(`<p>${processed}</p>`);
    }
  }

  if (inCodeBlock) {
    html.push(`<pre><code>${codeContent.join('\n')}</code></pre>`);
  }

  const result = [];
  let inList = false;
  for (const el of html) {
    if (el.startsWith('<li>')) {
      if (!inList) {
        result.push('<ul>');
        inList = true;
      }
      result.push(el);
    } else {
      if (inList) {
        result.push('</ul>');
        inList = false;
      }
      if (el !== '') result.push(el);
    }
  }
  if (inList) result.push('</ul>');

  return result.join('\n');
}

module.exports = { parseMarkdown, renderBold, renderItalic, renderLink };
