#pragma once

#include <Signal.h>

struct IDirect3D9;
struct IDirect3DDevice9;
struct D3D9Hook
{
    D3D9Hook() noexcept;

    static void Install();

    static D3D9Hook& Get();

    Signal<void(IDirect3D9*, IDirect3DDevice9*)> OnCreate;
    Signal<void(IDirect3DDevice9*)> OnPresent;
    Signal<void(IDirect3DDevice9*)> OnReset;

private:

};