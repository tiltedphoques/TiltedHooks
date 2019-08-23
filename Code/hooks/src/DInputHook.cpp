#include <DInputHook.h>
#include <dinput.h>

#include <FunctionHook.h>

struct DirectInputDeviceWrapper : IDirectInputDevice8A
{
    TP_ALLOCATOR

    DirectInputDeviceWrapper(IDirectInputDevice8A* aDevice, GUID aGuid) noexcept;

    ULONG _stdcall AddRef(void) override { return m_pRealDevice->AddRef(); }
    ULONG _stdcall Release(void);

    HRESULT _stdcall GetDeviceState(DWORD outDataLen, LPVOID outData);
    HRESULT _stdcall GetDeviceData(DWORD dataSize, LPDIDEVICEOBJECTDATA outData, LPDWORD outDataLen, DWORD flags);
    HRESULT _stdcall SetCooperativeLevel(HWND window, DWORD flags) { return m_pRealDevice->SetCooperativeLevel(window, flags); }
    HRESULT _stdcall QueryInterface(REFIID a, LPVOID* b) { return m_pRealDevice->QueryInterface(a, b); }
    HRESULT _stdcall GetCapabilities(LPDIDEVCAPS a) { return m_pRealDevice->GetCapabilities(a); }
    HRESULT _stdcall EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA a, LPVOID b, DWORD c) { return m_pRealDevice->EnumObjects(a, b, c); }
    HRESULT _stdcall GetProperty(REFGUID a, DIPROPHEADER* b) { return m_pRealDevice->GetProperty(a, b); }
    HRESULT _stdcall SetProperty(REFGUID a, const DIPROPHEADER* b) { return m_pRealDevice->SetProperty(a, b); }
    HRESULT _stdcall Acquire(void);
    HRESULT _stdcall Unacquire(void) { return m_pRealDevice->Unacquire(); }
    HRESULT _stdcall SetDataFormat(const DIDATAFORMAT* a) { return m_pRealDevice->SetDataFormat(a); }
    HRESULT _stdcall SetEventNotification(HANDLE a) { return m_pRealDevice->SetEventNotification(a); }
    HRESULT _stdcall GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA a, DWORD b, DWORD c) { return m_pRealDevice->GetObjectInfo(a, b, c); }
    HRESULT _stdcall GetDeviceInfo(LPDIDEVICEINSTANCEA a) { return m_pRealDevice->GetDeviceInfo(a); }
    HRESULT _stdcall RunControlPanel(HWND a, DWORD b) { return m_pRealDevice->RunControlPanel(a, b); }
    HRESULT _stdcall Initialize(HINSTANCE a, DWORD b, REFGUID c) { return m_pRealDevice->Initialize(a, b, c); }
    HRESULT _stdcall CreateEffect(REFGUID a, LPCDIEFFECT b, LPDIRECTINPUTEFFECT* c, LPUNKNOWN d) { return m_pRealDevice->CreateEffect(a, b, c, d); }
    HRESULT _stdcall EnumEffects(LPDIENUMEFFECTSCALLBACKA a, LPVOID b, DWORD c) { return m_pRealDevice->EnumEffects(a, b, c); }
    HRESULT _stdcall GetEffectInfo(LPDIEFFECTINFOA a, REFGUID b) { return m_pRealDevice->GetEffectInfo(a, b); }
    HRESULT _stdcall GetForceFeedbackState(LPDWORD a) { return m_pRealDevice->GetForceFeedbackState(a); }
    HRESULT _stdcall SendForceFeedbackCommand(DWORD a) { return m_pRealDevice->SendForceFeedbackCommand(a); }
    HRESULT _stdcall EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK a, LPVOID b, DWORD c) { return m_pRealDevice->EnumCreatedEffectObjects(a, b, c); }
    HRESULT _stdcall Escape(LPDIEFFESCAPE a) { return m_pRealDevice->Escape(a); }
    HRESULT _stdcall Poll(void) { return m_pRealDevice->Poll(); }
    HRESULT _stdcall SendDeviceData(DWORD a, LPCDIDEVICEOBJECTDATA b, LPDWORD c, DWORD d) { return m_pRealDevice->SendDeviceData(a, b, c, d); }
    HRESULT _stdcall EnumEffectsInFile(LPCSTR a, LPDIENUMEFFECTSINFILECALLBACK b, LPVOID c, DWORD d) { return m_pRealDevice->EnumEffectsInFile(a, b, c, d); }
    HRESULT _stdcall WriteEffectToFile(LPCSTR a, DWORD b, LPDIFILEEFFECT c, DWORD d) { return m_pRealDevice->WriteEffectToFile(a, b, c, d); }
    HRESULT _stdcall BuildActionMap(LPDIACTIONFORMATA a, LPCSTR b, DWORD c) { return m_pRealDevice->BuildActionMap(a, b, c); }
    HRESULT _stdcall SetActionMap(LPDIACTIONFORMATA a, LPCSTR b, DWORD c) { return m_pRealDevice->SetActionMap(a, b, c); }
    HRESULT _stdcall GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA a) { return m_pRealDevice->GetImageInfo(a); }

    static Set<DirectInputDeviceWrapper*> s_devices;

