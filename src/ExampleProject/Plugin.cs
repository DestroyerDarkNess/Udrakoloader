﻿// Plugin.cs

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ExampleProject.Udrakoloader
{
    public class Plugin
    {
        public static int EntryPoint(string pwzArgument)
        {
            string processName = Process.GetCurrentProcess().ProcessName;
            MessageBox.Show("C# Example | The current process is " + processName);
            return 0;
        }
    }
}
