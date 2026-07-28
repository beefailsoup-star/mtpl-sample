using System;
using System.IO;
using System.Threading;

namespace MtplSample
{
    public sealed class LoggerService
    {
        private static readonly Lazy<LoggerService> _instance = new(() => new LoggerService(), LazyThreadSafetyMode.ExecutionAndPublication);

        private readonly string _logPath;
        private readonly object _lock = new();

        private LoggerService()
        {
            _logPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "logs");
            Directory.CreateDirectory(_logPath);
        }

        public static LoggerService Instance => _instance.Value;

        public void LogInfo(string message) => WriteLog("INFO", message);

        public void LogWarning(string message) => WriteLog("WARN", message);

        public void LogError(string message, Exception ex = null)
        {
            var msg = ex == null ? message : $"{message} | Exception: {ex}";
            WriteLog("ERROR", msg);
        }

        private void WriteLog(string level, string message)
        {
            lock (_lock)
            {
                var line = $"{DateTime.UtcNow:yyyy-MM-dd HH:mm:ss.fff} [{level}] {message}";
                var file = Path.Combine(_logPath, $"log-{DateTime.UtcNow:yyyyMMdd}.txt");
                File.AppendAllText(file, line + Environment.NewLine);
            }
        }
    }
}