private:

    IDirectInputDevice8A* m_pRealDevice;

    GUID m_guid;
};

struct DirectInputWrapper : IDirectInput8A
{
    TP_ALLOCATOR

    DirectInputWrapper(IDirectInput8A* aInput) noexcept;

    ULONG _stdcall AddRef(void) override { return m_pDirectInput->AddRef(); }
    ULONG _stdcall Release(void) override;

    HRESULT _stdcall CreateDevice(REFGUID typeGuid, LPDIRECTINPUTDEVICE8A* device, LPUNKNOWN unused) override;
    HRESULT _stdcall QueryInterface(REFIID a, LPVOID* b) override  { return m_pDirectInput->QueryInterface(a, b); }
    HRESULT _stdcall EnumDevices(DWORD a, LPDIENUMDEVICESCALLBACKA b, LPVOID c, DWORD d) override  { return m_pDirectInput->EnumDevices(a, b, c, d); }
    HRESULT _stdcall GetDeviceStatus(REFGUID r) override { return m_pDirectInput->GetDeviceStatus(r); }
    HRESULT _stdcall RunControlPanel(HWND a, DWORD b) override { return m_pDirectInput->RunControlPanel(a, b); }
    HRESULT _stdcall Initialize(HINSTANCE a, DWORD b) override { return m_pDirectInput->Initialize(a, b); }
    HRESULT _stdcall FindDevice(REFGUID a, LPCSTR b, LPGUID c) override { return m_pDirectInput->FindDevice(a, b, c); }
    HRESULT _stdcall EnumDevicesBySemantics(LPCSTR a, LPDIACTIONFORMATA b, LPDIENUMDEVICESBYSEMANTICSCBA c, LPVOID d, DWORD e) override { return m_pDirectInput->EnumDevicesBySemantics(a, b, c, d, e); }
    HRESULT _stdcall ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK a, LPDICONFIGUREDEVICESPARAMSA b, DWORD c, LPVOID d) override { return m_pDirectInput->ConfigureDevices(a, b, c, d); }

private:

    IDirectInput8A* m_pDirectInput;
    DirectInputDeviceWrapper* m_pDevice;
};

DirectInputWrapper::DirectInputWrapper(IDirectInput8A* apDirectInput) noexcept
    : m_pDirectInput(apDirectInput)
    , m_pDevice(nullptr)
{
}

HRESULT _stdcall DirectInputWrapper::CreateDevice(REFGUID typeGuid, LPDIRECTINPUTDEVICE8A* apDevice, LPUNKNOWN unused)
{
    const auto result = m_pDirectInput->CreateDevice(typeGuid, reinterpret_cast<LPDIRECTINPUTDEVICE8A*>(& m_pDevice), unused);

    if (result == DI_OK)
    {
        *apDevice = New<DirectInputDeviceWrapper>(m_pDevice, typeGuid);
    }

    return result;
}

ULONG _stdcall DirectInputWrapper::Release(void)
{
    ULONG count = m_pDirectInput->Release();

    if (!count)
    {
        Delete(this);
    }

    return count;
}

Set<DirectInputDeviceWrapper*> DirectInputDeviceWrapper::s_devices;

DirectInputDeviceWrapper::DirectInputDeviceWrapper(IDirectInputDevice8A* aDevice, GUID aGuid) noexcept
    : m_pRealDevice(aDevice)
    , m_guid(aGuid)
{
    s_devices.insert(this);
}

