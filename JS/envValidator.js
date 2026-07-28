function getEnv(key, defaultValue) {
  const value = process.env[key];
  if (value === undefined || value === null) {
    if (defaultValue !== undefined) return defaultValue;
    throw new Error(`Environment variable "${key}" is not set and no default value provided`);
  }
  return value;
}

function getEnvInt(key, defaultValue) {
  const value = getEnv(key, defaultValue !== undefined ? String(defaultValue) : undefined);
  const parsed = parseInt(value, 10);
  if (isNaN(parsed)) {
    throw new Error(`Environment variable "${key}" with value "${value}" is not a valid integer`);
  }
  return parsed;
}

function getEnvFloat(key, defaultValue) {
  const value = getEnv(key, defaultValue !== undefined ? String(defaultValue) : undefined);
  const parsed = parseFloat(value);
  if (isNaN(parsed)) {
    throw new Error(`Environment variable "${key}" with value "${value}" is not a valid float`);
  }
  return parsed;
}

function getEnvBool(key, defaultValue) {
  const value = process.env[key];
  if (value === undefined || value === null) {
    if (defaultValue !== undefined) return defaultValue;
    throw new Error(`Environment variable "${key}" is not set and no default value provided`);
  }
  const lower = value.toLowerCase();
  if (['true', '1', 'yes', 'y'].includes(lower)) return true;
  if (['false', '0', 'no', 'n'].includes(lower)) return false;
  throw new Error(`Environment variable "${key}" with value "${value}" is not a valid boolean`);
}

function validateEnv(keys, options = {}) {
  const { strict = true } = options;
  const missing = [];
  const invalid = [];

  for (const key of keys) {
    const value = process.env[key];
    if (value === undefined || value === null) {
      missing.push(key);
    }
  }

  if (strict && missing.length > 0) {
    throw new Error(`Missing required environment variables: ${missing.join(', ')}`);
  }

  return { missing, invalid };
}

module.exports = { validateEnv, getEnv, getEnvInt, getEnvFloat, getEnvBool };
