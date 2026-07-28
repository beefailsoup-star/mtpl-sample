using System;

namespace MtplSample
{
    public class Report
    {
        public string Title { get; set; }
        public string Header { get; set; }
        public string Body { get; set; }
        public string Footer { get; set; }
        public DateTime GeneratedAt { get; set; } = DateTime.UtcNow;

        public void Display()
        {
            Console.WriteLine($"=== {Title} ===");
            Console.WriteLine(Header);
            Console.WriteLine(Body);
            Console.WriteLine(Footer);
            Console.WriteLine($"Generated: {GeneratedAt}");
        }
    }

    public interface IReportBuilder
    {
        void SetTitle(string title);
        void SetHeader(string header);
        void SetBody(string body);
        void SetFooter(string footer);
        Report Build();
    }

    public class ReportBuilder : IReportBuilder
    {
        private readonly Report _report = new();

        public void SetTitle(string title) => _report.Title = title;
        public void SetHeader(string header) => _report.Header = header;
        public void SetBody(string body) => _report.Body = body;
        public void SetFooter(string footer) => _report.Footer = footer;
        public Report Build() => _report;
    }

    public class ReportDirector
    {
        private readonly IReportBuilder _builder;

        public ReportDirector(IReportBuilder builder)
        {
            _builder = builder;
        }

        public Report BuildMinimalReport(string title, string body)
        {
            _builder.SetTitle(title);
            _builder.SetBody(body);
            _builder.SetHeader("Minimal Header");
            _builder.SetFooter("Minimal Footer");
            return _builder.Build();
        }

        public Report BuildFullReport(string title, string header, string body, string footer)
        {
            _builder.SetTitle(title);
            _builder.SetHeader(header);
            _builder.SetBody(body);
            _builder.SetFooter(footer);
            return _builder.Build();
        }
    }
}
