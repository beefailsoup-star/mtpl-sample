using System;
using System.Net;
using System.Net.Mail;
using System.Threading.Tasks;

namespace MtplSample
{
    public class EmailSender : IDisposable
    {
        private readonly SmtpClient _smtpClient;

        public EmailSender(string host, int port, string username, string password, bool useSsl = true)
        {
            _smtpClient = new SmtpClient(host, port)
            {
                Credentials = new NetworkCredential(username, password),
                EnableSsl = useSsl
            };
        }

        public async Task SendAsync(string to, string subject, string body, bool isHtml = false)
        {
            using var message = new MailMessage("noreply@mtplsample.com", to, subject, body)
            {
                IsBodyHtml = isHtml
            };
            await _smtpClient.SendMailAsync(message);
        }

        public async Task SendBulkAsync(string[] recipients, string subject, string body)
        {
            foreach (var to in recipients)
            {
                await SendAsync(to, subject, body);
            }
        }

        public void Dispose()
        {
            _smtpClient?.Dispose();
        }
    }
}
