'use strict';

const { spawn, execSync } = require('child_process');

const processRunner = {
  runCommand(command, args = [], options = {}) {
    return new Promise((resolve, reject) => {
      const child = spawn(command, args, { stdio: 'pipe', ...options });
      let stdout = '';
      let stderr = '';

      child.stdout.on('data', data => { stdout += data.toString(); });
      child.stderr.on('data', data => { stderr += data.toString(); });

      child.on('close', code => {
        if (code === 0) {
          resolve({ stdout, stderr, code });
        } else {
          const err = new Error(`Command exited with code ${code}`);
          err.stdout = stdout;
          err.stderr = stderr;
          err.code = code;
          reject(err);
        }
      });

      child.on('error', reject);
    });
  },

  runSync(command, options = {}) {
    try {
      const stdout = execSync(command, { encoding: 'utf8', ...options });
      return { stdout: stdout.trim(), code: 0 };
    } catch (err) {
      return { stdout: '', stderr: err.stderr, code: err.status };
    }
  },

  spawnDetached(command, args = [], options = {}) {
    const child = spawn(command, args, {
      detached: true,
      stdio: 'ignore',
      ...options
    });
    child.unref();
    return child;
  }
};

module.exports = processRunner;
