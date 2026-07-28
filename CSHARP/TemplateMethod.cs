using System;

namespace MtplSample
{
    public abstract class DataImporter
    {
        public void Import(string filePath)
        {
            OpenFile(filePath);
            var rawData = ReadData();
            var parsedData = ParseData(rawData);
            var validated = ValidateData(parsedData);
            SaveData(validated);
            CloseFile();
        }

        protected abstract void OpenFile(string filePath);
        protected abstract string ReadData();
        protected abstract object ParseData(string rawData);

        protected virtual object ValidateData(object data)
        {
            LoggerService.Instance.LogInfo("Data validated.");
            return data;
        }

        protected abstract void SaveData(object data);

        protected virtual void CloseFile()
        {
            LoggerService.Instance.LogInfo("File closed.");
        }
    }

    public class CsvDataImporter : DataImporter
    {
        private string _filePath;

        protected override void OpenFile(string filePath)
        {
            _filePath = filePath;
            LoggerService.Instance.LogInfo($"Opening CSV file: {filePath}");
        }

        protected override string ReadData()
        {
            return "name,age\nJohn,30\nJane,25";
        }

        protected override object ParseData(string rawData)
        {
            var lines = rawData.Split('\n');
            LoggerService.Instance.LogInfo($"Parsed {lines.Length - 1} records.");
            return lines;
        }

        protected override void SaveData(object data)
        {
            LoggerService.Instance.LogInfo($"Saved {((string[])data).Length - 1} CSV records to database.");
        }
    }

    public class JsonDataImporter : DataImporter
    {
        protected override void OpenFile(string filePath)
        {
            LoggerService.Instance.LogInfo($"Opening JSON file: {filePath}");
        }

        protected override string ReadData()
        {
            return "[{\"name\":\"John\"},{\"name\":\"Jane\"}]";
        }

        protected override object ParseData(string rawData)
        {
            LoggerService.Instance.LogInfo("Parsed JSON data.");
            return rawData;
        }

        protected override void SaveData(object data)
        {
            LoggerService.Instance.LogInfo("Saved JSON data to database.");
        }
    }
}
