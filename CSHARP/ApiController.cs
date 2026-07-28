using System;
using System.Net;
using System.Text.Json;
using System.Threading.Tasks;

namespace MtplSample
{
    public abstract class ApiController
    {
        protected async Task<IResponse> Ok<T>(T data)
        {
            return await Task.FromResult(new JsonResponse<T>(200, data));
        }

        protected async Task<IResponse> Created<T>(T data)
        {
            return await Task.FromResult(new JsonResponse<T>(201, data));
        }

        protected async Task<IResponse> NoContent()
        {
            return await Task.FromResult(new JsonResponse<object>(204, null));
        }

        protected async Task<IResponse> BadRequest(string message)
        {
            return await Task.FromResult(new ErrorResponse(400, message));
        }

        protected async Task<IResponse> NotFound(string message = "Resource not found")
        {
            return await Task.FromResult(new ErrorResponse(404, message));
        }

        protected async Task<IResponse> ServerError(string message = "Internal server error")
        {
            return await Task.FromResult(new ErrorResponse(500, message));
        }
    }

    public interface IResponse
    {
        int StatusCode { get; }
        string ToJson();
    }

    public class JsonResponse<T> : IResponse
    {
        public int StatusCode { get; }
        public T Data { get; }

        public JsonResponse(int statusCode, T data)
        {
            StatusCode = statusCode;
            Data = data;
        }

        public string ToJson() => JsonSerializer.Serialize(new { status = StatusCode, data = Data });
    }

    public class ErrorResponse : IResponse
    {
        public int StatusCode { get; }
        public string Message { get; }

        public ErrorResponse(int statusCode, string message)
        {
            StatusCode = statusCode;
            Message = message;
        }

        public string ToJson() => JsonSerializer.Serialize(new { status = StatusCode, error = Message });
    }
}
