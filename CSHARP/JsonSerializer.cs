using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace MtplSample
{
    public class JsonSerializer
    {
        public string Serialize(object obj)
        {
            if (obj == null) return "null";
            return SerializeValue(obj);
        }

        private string SerializeValue(object value)
        {
            if (value == null) return "null";
            if (value is string s) return $"\"{EscapeString(s)}\"";
            if (value is bool b) return b ? "true" : "false";
            if (value is int || value is long || value is float || value is double || value is decimal)
                return Convert.ToString(value, System.Globalization.CultureInfo.InvariantCulture);
            if (value is DateTime dt) return $"\"{dt:yyyy-MM-ddTHH:mm:ss.fffZ}\"";
            if (value is Guid g) return $"\"{g:D}\"";
            if (value is IEnumerable enumerable and not string) return SerializeArray(enumerable);
            if (value.GetType().IsClass) return SerializeObject(value);

            return value.ToString();
        }

        private string SerializeObject(object obj)
        {
            var sb = new StringBuilder("{");
            var properties = obj.GetType().GetProperties(BindingFlags.Public | BindingFlags.Instance);
            var pairs = new List<string>();

            foreach (var prop in properties)
            {
                if (!prop.CanRead) continue;
                var val = prop.GetValue(obj);
                pairs.Add($"\"{prop.Name}\":{SerializeValue(val)}");
            }

            sb.Append(string.Join(",", pairs));
            sb.Append("}");
            return sb.ToString();
        }

        private string SerializeArray(IEnumerable enumerable)
        {
            var items = enumerable.Cast<object>().Select(SerializeValue);
            return "[" + string.Join(",", items) + "]";
        }

        private static string EscapeString(string s)
        {
            return s.Replace("\\", "\\\\").Replace("\"", "\\\"").Replace("\n", "\\n").Replace("\r", "\\r").Replace("\t", "\\t");
        }
    }
}
