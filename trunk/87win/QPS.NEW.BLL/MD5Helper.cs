using System;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;


namespace QPS.NEW.BLL
{
    public class MD5Helper
    {
        public static string Encode(string str)
        {
            byte[] result = Encoding.Default.GetBytes(str);
            MD5 md5 = new MD5CryptoServiceProvider();
            byte[] output = md5.ComputeHash(result);
            string res= BitConverter.ToString(output).Replace("-", "").ToLower();

            return res;
        }
    }
}
