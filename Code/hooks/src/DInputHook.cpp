#include <DInputHook.hpp>

#define CINTERFACE

#include <dinput.h>

#include <FunctionHook.hpp>

namespace TiltedPhoques
{
    using TIDirectInputA_CreateDevice = HRESULT(_stdcall*)(IDirectInput8A* pDirectInput, REFGUID typeGuid, LPDIRECTINPUTDEVICE8A* apDevice, LPUNKNOWN unused);
    using TIDirectInputDevice8A_GetDeviceState =  HRESULT(_stdcall*)(IDirectInputDeviceA* apDevice, DWORD outDataLen, LPVOID outData);
    using TIDirectInputDevice8A_GetDeviceData =  HRESULT(_stdcall*)(IDirectInputDeviceA* apDevice, DWORD dataSize, LPDIDEVICEOBJECTDATA outData, LPDWORD outDataLen, DWORD flags);
    using TIDirectInputDevice8A_Release =  ULONG(_stdcall*)(IDirectInputDeviceA* apDevice);
    using TDirectInput8Create = HRESULT(_stdcall*)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);

    static TIDirectInputA_CreateDevice RealIDirectInputA_CreateDevice = nullptr;
    static TIDirectInputDevice8A_GetDeviceState RealIDirectInputDevice8A_GetDeviceState = nullptr;
    static TIDirectInputDevice8A_GetDeviceData RealIDirectInputDevice8A_GetDeviceData = nullptr;
    static TIDirectInputDevice8A_Release RealIDirectInputDevice8A_Release = nullptr;
    static TDirectInput8Create RealDirectInput8Create = nullptr;

    static Set<LPDIRECTINPUTDEVICE8A> s_devices;

    HRESULT _stdcall HookIDirectInputDeviceA_GetDeviceState(IDirectInputDeviceA* apDevice, DWORD outDataLen, LPVOID outData)
    {
        if (DInputHook::Get().IsEnabled())
        {
            std::memset(outData, 0, outDataLen);
            return 0;
        }

        return IDirectInputDevice_GetDeviceState(apDevice, outDataLen, outData);
    }

    HRESULT _stdcall HookIDirectInputDeviceA_GetDeviceData(IDirectInputDeviceA* apDevice, DWORD dataSize, LPDIDEVICEOBJECTDATA outData, LPDWORD outDataLen, DWORD flags)
    {
        auto& input = DInputHook::Get();

        const auto result = RealIDirectInputDevice8A_GetDeviceData(apDevice, dataSize, outData, outDataLen, flags);

        DIDEVICEINSTANCEA instanceInfo;
        instanceInfo.dwSize = sizeof(instanceInfo);
        if (IDirectInputDevice_GetDeviceInfo(apDevice, &instanceInfo) != DI_OK)
        {
            return result;
        }

        if (input.IsEnabled())
        {
            *outDataLen = 0;

            return result;
        }

        if (instanceInfo.guidInstance == GUID_SysKeyboard)
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

    ULONG _stdcall HookIDirectInputDeviceA_Release(IDirectInputDeviceA* apDevice)
    {
        const auto result = RealIDirectInputDevice8A_Release(apDevice);
        if (result == 0)
        {
            s_devices.erase((LPDIRECTINPUTDEVICE8A)apDevice);
        }
        
        return result;
    }

    HRESULT _stdcall HookIDirectInputA_CreateDevice(IDirectInput8A* pDirectInput, REFGUID typeGuid, LPDIRECTINPUTDEVICE8A* apDevice, LPUNKNOWN unused)
    {
        const auto result = RealIDirectInputA_CreateDevice(pDirectInput, typeGuid, apDevice, unused);

        if (result == DI_OK)
        {
            s_devices.insert(*apDevice);

            if (RealIDirectInputDevice8A_GetDeviceState == nullptr)
            {
                RealIDirectInputDevice8A_GetDeviceState = reinterpret_cast<TIDirectInputDevice8A_GetDeviceState>((*apDevice)->lpVtbl->GetDeviceState);
                TP_HOOK_IMMEDIATE(&RealIDirectInputDevice8A_GetDeviceState, HookIDirectInputDeviceA_GetDeviceState);
            }

            if (RealIDirectInputDevice8A_GetDeviceData == nullptr)
            {
                RealIDirectInputDevice8A_GetDeviceData = reinterpret_cast<TIDirectInputDevice8A_GetDeviceData>((*apDevice)->lpVtbl->GetDeviceData);
                TP_HOOK_IMMEDIATE(&RealIDirectInputDevice8A_GetDeviceData, HookIDirectInputDeviceA_GetDeviceData);
            }
            
            if (RealIDirectInputDevice8A_Release == nullptr)
            {
                RealIDirectInputDevice8A_Release = reinterpret_cast<TIDirectInputDevice8A_Release>((*apDevice)->lpVtbl->Release);
                TP_HOOK_IMMEDIATE(&RealIDirectInputDevice8A_Release, HookIDirectInputDeviceA_Release);
            }
        }

        return result;
    }

    static HRESULT _stdcall HookDirectInput8Create(HINSTANCE instance, DWORD version, REFIID iid, LPVOID* out, LPUNKNOWN outer)
    {
        IDirectInput8A* pDirectInput = nullptr;

        const auto result = RealDirectInput8Create(instance, version, iid, reinterpret_cast<LPVOID*>(&pDirectInput), outer);

        *out = static_cast<LPVOID>(pDirectInput);

        if (result == DI_OK && RealIDirectInputA_CreateDevice == nullptr)
        {
            RealIDirectInputA_CreateDevice = pDirectInput->lpVtbl->CreateDevice;
            TP_HOOK_IMMEDIATE(&RealIDirectInputA_CreateDevice, HookIDirectInputA_CreateDevice);
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

    void DInputHook::SetToggleKeys(std::initializer_list<unsigned long> aKeys) noexcept
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
        for (auto& device : s_devices)
        {
            IDirectInputDevice_Acquire(device);
        }
    }

    void DInputHook::Unacquire() const noexcept
    {
        for (auto& device : s_devices)
        {
            IDirectInputDevice_Unacquire(device);
        }
    }

    DInputHook& DInputHook::Get() noexcept
    {
        static DInputHook s_instance;
        return s_instance;
    }

    void DInputHook::Update() const noexcept
    {
        RAWINPUTDEVICE device[2];

        device[0].usUsagePage = 0x01;
        device[0].usUsage = 0x06;
        device[0].dwFlags = RIDEV_REMOVE;
        device[0].hwndTarget = nullptr;

        device[1].usUsagePage = 0x01;
        device[1].usUsage = 0x02;
        device[1].dwFlags = RIDEV_REMOVE;
        device[1].hwndTarget = nullptr;

        RegisterRawInputDevices(device, sizeof(device) / sizeof(RAWINPUTDEVICE), sizeof(RAWINPUTDEVICE));

        if (m_enabled)
        {
            Acquire();

            device[0].dwFlags = 0;
            device[1].dwFlags = 0;

            RegisterRawInputDevices(device, sizeof(device) / sizeof(RAWINPUTDEVICE), sizeof(RAWINPUTDEVICE));
        }
        else
        {
            Unacquire();
        }
    }
}