HRESULT _stdcall DirectInputDeviceWrapper::GetDeviceState(DWORD outDataLen, LPVOID outData)
{
    if (DInputHook::Get().IsEnabled())
    {
        std::memset(outData, 0, outDataLen);
        return 0;
    }

    return m_pRealDevice->GetDeviceState(outDataLen, outData);
}

HRESULT _stdcall DirectInputDeviceWrapper::GetDeviceData(DWORD dataSize, LPDIDEVICEOBJECTDATA outData, LPDWORD outDataLen, DWORD flags)
{
    auto& input = DInputHook::Get();

    const auto result = m_pRealDevice->GetDeviceData(dataSize, outData, outDataLen, flags);

    if (input.IsEnabled())
    {
        *outDataLen = 0;

        return result;
    }
        
    if (m_guid == GUID_SysKeyboard)
    {
        for (DWORD i = 0; i < *outDataLen; ++i)
        {
            if (input.IsToggleKey(outData[i].dwOfs) && outData[i].dwData & 0x80)
            {
                DInputHook::Get().SetEnabled(true);
            }
        }
    }

    return result;
}

ULONG _stdcall DirectInputDeviceWrapper::Release(void)
{
    ULONG count = m_pRealDevice->Release();

    if (count == 0)
    {
        s_devices.erase(this);
        Delete(this);
    }

    return count;
}

HRESULT _stdcall DirectInputDeviceWrapper::Acquire(void)
{
    return m_pRealDevice->Acquire();    
}

using TDirectInput8Create = HRESULT(_stdcall*)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
static TDirectInput8Create RealDirectInput8Create;

static HRESULT _stdcall HookDirectInput8Create(HINSTANCE instance, DWORD version, REFIID iid, LPVOID* out, LPUNKNOWN outer)
{
    IDirectInput8A* pDirectInput = nullptr;

    auto result = RealDirectInput8Create(instance, version, iid, (LPVOID*)& pDirectInput, outer);

    if (result == DI_OK)
    {
        *out = New<DirectInputWrapper>(pDirectInput);
    }

    return result;
}

void DInputHook::Install() noexcept
{
    TP_HOOK_IAT(DirectInput8Create, "dinput8.dll");
}

DInputHook::DInputHook() noexcept
{
    SetToggleKeys({ DIK_RCONTROL });
}

void DInputHook::SetToggleKeys(std::initializer_list<unsigned long> aKeys)
{
    m_toggleKeys.clear();

    for (auto key : aKeys)
    {
        m_toggleKeys.insert(key);
    }
}

bool DInputHook::IsToggleKey(unsigned int aKey) const noexcept
{
    return m_toggleKeys.count(aKey) > 0;
}

void DInputHook::Acquire() const noexcept
{
    for(auto& device : DirectInputDeviceWrapper::s_devices)
    {
        device->Acquire();
    }
}

void DInputHook::Unacquire() const noexcept
{
    for (auto& device : DirectInputDeviceWrapper::s_devices)
    {
        device->Unacquire();
    }
}

DInputHook& DInputHook::Get()
{
    static DInputHook s_instance;
    return s_instance;
}

void DInputHook::Update() const
{
    RAWINPUTDEVICE device[2];

    device[0].usUsagePage = 0x01;
    device[0].usUsage = 0x06;
    device[0].dwFlags = RIDEV_REMOVE;
    device[0].hwndTarget = nullptr;

    device[1].usUsagePage = 0x01;
    device[1].usUsage = 0x02;
    device[1].dwFlags =  RIDEV_REMOVE;
    device[1].hwndTarget = nullptr;

    RegisterRawInputDevices(device, sizeof(device) / sizeof(RAWINPUTDEVICE), sizeof(RAWINPUTDEVICE));

    if (m_enabled)
    {
        for (const auto pDevice : DirectInputDeviceWrapper::s_devices)
        {
            pDevice->Acquire();
        }

        device[0].dwFlags = 0;
        device[1].dwFlags = 0;

        RegisterRawInputDevices(device, sizeof(device) / sizeof(RAWINPUTDEVICE), sizeof(RAWINPUTDEVICE));
    }
    else
    {
        for (const auto pDevice : DirectInputDeviceWrapper::s_devices)
        {
            pDevice->Unacquire();
        }
    }
}
