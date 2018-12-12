// Outl64FuzzLib.cpp: ���������� �������� DLL.

//
// ����������. ���������� COM+ 1.0:
//      ��� ��������� ����������� �� �������� ��������� Microsoft Transaction Explorer.
//      ����������� �� ����������� �� ���������. 

#include "stdafx.h"
#include "resource.h"
#include "Outl64FuzzLib_i.h"
#include "dllmain.h"
#include "compreg.h"


using namespace ATL;

// ������������, ����� ����������, ����� �� ��������� DLL ���������� OLE.
STDAPI DllCanUnloadNow(void)
{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _AtlModule.GetLockCount()==0) ? S_OK : S_FALSE;
	}

// ���������� ������� ������ ��� �������� ������� ���������� ����.
_Check_return_
STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
		return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - ��������� ������ � ��������� ������.
STDAPI DllRegisterServer(void)
{
	// ������������ ������, ���������� ����� � ��� ���������� � ���������� �����
	HRESULT hr = _AtlModule.DllRegisterServer();
		return hr;
}

// DllUnregisterServer - ������� ������ �� ���������� �������.
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
		return hr;
}

// DllInstall - ��������� � ������� ������ ���������� ������� ��� ����������� ������������ � ����������.
STDAPI DllInstall(BOOL bInstall, _In_opt_  LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	static const wchar_t szUserSwitch[] = L"user";

	if (pszCmdLine != NULL)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			ATL::AtlSetPerUserRegistration(true);
		}
	}

	if (bInstall)
	{	
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}

	return hr;
}


