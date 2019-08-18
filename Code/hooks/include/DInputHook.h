#pragma once

#include <Stl.h>

struct DInputHook
{
    DInputHook(DInputHook&&) = delete;
    DInputHook(const DInputHook&) = delete;
    DInputHook& operator=(DInputHook&&) = delete;
    DInputHook& operator=(const DInputHook&) = delete;

    void SetEnabled(bool aEnabled) noexcept { m_enabled = aEnabled; Update(); }
    [[nodiscard]] bool IsEnabled() const noexcept { return m_enabled; }
    void SetToggleKeys(std::initializer_list<unsigned long> aKeys);
    [[nodiscard]] bool IsToggleKey(unsigned int aKey) const noexcept;

    void Acquire() const noexcept;
    void Unacquire() const noexcept;

    static void Install() noexcept;
    static DInputHook& Get();

    void Update() const;

private:

    DInputHook() noexcept;
    ~DInputHook() = default;

    Set<unsigned long> m_toggleKeys;

    bool m_enabled{false};
};
