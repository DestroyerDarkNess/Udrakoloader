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
