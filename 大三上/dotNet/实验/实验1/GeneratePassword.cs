using System;
using System.Security.Cryptography;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;

class Program
{
    [DllImport("user32.dll")]
    public static extern bool OpenClipboard(IntPtr hWndNewOwner);

    [DllImport("user32.dll")]
    public static extern bool CloseClipboard();

    [DllImport("user32.dll")]
    public static extern bool SetClipboardData(uint uFormat, IntPtr data);

    [STAThread]
    static void Main(string[] args)
    {
        while(true){
            Console.WriteLine("请选择操作：");
            Console.WriteLine("1. 生成口令");
            Console.WriteLine("2. DES加密");
            Console.WriteLine("3. DES解密");
            Console.WriteLine("4. 退出");
            Console.Write("请输入操作序号：");
            if (int.TryParse(Console.ReadLine(), out int operation))
            {
                switch (operation)
                {
                    case 1:
                        GeneratePassword();
                        break;
                    case 2:
                        DESEncrypt();
                        break;
                    case 3:
                        DESDecrypt();
                        break;
                    case 4:
                        return;
                    default:
                        Console.WriteLine("无效的操作序号。");
                        break;
                }
            }
            else
            {
                Console.WriteLine("无效的操作序号。");
            }
        }

    }
    static void GeneratePassword()
    {
        Console.Write("请输入口令长度（8到16位）：");
        if (int.TryParse(Console.ReadLine(), out int passwordLength) && passwordLength >= 8 && passwordLength <= 16)
        {
            string allowedChars = "abcdefghijkmnpqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ23456789!@#$%^&*()-_+=<>?";
            //去除l L 0 O * .
            string excludeChars = "iIlL0O*.";
            // 从允许的字符中去除不容易区分的字符
            foreach (char c in excludeChars)
            {
                allowedChars = allowedChars.Replace(c.ToString(), "");
            }
            //验证是否包含大写、小写、数字、特殊字符之间的三种
            string password = "";
            bool hasUpper = false;
            bool hasLower = false;
            bool hasNumber = false;
            bool hasSpecial = false;
            while (!hasUpper || !hasLower || !hasNumber || !hasSpecial)
            {
                hasUpper = false;
                hasLower = false;
                hasNumber = false;
                hasSpecial = false;
                password = Generate(allowedChars, passwordLength);
                foreach (char c in password)
                {
                    if (char.IsUpper(c))
                    {
                        hasUpper = true;
                    }
                    else if (char.IsLower(c))
                    {
                        hasLower = true;
                    }
                    else if (char.IsNumber(c))
                    {
                        hasNumber = true;
                    }
                    else
                    {
                        hasSpecial = true;
                    }
                }
            }
            Console.WriteLine($"生成口令为：{password}");

            // 将生成的口令复制到剪贴板
            SetClipboardText(password);

            Console.WriteLine("生成的口令已复制到剪贴板。");
        }
        else
        {
            Console.WriteLine("口令长度必须在8到16之间。");
        }
    }

    static string Generate(string allowedChars, int length)
    {
        using (var rng = new RNGCryptoServiceProvider())
        {
            byte[] randomBytes = new byte[length];
            rng.GetBytes(randomBytes); // 生成随机数

            char[] chars = new char[length];
            int allowedCharCount = allowedChars.Length;

            for (int i = 0; i < length; i++)
            {
                chars[i] = allowedChars[randomBytes[i] % allowedCharCount]; // 取模，防止越界
            }

            return new string(chars);
        }
    }

    static void SetClipboardText(string text)
    {
        OpenClipboard(IntPtr.Zero);
        var ptr = Marshal.StringToHGlobalUni(text);
        SetClipboardData(13, ptr); // 13 表示CF_UNICODETEXT
        CloseClipboard();
        Marshal.FreeHGlobal(ptr);
    }

    static void DESEncrypt()
    {
        Console.Write("请输入要加密的字符串：");
        string input = Console.ReadLine();
        //生成密钥
        string key = Generate("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 8);
        Console.WriteLine($"生成的密钥为：{key}");
        string result = Encrypt(input, key);
        Console.WriteLine($"加密结果：{result}");
        //把密钥和加密结果复制到剪贴板
        SetClipboardText($"密钥：{key}\r\n加密结果：{Encrypt(input, key)}");
        Console.WriteLine("密钥和加密结果已复制到剪贴板。");
        //询问是否保存密钥
        Console.Write("是否保存密钥？（y/n）：");
        string readop = Console.ReadLine();
        if (readop.ToLower() == "y" || readop.ToLower() == "yes")
        {
            Console.Write("请输入保存路径，默认保存到桌面");
            string path = Console.ReadLine();
            //判断路径是否存在
            if (string.IsNullOrWhiteSpace(path)||!Directory.Exists(Path.GetDirectoryName(path)))
            {
                //修改到桌面
                path = Environment.GetFolderPath(Environment.SpecialFolder.Desktop) + "\\key.txt";
            }
            File.WriteAllText(path, key);
            Console.WriteLine("密钥已保存。");
        }
    }
    static string Encrypt(string input, string key)
    {
        byte[] inputBytes = Encoding.UTF8.GetBytes(input);
        byte[] keyBytes = Encoding.UTF8.GetBytes(key);
        using (var des = new DESCryptoServiceProvider())
        {
            des.Key = keyBytes;
            des.IV = keyBytes;
            des.Mode = CipherMode.ECB;
            des.Padding = PaddingMode.PKCS7;
            using (var ms = new System.IO.MemoryStream())
            {
                using (var cs = new CryptoStream(ms, des.CreateEncryptor(), CryptoStreamMode.Write))
                {
                    cs.Write(inputBytes, 0, inputBytes.Length);
                    cs.FlushFinalBlock();
                    return Convert.ToBase64String(ms.ToArray());
                }
            }
        }
    }
    static void DESDecrypt()
    {
        Console.Write("请输入要解密的字符串：");
        string input = Console.ReadLine();
        Console.Write("请输入密钥：");
        string key = Console.ReadLine();
        Console.WriteLine($"解密结果：{Decrypt(input, key)}");
        //把解密结果复制到剪贴板
        SetClipboardText($"解密结果：{Decrypt(input, key)}");
        Console.WriteLine("解密结果已复制到剪贴板。");
    }
    static string Decrypt(string input, string key)
    {
        byte[] inputBytes = Convert.FromBase64String(input);
        byte[] keyBytes = Encoding.UTF8.GetBytes(key);
        using (var des = new DESCryptoServiceProvider())
        {
            des.Key = keyBytes;
            des.IV = keyBytes;
            des.Mode = CipherMode.ECB;
            des.Padding = PaddingMode.PKCS7;
            using (var ms = new System.IO.MemoryStream())
            {
                using (var cs = new CryptoStream(ms, des.CreateDecryptor(), CryptoStreamMode.Write))
                {
                    cs.Write(inputBytes, 0, inputBytes.Length);
                    cs.FlushFinalBlock();
                    return Encoding.UTF8.GetString(ms.ToArray());
                }
            }
        }
    }


}
