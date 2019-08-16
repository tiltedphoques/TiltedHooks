#pragma once

#include <Windows.h>

struct WindowsHook
{
    WindowsHook(WindowsHook&&) = delete;
    WindowsHook(const WindowsHook&) = delete;
    WindowsHook& operator=(WindowsHook&&) = delete;
    WindowsHook& operator=(const WindowsHook&) = delete;

    void SetCallback(WNDPROC apCallback) noexcept { m_pCallback = apCallback; }
    [[nodiscard]] WNDPROC GetCallback() const noexcept { return m_pCallback; }

    static void Install() noexcept;
    static WindowsHook& Get();

private:

    WindowsHook() = default;
    ~WindowsHook() = default;

    WNDPROC m_pCallback{ nullptr };
};