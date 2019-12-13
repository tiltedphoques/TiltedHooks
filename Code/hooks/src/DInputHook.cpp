#include <DInputHook.hpp>

#define CINTERFACE

#include <dinput.h>

#include <FunctionHook.hpp>
#include <iostream>

namespace TiltedPhoques
{
    struct StubIDirectInputDevice8A
    {
        StubIDirectInputDevice8A(IDirectInputDevice8A* apDevice) : m_pDevice(apDevice) {}

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppvObj) PURE { return IDirectInputDevice8_QueryInterface(m_pDevice, riid, ppvObj); }
        virtual ULONG STDMETHODCALLTYPE AddRef() PURE { return IDirectInputDevice8_AddRef(m_pDevice); }
        virtual ULONG STDMETHODCALLTYPE Release() PURE;

        /*** IDirectInputDevice8A methods ***/
        virtual HRESULT STDMETHODCALLTYPE GetCapabilities(LPDIDEVCAPS a) PURE { return IDirectInputDevice8_GetCapabilities(m_pDevice, a); }
        virtual HRESULT STDMETHODCALLTYPE EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA a, LPVOID b, DWORD c) PURE { return IDirectInputDevice8_EnumObjects(m_pDevice, a, b, c); }
        virtual HRESULT STDMETHODCALLTYPE GetProperty(REFGUID a, LPDIPROPHEADER b) PURE { return IDirectInputDevice8_GetProperty(m_pDevice, a, b); }
        virtual HRESULT STDMETHODCALLTYPE SetProperty(REFGUID a, LPCDIPROPHEADER b) PURE { return IDirectInputDevice8_SetProperty(m_pDevice, a, b); }
        virtual HRESULT STDMETHODCALLTYPE Acquire() PURE { return IDirectInputDevice8_Acquire(m_pDevice); }
        virtual HRESULT STDMETHODCALLTYPE Unacquire() PURE { return IDirectInputDevice8_Unacquire(m_pDevice); }
        virtual HRESULT STDMETHODCALLTYPE GetDeviceState(DWORD a, LPVOID b) PURE;
        virtual HRESULT STDMETHODCALLTYPE GetDeviceData(DWORD a, LPDIDEVICEOBJECTDATA b, LPDWORD c, DWORD d) PURE;
        virtual HRESULT STDMETHODCALLTYPE SetDataFormat(LPCDIDATAFORMAT a) PURE { return IDirectInputDevice8_SetDataFormat(m_pDevice, a); }
        virtual HRESULT STDMETHODCALLTYPE SetEventNotification(HANDLE a) PURE { return IDirectInputDevice8_SetEventNotification(m_pDevice, a); }
        virtual HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND a, DWORD b) PURE { return IDirectInputDevice8_SetCooperativeLevel(m_pDevice, a, b); }
        virtual HRESULT STDMETHODCALLTYPE GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA a, DWORD b, DWORD c) PURE { return IDirectInputDevice8_GetObjectInfo(m_pDevice, a, b, c); }
        virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo(LPDIDEVICEINSTANCEA a) PURE { return IDirectInputDevice8_GetDeviceInfo(m_pDevice, a); }
        virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND a, DWORD b) PURE { return IDirectInputDevice8_RunControlPanel(m_pDevice, a, b); }
        virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE a, DWORD b, REFGUID c) PURE { return IDirectInputDevice8_Initialize(m_pDevice, a, b, c); }
        virtual HRESULT STDMETHODCALLTYPE CreateEffect(REFGUID a, LPCDIEFFECT b, LPDIRECTINPUTEFFECT* c, LPUNKNOWN d) PURE { return IDirectInputDevice8_CreateEffect(m_pDevice, a, b, c, d); }
        virtual HRESULT STDMETHODCALLTYPE EnumEffects(LPDIENUMEFFECTSCALLBACKA a, LPVOID b, DWORD c) PURE { return IDirectInputDevice8_EnumEffects(m_pDevice, a, b, c); }
        virtual HRESULT STDMETHODCALLTYPE GetEffectInfo(LPDIEFFECTINFOA a, REFGUID b) PURE { return IDirectInputDevice8_GetEffectInfo(m_pDevice, a, b); }
        virtual HRESULT STDMETHODCALLTYPE GetForceFeedbackState(LPDWORD a) PURE { return IDirectInputDevice8_GetForceFeedbackState(m_pDevice, a); }
        virtual HRESULT STDMETHODCALLTYPE SendForceFeedbackCommand(DWORD a) PURE { return IDirectInputDevice8_SendForceFeedbackCommand(m_pDevice, a); }
        virtual HRESULT STDMETHODCALLTYPE EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK a, LPVOID b, DWORD c) PURE { return IDirectInputDevice8_EnumCreatedEffectObjects(m_pDevice, a, b, c); }
        virtual HRESULT STDMETHODCALLTYPE Escape(LPDIEFFESCAPE a) PURE { return IDirectInputDevice8_Escape(m_pDevice, a); }
        virtual HRESULT STDMETHODCALLTYPE Poll() PURE { return IDirectInputDevice8_Poll(m_pDevice); }
        virtual HRESULT STDMETHODCALLTYPE SendDeviceData(DWORD a, LPCDIDEVICEOBJECTDATA b, LPDWORD c, DWORD d) PURE { return IDirectInputDevice8_SendDeviceData(m_pDevice, a, b, c, d); }
        virtual HRESULT STDMETHODCALLTYPE EnumEffectsInFile(LPCSTR a, LPDIENUMEFFECTSINFILECALLBACK b, LPVOID c, DWORD d) PURE { return IDirectInputDevice8_EnumEffectsInFile(m_pDevice, a, b, c, d); }
        virtual HRESULT STDMETHODCALLTYPE WriteEffectToFile(LPCSTR a, DWORD b, LPDIFILEEFFECT c, DWORD d) PURE { return IDirectInputDevice8_WriteEffectToFile(m_pDevice, a, b, c, d); }
        virtual HRESULT STDMETHODCALLTYPE BuildActionMap(LPDIACTIONFORMATA a, LPCSTR b, DWORD c) PURE { return IDirectInputDevice8_BuildActionMap(m_pDevice, a, b, c); }
        virtual HRESULT STDMETHODCALLTYPE SetActionMap(LPDIACTIONFORMATA a, LPCSTR b, DWORD c) PURE { return IDirectInputDevice8_SetActionMap(m_pDevice, a, b, c); }
        virtual HRESULT STDMETHODCALLTYPE GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA a) PURE { return IDirectInputDevice8_GetImageInfo(m_pDevice, a); }

    private:
        IDirectInputDevice8A* m_pDevice;
    };

    using TIDirectInputA_CreateDevice = HRESULT(_stdcall*)(IDirectInput8A * pDirectInput, REFGUID typeGuid, LPDIRECTINPUTDEVICE8A * apDevice, LPUNKNOWN unused);
    using TDirectInput8Create = HRESULT(_stdcall*)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);

    static TIDirectInputA_CreateDevice RealIDirectInputA_CreateDevice = nullptr;
    static TDirectInput8Create RealDirectInput8Create = nullptr;

    static Set<StubIDirectInputDevice8A*> s_devices;

    HRESULT _stdcall StubIDirectInputDevice8A::GetDeviceState(DWORD outDataLen, LPVOID outData)
    {
        if (DInputHook::Get().IsEnabled())
        {
            std::memset(outData, 0, outDataLen);
            return 0;
        }

        return IDirectInputDevice8_GetDeviceState(m_pDevice, outDataLen, outData);
    }

    HRESULT _stdcall StubIDirectInputDevice8A::GetDeviceData(DWORD dataSize, LPDIDEVICEOBJECTDATA outData, LPDWORD outDataLen, DWORD flags)
    {
        auto& input = DInputHook::Get();

        const auto result = IDirectInputDevice8_GetDeviceData(m_pDevice, dataSize, outData, outDataLen, flags);

        DIDEVICEINSTANCEA instanceInfo;
        instanceInfo.dwSize = sizeof(instanceInfo);
        if (IDirectInputDevice8_GetDeviceInfo(m_pDevice, &instanceInfo) != DI_OK)
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

    ULONG _stdcall StubIDirectInputDevice8A::Release()
    {
        const auto result = IDirectInputDevice8_Release(m_pDevice);
        if (result == 0)
        {
            s_devices.erase(this);

            delete this;
        }

        return result;
    }

    HRESULT _stdcall HookIDirectInputA_CreateDevice(IDirectInput8A* pDirectInput, REFGUID typeGuid, LPDIRECTINPUTDEVICE8A* apDevice, LPUNKNOWN unused)
    {
        const auto result = RealIDirectInputA_CreateDevice(pDirectInput, typeGuid, apDevice, unused);

        if (result == DI_OK)
        {
            auto pStub = new StubIDirectInputDevice8A(*apDevice);

            s_devices.insert(pStub);

            *apDevice = reinterpret_cast<LPDIRECTINPUTDEVICE8A>(pStub);
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
            device->Acquire();
        }
    }

    void DInputHook::Unacquire() const noexcept
    {
        for (auto& device : s_devices)
        {
            device->Unacquire();
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
