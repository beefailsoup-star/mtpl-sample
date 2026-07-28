using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace MtplSample
{
    public class CsvExporter
    {
        private readonly string _delimiter;

        public CsvExporter(string delimiter = ",")
        {
            _delimiter = delimiter;
        }

        public string Export<T>(IEnumerable<T> records) where T : class
        {
            var sb = new StringBuilder();
            var properties = typeof(T).GetProperties();
            var headers = string.Join(_delimiter, properties.Select(p => EscapeField(p.Name)));
            sb.AppendLine(headers);

            foreach (var record in records)
            {
                var values = properties.Select(p =>
                {
                    var val = p.GetValue(record)?.ToString() ?? "";
                    return EscapeField(val);
                });
                sb.AppendLine(string.Join(_delimiter, values));
            }

            return sb.ToString();
        }

        public void ExportToFile<T>(string path, IEnumerable<T> records) where T : class
        {
            var content = Export(records);
            File.WriteAllText(path, content, Encoding.UTF8);
        }

        private string EscapeField(string value)
        {
            if (value.Contains(_delimiter) || value.Contains("\"") || value.Contains("\n"))
                return "\"" + value.Replace("\"", "\"\"") + "\"";
            return value;
        }
    }
}
