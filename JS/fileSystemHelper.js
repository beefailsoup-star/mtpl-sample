'use strict';

const fs = require('fs');

const fileSystemHelper = {
  readFile(filePath, encoding = 'utf8') {
    return fs.promises.readFile(filePath, encoding);
  },

  writeFile(filePath, data, encoding = 'utf8') {
    return fs.promises.writeFile(filePath, data, encoding);
  },

  appendFile(filePath, data, encoding = 'utf8') {
    return fs.promises.appendFile(filePath, data, encoding);
  },

  deleteFile(filePath) {
    return fs.promises.unlink(filePath);
  },

  fileExists(filePath) {
    return fs.promises.access(filePath, fs.constants.F_OK)
      .then(() => true)
      .catch(() => false);
  },

  readDir(dirPath) {
    return fs.promises.readdir(dirPath);
  },

  copyFile(src, dest) {
    return fs.promises.copyFile(src, dest);
  }
};

module.exports = fileSystemHelper;
