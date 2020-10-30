#include "stdafx.h"
#include <metahost.h>
#include <string>
#pragma comment(lib, "mscoree.lib")

#include "Bootstrapper.h"

using namespace std;

DllExport void LoadManagedProject(const wchar_t * managedDllLocation)
{
    HRESULT hr;

	wstring test(&managedDllLocation[0]); //convert to wstring
	string filename(test.begin(), test.end()); //and convert to string.

	// Remove directory if present.
	// Do this before extension removal incase directory has a period character.
	const size_t last_slash_idx = filename.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		filename.erase(0, last_slash_idx + 1);
	}

	// Remove extension if present.
	const size_t period_idx = filename.rfind('.');
	if (std::string::npos != period_idx)
	{
		filename.erase(period_idx);
	}

	string RootCompleteNamespace = filename  + std::string(".Udrakoloader.Plugin");

	std::wstring widestr = std::wstring(RootCompleteNamespace.begin(), RootCompleteNamespace.end());

	//MessageBox(NULL, widestr.c_str(), L"Archivo : ", MB_ICONEXCLAMATION | MB_OK);
	string LogInfo = std::string("Loading: ") + RootCompleteNamespace + std::string(" | Welcome Message : ");
	DWORD resultado;
    // Secure a handle to the CLR v4.0
    ICLRRuntimeHost* pClr = StartCLR(L"v4.0.30319");
    if (pClr != NULL)
    {
		
		DWORD result;
        hr = pClr->ExecuteInDefaultAppDomain(
            managedDllLocation,
			widestr.c_str(), //L"<RootNameSpace>.Udrakoloader.Plugin"
            L"EntryPoint",
            L"Argument",
            &result);
		hr = pClr->Start();
		resultado = result;
    }

}

ICLRRuntimeHost* StartCLR(LPCWSTR dotNetVersion)
{
    HRESULT hr; 

    ICLRMetaHost* pClrMetaHost = NULL;
    ICLRRuntimeInfo* pClrRuntimeInfo = NULL;
    ICLRRuntimeHost* pClrRuntimeHost = NULL;

    // Get the CLRMetaHost that tells us about .NET on this machine
    hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pClrMetaHost);
    if (hr == S_OK)
    {
        // Get the runtime information for the particular version of .NET
        hr = pClrMetaHost->GetRuntime(dotNetVersion, IID_PPV_ARGS(&pClrRuntimeInfo));
        if (hr == S_OK)
        {
            // Check if the specified runtime can be loaded into the process. This
            // method will take into account other runtimes that may already be
            // loaded into the process and set pbLoadable to TRUE if this runtime can
            // be loaded in an in-process side-by-side fashion.
            BOOL fLoadable;
            hr = pClrRuntimeInfo->IsLoadable(&fLoadable);
            if ((hr == S_OK) && fLoadable)
            {
                // Load the CLR into the current process and return a runtime interface
                // pointer.
                hr = pClrRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,
                    IID_PPV_ARGS(&pClrRuntimeHost));
                if (hr == S_OK)
                {
                    // Start it. This is okay to call even if the CLR is already running
                    pClrRuntimeHost->Start();
                    return pClrRuntimeHost;                    
                }
            }
        }
    }

    // Cleanup if failed
    if (pClrRuntimeHost)
    {
        pClrRuntimeHost->Release();
        pClrRuntimeHost = NULL;
    }
    if (pClrRuntimeInfo)
    {
        pClrRuntimeInfo->Release();
        pClrRuntimeInfo = NULL;
    }
    if (pClrMetaHost)
    {
        pClrMetaHost->Release();
        pClrMetaHost = NULL;
    }

    return NULL;
}
