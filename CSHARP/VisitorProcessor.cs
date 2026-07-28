using System;
using System.Collections.Generic;

namespace MtplSample
{
    public interface IVisitor<T>
    {
        void Visit(T element);
    }

    public interface IElement
    {
        void Accept<T>(IVisitor<T> visitor);
    }

    public class DocumentElement : IElement
    {
        public string Text { get; set; }

        public void Accept<T>(IVisitor<T> visitor)
        {
            if (visitor is IVisitor<DocumentElement> docVisitor)
                docVisitor.Visit(this);
        }
    }

    public class ImageElement : IElement
    {
        public string Url { get; set; }

        public void Accept<T>(IVisitor<T> visitor)
        {
            if (visitor is IVisitor<ImageElement> imgVisitor)
                imgVisitor.Visit(this);
        }
    }

    public class HtmlExportVisitor : IVisitor<DocumentElement>, IVisitor<ImageElement>
    {
        public string Output { get; private set; } = "";

        public void Visit(DocumentElement element)
        {
            Output += $"<p>{element.Text}</p>\n";
        }

        public void Visit(ImageElement element)
        {
            Output += $"<img src=\"{element.Url}\" />\n";
        }
    }

    public class VisitorProcessor
    {
        public string Process(IEnumerable<IElement> elements, object visitor)
        {
            foreach (var element in elements)
            {
                if (visitor is IVisitor<DocumentElement> && element is DocumentElement)
                    element.Accept((IVisitor<DocumentElement>)visitor);
                else if (visitor is IVisitor<ImageElement> && element is ImageElement)
                    element.Accept((IVisitor<ImageElement>)visitor);
            }

            if (visitor is HtmlExportVisitor html)
                return html.Output;

            return "";
        }
    }
}
