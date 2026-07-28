using System;

namespace MtplSample
{
    public interface ITarget
    {
        string Request();
    }

    public class Adaptee
    {
        public string SpecificRequest()
        {
            return "Specific request from Adaptee";
        }
    }

    public class AdapterWrapper : ITarget
    {
        private readonly Adaptee _adaptee;

        public AdapterWrapper(Adaptee adaptee)
        {
            _adaptee = adaptee;
        }

        public string Request()
        {
            return $"[Adapter] {_adaptee.SpecificRequest()}";
        }
    }

    public interface IXmlService
    {
        string GetXmlData();
    }

    public class JsonService
    {
        public string GetJsonData() => "{\"key\": \"value\"}";
    }

    public class JsonToXmlAdapter : IXmlService
    {
        private readonly JsonService _jsonService;

        public JsonToXmlAdapter(JsonService jsonService)
        {
            _jsonService = jsonService;
        }

        public string GetXmlData()
        {
            var json = _jsonService.GetJsonData();
            return $"<root><key>value</key></root>";
        }
    }
}
