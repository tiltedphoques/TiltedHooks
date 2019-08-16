#pragma once

#include <Windows.h>

struct WindowsHook
{
    void Install();

    void SetCallback(WNDPROC apCallback) noexcept { m_pCallback = apCallback; }
    WNDPROC GetCallback() const noexcept { return m_pCallback; }

    static WindowsHook& Get();

private:

    WNDPROC m_pCallback{ nullptr };
};