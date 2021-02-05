#pragma once

#include <TiltedCore/Stl.hpp>

namespace TiltedPhoques
{
    struct DInputHook
    {
        TP_NOCOPYMOVE(DInputHook);

        void SetEnabled(bool aEnabled) noexcept { m_enabled = aEnabled; Update(); }
        [[nodiscard]] bool IsEnabled() const noexcept { return m_enabled; }
        void SetToggleKeys(std::initializer_list<unsigned long> aKeys) noexcept;
        [[nodiscard]] bool IsToggleKey(unsigned int aKey) const noexcept;

        void Acquire() const noexcept;
        void Unacquire() const noexcept;

        static void Install() noexcept;
        static DInputHook& Get() noexcept;

        void Update() const noexcept;

    private:

        DInputHook() noexcept;
        ~DInputHook() = default;

        Set<unsigned long> m_toggleKeys;

        bool m_enabled{ false };
    };
}
