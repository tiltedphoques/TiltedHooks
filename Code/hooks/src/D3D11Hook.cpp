#include <D3D11Hook.h>

#include <FunctionHook.h>


D3D11Hook::D3D11Hook() noexcept
{
}

void D3D11Hook::Install()
{
}

D3D11Hook& D3D11Hook::Get()
{
    static D3D11Hook s_instance;
    return s_instance;
}
