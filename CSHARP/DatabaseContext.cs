using System;
using System.Data;
using System.Data.Common;

namespace MtplSample
{
    public abstract class DatabaseContext : IDisposable
    {
        private readonly string _connectionString;
        private DbConnection _connection;
        private DbTransaction _transaction;

        protected DatabaseContext(string connectionString)
        {
            _connectionString = connectionString ?? throw new ArgumentNullException(nameof(connectionString));
        }

        protected abstract DbConnection CreateConnection(string connectionString);

        public DbConnection Connection
        {
            get
            {
                if (_connection == null)
                {
                    _connection = CreateConnection(_connectionString);
                    _connection.Open();
                }
                return _connection;
            }
        }

        public DbTransaction BeginTransaction()
        {
            if (_transaction != null)
                throw new InvalidOperationException("Transaction already started.");

            _transaction = Connection.BeginTransaction();
            return _transaction;
        }

        public void Commit()
        {
            _transaction?.Commit();
            _transaction = null;
        }

        public void Rollback()
        {
            _transaction?.Rollback();
            _transaction = null;
        }

        public void Dispose()
        {
            _transaction?.Dispose();
            _connection?.Close();
            _connection?.Dispose();
        }
    }
}
