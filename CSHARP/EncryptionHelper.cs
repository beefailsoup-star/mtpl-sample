using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace MtplSample
{
    public class EncryptionHelper
    {
        private readonly byte[] _key;
        private readonly byte[] _iv;

        public EncryptionHelper(byte[] key, byte[] iv)
        {
            _key = key ?? throw new ArgumentNullException(nameof(key));
            _iv = iv ?? throw new ArgumentNullException(nameof(iv));
        }

        public EncryptionHelper(string base64Key, string base64Iv)
        {
            _key = Convert.FromBase64String(base64Key);
            _iv = Convert.FromBase64String(base64Iv);
        }

        public string Encrypt(string plainText)
        {
            using var aes = Aes.Create();
            aes.Key = _key;
            aes.IV = _iv;

            using var encryptor = aes.CreateEncryptor();
            using var ms = new MemoryStream();
            using var cs = new CryptoStream(ms, encryptor, CryptoStreamMode.Write);
            using var sw = new StreamWriter(cs);
            sw.Write(plainText);
            sw.Flush();
            cs.FlushFinalBlock();
            return Convert.ToBase64String(ms.ToArray());
        }

        public string Decrypt(string cipherText)
        {
            using var aes = Aes.Create();
            aes.Key = _key;
            aes.IV = _iv;

            using var decryptor = aes.CreateDecryptor();
            using var ms = new MemoryStream(Convert.FromBase64String(cipherText));
            using var cs = new CryptoStream(ms, decryptor, CryptoStreamMode.Read);
            using var sr = new StreamReader(cs);
            return sr.ReadToEnd();
        }

        public static (string Key, string Iv) GenerateKey()
        {
            using var aes = Aes.Create();
            aes.GenerateKey();
            aes.GenerateIV();
            return (Convert.ToBase64String(aes.Key), Convert.ToBase64String(aes.IV));
        }
    }
}
