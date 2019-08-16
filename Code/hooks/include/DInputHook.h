#pragma once

#include <Stl.h>

struct DInputHook
{
    DInputHook() noexcept;

    void Install();
    bool IsInputBlocked() const noexcept { return m_blockInput; }
    void SetInputBlocked(bool aBlockInput) noexcept { m_blockInput = aBlockInput; }
    void SetToggleKeys(std::initializer_list<unsigned long> aKeys);
    bool IsToggleKey(unsigned int aKey) const noexcept;

    static DInputHook& Get();

private:

    bool m_blockInput{ false };
    Set<unsigned long> m_toggleKeys;
};