#pragma once

#include <Signal.h>

struct IDirect3D9;
struct IDirect3DDevice9;
struct D3D9Hook
{
    D3D9Hook(D3D9Hook&&) = delete;
    D3D9Hook(const D3D9Hook&) = delete;
    D3D9Hook& operator=(D3D9Hook&&) = delete;
    D3D9Hook& operator=(const D3D9Hook&) = delete;

    Signal<void(IDirect3D9*, IDirect3DDevice9*)> OnCreate;
    Signal<void(IDirect3DDevice9*)> OnPresent;
    Signal<void(IDirect3DDevice9*)> OnReset;

    static void Install();
    static D3D9Hook& Get();

private:

    D3D9Hook() noexcept;
    ~D3D9Hook() = default;
};