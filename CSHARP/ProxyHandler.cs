using System;

namespace MtplSample
{
    public interface IDataService
    {
        string GetData(Guid id);
    }

    public class RealDataService : IDataService
    {
        public string GetData(Guid id)
        {
            return $"Real data for {id}";
        }
    }

    public class ProxyHandler : IDataService
    {
        private readonly RealDataService _realService;
        private readonly string _allowedRole;

        public ProxyHandler(RealDataService realService, string allowedRole)
        {
            _realService = realService;
            _allowedRole = allowedRole;
        }

        public string GetData(Guid id)
        {
            if (!CheckAccess())
                throw new UnauthorizedAccessException("Access denied.");

            LogAccess(id);
            return _realService.GetData(id);
        }

        private bool CheckAccess()
        {
            return !string.IsNullOrEmpty(_allowedRole);
        }

        private void LogAccess(Guid id)
        {
            LoggerService.Instance.LogInfo($"Proxy: Data accessed for ID {id} by role {_allowedRole}");
        }
    }

    public class LazyProxy : IDataService
    {
        private RealDataService _realService;

        public string GetData(Guid id)
        {
            _realService ??= new RealDataService();
            return _realService.GetData(id);
        }
    }
}
