#pragma once

#include <Stl.h>

struct DInputHook
{
    DInputHook(DInputHook&&) = delete;
    DInputHook(const DInputHook&) = delete;
    DInputHook& operator=(DInputHook&&) = delete;
    DInputHook& operator=(const DInputHook&) = delete;

    [[nodiscard]] bool IsInputBlocked() const noexcept { return m_blockInput; }
    void SetInputBlocked(bool aBlockInput) noexcept { m_blockInput = aBlockInput; }
    void SetToggleKeys(std::initializer_list<unsigned long> aKeys);
    [[nodiscard]] bool IsToggleKey(unsigned int aKey) const noexcept;

    void Acquire() const noexcept;
    void Unacquire() const noexcept;

    static void Install() noexcept;
    static DInputHook& Get();



private:

    DInputHook() noexcept;
    ~DInputHook() = default;

    bool m_blockInput{ false };
    Set<unsigned long> m_toggleKeys;
};