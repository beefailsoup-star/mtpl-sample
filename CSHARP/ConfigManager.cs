using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;

namespace MtplSample
{
    public class ConfigManager
    {
        private readonly string _filePath;
        private Dictionary<string, object> _config;

        public ConfigManager(string filePath = null)
        {
            _filePath = filePath ?? Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "appsettings.json");
            _config = new Dictionary<string, object>();
        }

        public void Load()
        {
            if (!File.Exists(_filePath))
                throw new FileNotFoundException($"Configuration file not found: {_filePath}");

            var json = File.ReadAllText(_filePath);
            _config = JsonSerializer.Deserialize<Dictionary<string, object>>(json) ?? new Dictionary<string, object>();
        }

        public T Get<T>(string key, T defaultValue = default)
        {
            if (_config.TryGetValue(key, out var value))
            {
                try
                {
                    return (T)Convert.ChangeType(value, typeof(T));
                }
                catch
                {
                    return defaultValue;
                }
            }
            return defaultValue;
        }

        public void Set<T>(string key, T value)
        {
            _config[key] = value;
        }

        public void Save()
        {
            var json = JsonSerializer.Serialize(_config, new JsonSerializerOptions { WriteIndented = true });
            File.WriteAllText(_filePath, json);
        }
    }
}
