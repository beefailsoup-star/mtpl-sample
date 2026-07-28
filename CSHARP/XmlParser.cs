using System;
using System.Collections.Generic;
using System.Xml;
using System.Xml.Linq;

namespace MtplSample
{
    public class XmlParser
    {
        public XDocument Load(string xml)
        {
            return XDocument.Parse(xml);
        }

        public XDocument LoadFile(string path)
        {
            return XDocument.Load(path);
        }

        public Dictionary<string, object> FlattenToDictionary(string xml)
        {
            var doc = XDocument.Parse(xml);
            var result = new Dictionary<string, object>();
            TraverseElement(doc.Root, "", result);
            return result;
        }

        private void TraverseElement(XElement element, string prefix, Dictionary<string, object> result)
        {
            var key = string.IsNullOrEmpty(prefix) ? element.Name.LocalName : $"{prefix}:{element.Name.LocalName}";

            if (element.HasElements)
            {
                foreach (var child in element.Elements())
                {
                    TraverseElement(child, key, result);
                }
            }
            else
            {
                result[key] = element.Value;
            }

            foreach (var attr in element.Attributes())
            {
                result[$"{key}@{attr.Name.LocalName}"] = attr.Value;
            }
        }

        public string QueryValue(string xml, string xpath)
        {
            var doc = new XmlDocument();
            doc.LoadXml(xml);
            var node = doc.SelectSingleNode(xpath);
            return node?.InnerText;
        }
    }
}
