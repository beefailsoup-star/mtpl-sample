'use strict';

const csvParser = {
  parseCSV(csvText, delimiter = ',') {
    if (!csvText || typeof csvText !== 'string') return [];
    const lines = csvText.trim().split(/\r?\n/);
    if (lines.length === 0) return [];
    const headers = lines[0].split(delimiter).map(h => h.trim());

    return lines.slice(1).map(line => {
      if (!line.trim()) return null;
      const values = [];
      let current = '';
      let inQuotes = false;
      for (let i = 0; i < line.length; i++) {
        const ch = line[i];
        if (ch === '"') {
          if (inQuotes && i + 1 < line.length && line[i + 1] === '"') {
            current += '"';
            i++;
          } else {
            inQuotes = !inQuotes;
          }
        } else if (ch === delimiter && !inQuotes) {
          values.push(current.trim());
          current = '';
        } else {
          current += ch;
        }
      }
      values.push(current.trim());
      const row = {};
      headers.forEach((header, idx) => {
        row[header] = values[idx] || '';
      });
      return row;
    }).filter(row => row !== null);
  },

  stringifyCSV(data, delimiter = ',') {
    if (!Array.isArray(data) || data.length === 0) return '';
    const headers = Object.keys(data[0]);
    const lines = data.map(row =>
      headers.map(key => {
        let val = row[key];
        if (val === null || val === undefined) val = '';
        val = String(val);
        if (val.includes(delimiter) || val.includes('"') || val.includes('\n')) {
          val = '"' + val.replace(/"/g, '""') + '"';
        }
        return val;
      }).join(delimiter)
    );
    return headers.join(delimiter) + '\n' + lines.join('\n');
  }
};

module.exports = csvParser;
