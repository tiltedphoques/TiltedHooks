#include <D3D9Hook.h>
#include <d3d9.h>

#include <FunctionHook.h>
#include <mutex>
#include <intrin.h>

struct IDirect3D9Hook : IDirect3D9
{
    TP_ALLOCATOR

    explicit IDirect3D9Hook(IDirect3D9* pOriginal) noexcept : m_pIDirect3D9(pOriginal) {}
    virtual ~IDirect3D9Hook(void) = default;

    IDirect3D9Hook(IDirect3D9Hook&&) = delete;
    IDirect3D9Hook(const IDirect3D9Hook&) = delete;
    IDirect3D9Hook& operator=(IDirect3D9Hook&&) = delete;
    IDirect3D9Hook& operator=(const IDirect3D9Hook&) = delete;

    HRESULT  __stdcall QueryInterface(REFIID riid, void** ppvObj) override { return m_pIDirect3D9->QueryInterface(riid, ppvObj); }
    ULONG    __stdcall AddRef(void)override { return(m_pIDirect3D9->AddRef()); }
    ULONG    __stdcall Release(void)override;
    HRESULT  __stdcall RegisterSoftwareDevice(void* pInitializeFunction)override { return(m_pIDirect3D9->RegisterSoftwareDevice(pInitializeFunction)); }
    UINT     __stdcall GetAdapterCount(void)override { return(m_pIDirect3D9->GetAdapterCount()); }
    HRESULT  __stdcall GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier)override { return(m_pIDirect3D9->GetAdapterIdentifier(Adapter, Flags, pIdentifier)); }
    UINT     __stdcall GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)override { return(m_pIDirect3D9->GetAdapterModeCount(Adapter, Format)); }
    HRESULT  __stdcall EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)override { return(m_pIDirect3D9->EnumAdapterModes(Adapter, Format, Mode, pMode)); }
    HRESULT  __stdcall GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)override { return(m_pIDirect3D9->GetAdapterDisplayMode(Adapter, pMode)); }
    HRESULT  __stdcall CheckDeviceType(UINT iAdapter, D3DDEVTYPE DevType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)override { return(m_pIDirect3D9->CheckDeviceType(iAdapter, DevType, DisplayFormat, BackBufferFormat, bWindowed)); }
    HRESULT  __stdcall CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)override { return(m_pIDirect3D9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat)); }
    HRESULT  __stdcall CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels) override {return(m_pIDirect3D9->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels));}
    HRESULT  __stdcall CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat) override { return(m_pIDirect3D9->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat));}
    HRESULT  __stdcall CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)override { return(m_pIDirect3D9->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat)); }
    HRESULT  __stdcall GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps) override { return(m_pIDirect3D9->GetDeviceCaps(Adapter, DeviceType, pCaps)); }
    HMONITOR __stdcall GetAdapterMonitor(UINT Adapter) override { return(m_pIDirect3D9->GetAdapterMonitor(Adapter)); }
    HRESULT  __stdcall CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface) override;

private:
    IDirect3D9* m_pIDirect3D9;
};

ULONG __stdcall IDirect3D9Hook::Release(void)
{
    const auto count = m_pIDirect3D9->Release();
    if (!count)
        Delete(this);

    return count;
}

// Reset 16
// Present 17

using TReset = HRESULT(__stdcall*)(IDirect3DDevice9Ex* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
using TPresent = HRESULT(__stdcall*)(IDirect3DDevice9Ex* pDevice, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion);

static TReset RealReset = nullptr;
static TPresent RealPresent = nullptr;

static HRESULT __stdcall HookReset(IDirect3DDevice9Ex* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    TP_EMPTY_HOOK_PLACEHOLDER;

    const auto result = RealReset(pDevice, pPresentationParameters);

    D3D9Hook::Get().OnReset(pDevice);

    return result;
}

static HRESULT __stdcall HookPresent(IDirect3DDevice9Ex* pDevice, RECT* pSourceRect, RECT* pDestRect, HWND hDestWindowOverride, RGNDATA* pDirtyRegion)
{
    TP_EMPTY_HOOK_PLACEHOLDER;

    D3D9Hook::Get().OnPresent(pDevice);

    const auto result = RealPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

    return result;
}

HRESULT __stdcall IDirect3D9Hook::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface)
{
    const auto result = m_pIDirect3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

    const auto pDevice = *ppReturnedDeviceInterface;

    if (RealReset == nullptr)
    {
        RealReset = (TReset)(*(void***)pDevice)[16];
        TP_HOOK_IMMEDIATE(&RealReset, HookReset);
    }

    if (RealPresent == nullptr)
    {
        RealPresent = (TPresent)(*(void***)pDevice)[17];
        TP_HOOK_IMMEDIATE(&RealPresent, HookPresent);
    }

    D3D9Hook::Get().OnCreate(m_pIDirect3D9, pDevice);

    return result;
}

using TDirect3DCreate9 = IDirect3D9*(WINAPI*)(UINT);
static TDirect3DCreate9 RealDirect3DCreate9 = nullptr;

static IDirect3D9* WINAPI HookDirect3DCreate9(UINT SDKVersion)
{
    IDirect3D9* pIDirect3D9 = RealDirect3DCreate9(SDKVersion);
    const auto pD3D9 = New<IDirect3D9Hook>(pIDirect3D9);

    return pD3D9;
}

D3D9Hook::D3D9Hook() noexcept
{
}

void D3D9Hook::Install()
{
    if(RealDirect3DCreate9 == nullptr)
        RealDirect3DCreate9 = reinterpret_cast<TDirect3DCreate9>(TP_HOOK_SYSTEM("d3d9.dll", "Direct3DCreate9", HookDirect3DCreate9));
}

D3D9Hook& D3D9Hook::Get()
{
    static D3D9Hook s_instance;
    return s_instance;
}
