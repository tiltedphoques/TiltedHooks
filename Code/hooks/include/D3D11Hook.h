#pragma once

struct D3D11Hook
{
    D3D11Hook(D3D11Hook&&) = delete;
    D3D11Hook(const D3D11Hook&) = delete;
    D3D11Hook& operator=(D3D11Hook&&) = delete;
    D3D11Hook& operator=(const D3D11Hook&) = delete;

    static void Install();
    static D3D11Hook& Get();

private:

    D3D11Hook() noexcept;
    ~D3D11Hook() = default;
};
