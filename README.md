# UdrakoLoader
![passing](https://img.shields.io/badge/build-passing-brightgreen) 


<img align="left" width="300" height="110" src="https://i.ibb.co/jrrCpd6/Udraco-Loader.png">

## Introduction
Udrakoloader is a mod, Currently Compatible With SAMP and HALO [Possibly With many more games]. 
Provides the ability to load scripts (DLL) developed in .Net into the game.

Based on [ScriptHookvDotNet](https://github.com/crosire/scripthookvdotnet) and [SharpNeedle](https://github.com/ChadSki/SharpNeedle) . Basically consists of CLR Hosting, to run the .Net plugins.

-- I don't take credit for this for the following reasons:

- Most of the code is from the SharpNeedle project, Modified with parts of ScriptHookvDotNet for more compatibility.

## How to Install a Plugin?​
- Extract the Plugin (.dll) into the folder "UdrakoLoader", in the root directory of the game.

## Attention:
- The .net DLLs must be compiled under the .Net Framework 4.0.
- The name of the Plugin DLL must be the same as the Root Namespace.

Some examples : [Compile DLL and put inside the "Udrakoloader" folder]

For C# Plugins, you must provide the correct Namespace directory.

![SampleImg](https://i.ibb.co/YLJb3PN/exampletest.png)

In this case Replace ["namespace ExampleProject.Udrakoloader"] with ["namespace <Your Root Namespace Project>.Udrakoloader"]
 
 
 - UdrakoLoader C# Plugin Example:
 ```c#
// Plugin.cs
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
```

 - UdrakoLoader VB Plugin Example:
 
 ```vb
'Plugin.vb
Imports System
Imports System.Collections.Generic
Imports System.Diagnostics
Imports System.Linq
Imports System.Text
Imports System.Windows.Forms
Imports System.Reflection
Imports System.Runtime.CompilerServices
Imports System.Runtime.InteropServices
Imports System.Security

Namespace Udrakoloader

    Public Class Plugin

        Public Shared Function EntryPoint(ByVal pwzArgument As String) As Integer
            Dim processName As String = Process.GetCurrentProcess().ProcessName
            MessageBox.Show("vb Example | The current process is " & processName)
            Return 0
        End Function

    End Class

End Namespace
```

 ## Contributors
- Destroyer : Mod SharpNeedle Source .  / Discord : Destroyer#8328
- ChadSki / Usman Sabir : SharpNeedle Source .
- crosire : ScriptHookvDotNet Examples.

# Download

Download Pre Releases made for games: [Udrako Loader Downloads](https://github.com/DestroyerDarkNess/Udrakoloader/releases/tag/1.0) 




