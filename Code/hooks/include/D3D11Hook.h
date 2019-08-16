#pragma once

struct D3D11Hook
{
    D3D11Hook() noexcept;

    static void Install();

    static D3D11Hook& Get();

private:

};