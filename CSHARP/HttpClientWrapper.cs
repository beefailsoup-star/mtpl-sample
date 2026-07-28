using System;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace MtplSample
{
    public class HttpClientWrapper : IDisposable
    {
        private readonly HttpClient _client;

        public HttpClientWrapper(string baseUrl = null, TimeSpan? timeout = null)
        {
            _client = new HttpClient();
            if (!string.IsNullOrEmpty(baseUrl))
                _client.BaseAddress = new Uri(baseUrl);
            if (timeout.HasValue)
                _client.Timeout = timeout.Value;
            _client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
        }

        public void SetBearerToken(string token)
        {
            _client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", token);
        }

        public void AddHeader(string name, string value)
        {
            _client.DefaultRequestHeaders.Add(name, value);
        }

        public async Task<T> GetAsync<T>(string endpoint)
        {
            var response = await _client.GetAsync(endpoint);
            response.EnsureSuccessStatusCode();
            var json = await response.Content.ReadAsStringAsync();
            return JsonSerializer.Deserialize<T>(json);
        }

        public async Task<TResponse> PostAsync<TRequest, TResponse>(string endpoint, TRequest body)
        {
            var json = JsonSerializer.Serialize(body);
            var content = new StringContent(json, Encoding.UTF8, "application/json");
            var response = await _client.PostAsync(endpoint, content);
            response.EnsureSuccessStatusCode();
            var responseJson = await response.Content.ReadAsStringAsync();
            return JsonSerializer.Deserialize<TResponse>(responseJson);
        }

        public async Task<TResponse> PutAsync<TRequest, TResponse>(string endpoint, TRequest body)
        {
            var json = JsonSerializer.Serialize(body);
            var content = new StringContent(json, Encoding.UTF8, "application/json");
            var response = await _client.PutAsync(endpoint, content);
            response.EnsureSuccessStatusCode();
            var responseJson = await response.Content.ReadAsStringAsync();
            return JsonSerializer.Deserialize<TResponse>(responseJson);
        }

        public async Task DeleteAsync(string endpoint)
        {
            var response = await _client.DeleteAsync(endpoint);
            response.EnsureSuccessStatusCode();
        }

        public void Dispose()
        {
            _client?.Dispose();
        }
    }
}
