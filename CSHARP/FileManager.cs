using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace MtplSample
{
    public class FileManager
    {
        public Task WriteTextAsync(string path, string content)
        {
            var dir = Path.GetDirectoryName(path);
            if (!string.IsNullOrEmpty(dir) && !Directory.Exists(dir))
                Directory.CreateDirectory(dir);
            return File.WriteAllTextAsync(path, content, Encoding.UTF8);
        }

        public Task<string> ReadTextAsync(string path)
        {
            if (!File.Exists(path))
                throw new FileNotFoundException("File not found.", path);
            return File.ReadAllTextAsync(path, Encoding.UTF8);
        }

        public Task AppendTextAsync(string path, string content)
        {
            var dir = Path.GetDirectoryName(path);
            if (!string.IsNullOrEmpty(dir) && !Directory.Exists(dir))
                Directory.CreateDirectory(dir);
            return File.AppendAllTextAsync(path, content + Environment.NewLine, Encoding.UTF8);
        }

        public void Copy(string source, string destination, bool overwrite = false)
        {
            File.Copy(source, destination, overwrite);
        }

        public void Move(string source, string destination, bool overwrite = false)
        {
            if (overwrite && File.Exists(destination))
                File.Delete(destination);
            File.Move(source, destination);
        }

        public void Delete(string path)
        {
            if (File.Exists(path))
                File.Delete(path);
        }

        public IEnumerable<string> ListFiles(string directory, string pattern = "*.*")
        {
            if (!Directory.Exists(directory))
                throw new DirectoryNotFoundException($"Directory not found: {directory}");
            return Directory.EnumerateFiles(directory, pattern, SearchOption.TopDirectoryOnly);
        }

        public long GetSize(string path)
        {
            return new FileInfo(path).Length;
        }
    }
}
