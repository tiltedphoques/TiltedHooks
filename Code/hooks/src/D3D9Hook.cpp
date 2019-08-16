#include <D3D9Hook.h>
#include <d3d9.h>

#include <FunctionHook.h>

struct IDirect3D9Hook : IDirect3D9
{
    TP_ALLOCATOR

    explicit IDirect3D9Hook(IDirect3D9* pOriginal) noexcept : m_pIDirect3D9(pOriginal) {}
    virtual ~IDirect3D9Hook(void) = default;

    IDirect3D9Hook(IDirect3D9Hook&&) = delete;
    IDirect3D9Hook(const IDirect3D9Hook&) = delete;
    IDirect3D9Hook& operator=(IDirect3D9Hook&&) = delete;
    IDirect3D9Hook& operator=(const IDirect3D9Hook&) = delete;

    HRESULT  __stdcall QueryInterface(REFIID riid, void** ppvObj) override;
    ULONG    __stdcall AddRef(void)override { return(m_pIDirect3D9->AddRef()); }
    ULONG    __stdcall Release(void)override;
    HRESULT  __stdcall RegisterSoftwareDevice(void* pInitializeFunction)override { return(m_pIDirect3D9->RegisterSoftwareDevice(pInitializeFunction)); }
    UINT     __stdcall GetAdapterCount(void)override { return(m_pIDirect3D9->GetAdapterCount()); }
    HRESULT  __stdcall GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier)override { return(m_pIDirect3D9->GetAdapterIdentifier(Adapter, Flags, pIdentifier)); }
    UINT     __stdcall GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)override { return(m_pIDirect3D9->GetAdapterModeCount(Adapter, Format)); }
    HRESULT  __stdcall EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)override { return(m_pIDirect3D9->EnumAdapterModes(Adapter, Format, Mode, pMode)); }
    HRESULT  __stdcall GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)override { return(m_pIDirect3D9->GetAdapterDisplayMode(Adapter, pMode)); }
    HRESULT  __stdcall CheckDeviceType(UINT iAdapter, D3DDEVTYPE DevType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)override { return(m_pIDirect3D9->CheckDeviceType(iAdapter, DevType, DisplayFormat, BackBufferFormat, bWindowed)); }
    HRESULT  __stdcall CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)override { return(m_pIDirect3D9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat)); }
    HRESULT  __stdcall CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels) override {return(m_pIDirect3D9->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels));}
    HRESULT  __stdcall CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat) override { return(m_pIDirect3D9->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat));}
    HRESULT  __stdcall CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)override { return(m_pIDirect3D9->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat)); }
    HRESULT  __stdcall GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps) override { return(m_pIDirect3D9->GetDeviceCaps(Adapter, DeviceType, pCaps)); }
    HMONITOR __stdcall GetAdapterMonitor(UINT Adapter) override { return(m_pIDirect3D9->GetAdapterMonitor(Adapter)); }
    HRESULT  __stdcall CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface) override;

private:
    IDirect3D9* m_pIDirect3D9;
};

struct IDirect3DDevice9Hook : IDirect3DDevice9
{
    TP_ALLOCATOR

    explicit IDirect3DDevice9Hook(IDirect3DDevice9* apDevice) noexcept : m_pIDirect3DDevice9(apDevice) {}
    virtual ~IDirect3DDevice9Hook() = default;

    IDirect3DDevice9Hook(IDirect3DDevice9Hook&&) = delete;
    IDirect3DDevice9Hook(const IDirect3DDevice9Hook&) = delete;
    IDirect3DDevice9Hook& operator=(IDirect3DDevice9Hook&&) = delete;
    IDirect3DDevice9Hook& operator=(const IDirect3DDevice9Hook&) = delete;

    HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObj) override;
    ULONG   __stdcall AddRef(void) override { return(m_pIDirect3DDevice9->AddRef()); }
    ULONG   __stdcall Release(void) override;
    HRESULT __stdcall TestCooperativeLevel(void) override { return(m_pIDirect3DDevice9->TestCooperativeLevel()); }
    UINT __stdcall GetAvailableTextureMem(void) override { return(m_pIDirect3DDevice9->GetAvailableTextureMem()); }
    HRESULT __stdcall EvictManagedResources(void) override { return(m_pIDirect3DDevice9->EvictManagedResources()); }
    HRESULT __stdcall GetDirect3D(IDirect3D9** ppD3D9) override { return(m_pIDirect3DDevice9->GetDirect3D(ppD3D9)); }
    HRESULT __stdcall GetDeviceCaps(D3DCAPS9* pCaps) override { return(m_pIDirect3DDevice9->GetDeviceCaps(pCaps)); }
    HRESULT __stdcall GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode) override { return(m_pIDirect3DDevice9->GetDisplayMode(iSwapChain, pMode)); }
    HRESULT __stdcall GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters) override { return(m_pIDirect3DDevice9->GetCreationParameters(pParameters)); }
    HRESULT __stdcall SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap) override { return(m_pIDirect3DDevice9->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap)); }
    void    __stdcall SetCursorPosition(int X, int Y, DWORD Flags) override { return(m_pIDirect3DDevice9->SetCursorPosition(X, Y, Flags)); }
    BOOL    __stdcall ShowCursor(BOOL bShow) override { return(m_pIDirect3DDevice9->ShowCursor(bShow)); }
    HRESULT __stdcall CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain) override { return(m_pIDirect3DDevice9->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain)); }
    HRESULT __stdcall GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain) override { return(m_pIDirect3DDevice9->GetSwapChain(iSwapChain, pSwapChain)); }
    UINT    __stdcall GetNumberOfSwapChains(void) override { return(m_pIDirect3DDevice9->GetNumberOfSwapChains()); }
    HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) override;
    HRESULT __stdcall Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion) override;
    HRESULT __stdcall GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer) override { return(m_pIDirect3DDevice9->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer)); }
    HRESULT __stdcall GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus) override { return(m_pIDirect3DDevice9->GetRasterStatus(iSwapChain, pRasterStatus)); }
    HRESULT __stdcall SetDialogBoxMode(BOOL bEnableDialogs) override { return(m_pIDirect3DDevice9->SetDialogBoxMode(bEnableDialogs)); }
    void __stdcall SetGammaRamp(UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp) override { return(m_pIDirect3DDevice9->SetGammaRamp(iSwapChain, Flags, pRamp)); }
    void __stdcall GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp) override { return(m_pIDirect3DDevice9->GetGammaRamp(iSwapChain, pRamp)); }
    HRESULT __stdcall CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle) override { return(m_pIDirect3DDevice9->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle)); }
    HRESULT __stdcall CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle) override { return(m_pIDirect3DDevice9->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle)); }
    HRESULT __stdcall CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle) override { return(m_pIDirect3DDevice9->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle)); }
    HRESULT __stdcall CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle) override { return(m_pIDirect3DDevice9->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle)); }
    HRESULT __stdcall CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle) override { return(m_pIDirect3DDevice9->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle)); }
    HRESULT __stdcall CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) override { return(m_pIDirect3DDevice9->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle)); }
    HRESULT __stdcall CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) override { return(m_pIDirect3DDevice9->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle)); }
    HRESULT __stdcall UpdateSurface(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint) override { return(m_pIDirect3DDevice9->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint)); }
    HRESULT __stdcall UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture) override { return(m_pIDirect3DDevice9->UpdateTexture(pSourceTexture, pDestinationTexture)); }
    HRESULT __stdcall GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface) override { return(m_pIDirect3DDevice9->GetRenderTargetData(pRenderTarget, pDestSurface)); }
    HRESULT __stdcall GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface) override { return(m_pIDirect3DDevice9->GetFrontBufferData(iSwapChain, pDestSurface)); }
    HRESULT __stdcall StretchRect(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter) override { return(m_pIDirect3DDevice9->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter)); }
    HRESULT __stdcall ColorFill(IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color) override { return(m_pIDirect3DDevice9->ColorFill(pSurface, pRect, color)); }
    HRESULT __stdcall CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) override { return(m_pIDirect3DDevice9->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle)); }
    HRESULT __stdcall SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget) override { return(m_pIDirect3DDevice9->SetRenderTarget(RenderTargetIndex, pRenderTarget)); }
    HRESULT __stdcall GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget) override { return(m_pIDirect3DDevice9->GetRenderTarget(RenderTargetIndex, ppRenderTarget)); }
    HRESULT __stdcall SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil) override { return(m_pIDirect3DDevice9->SetDepthStencilSurface(pNewZStencil)); }
    HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface) override { return(m_pIDirect3DDevice9->GetDepthStencilSurface(ppZStencilSurface)); }
    HRESULT __stdcall BeginScene(void) override { return(m_pIDirect3DDevice9->BeginScene()); }
    HRESULT __stdcall EndScene(void) override { return(m_pIDirect3DDevice9->EndScene()); }
    HRESULT __stdcall Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) override { return(m_pIDirect3DDevice9->Clear(Count, pRects, Flags, Color, Z, Stencil)); }
    HRESULT __stdcall SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix) override { return(m_pIDirect3DDevice9->SetTransform(State, pMatrix)); }
    HRESULT __stdcall GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix) override { return(m_pIDirect3DDevice9->GetTransform(State, pMatrix)); }
    HRESULT __stdcall MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix) override { return(m_pIDirect3DDevice9->MultiplyTransform(State, pMatrix)); }
    HRESULT __stdcall SetViewport(CONST D3DVIEWPORT9* pViewport) override { return(m_pIDirect3DDevice9->SetViewport(pViewport)); }
    HRESULT __stdcall GetViewport(D3DVIEWPORT9* pViewport) override { return(m_pIDirect3DDevice9->GetViewport(pViewport)); }
    HRESULT __stdcall SetMaterial(CONST D3DMATERIAL9* pMaterial) override { return(m_pIDirect3DDevice9->SetMaterial(pMaterial)); }
    HRESULT __stdcall GetMaterial(D3DMATERIAL9* pMaterial) override { return(m_pIDirect3DDevice9->GetMaterial(pMaterial)); }
    HRESULT __stdcall SetLight(DWORD Index, CONST D3DLIGHT9* pLight) override { return(m_pIDirect3DDevice9->SetLight(Index, pLight)); }
    HRESULT __stdcall GetLight(DWORD Index, D3DLIGHT9* pLight) override { return(m_pIDirect3DDevice9->GetLight(Index, pLight)); }
    HRESULT __stdcall LightEnable(DWORD Index, BOOL Enable) override { return(m_pIDirect3DDevice9->LightEnable(Index, Enable)); }
    HRESULT __stdcall GetLightEnable(DWORD Index, BOOL* pEnable) override { return(m_pIDirect3DDevice9->GetLightEnable(Index, pEnable)); }
    HRESULT __stdcall SetClipPlane(DWORD Index, CONST float* pPlane) override { return(m_pIDirect3DDevice9->SetClipPlane(Index, pPlane)); }
    HRESULT __stdcall GetClipPlane(DWORD Index, float* pPlane) override { return(m_pIDirect3DDevice9->GetClipPlane(Index, pPlane)); }
    HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) override { return(m_pIDirect3DDevice9->SetRenderState(State, Value)); }
    HRESULT __stdcall GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue) override { return(m_pIDirect3DDevice9->GetRenderState(State, pValue)); }
    HRESULT __stdcall CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB) override { return(m_pIDirect3DDevice9->CreateStateBlock(Type, ppSB)); }
    HRESULT __stdcall BeginStateBlock(void) override { return(m_pIDirect3DDevice9->BeginStateBlock()); }
    HRESULT __stdcall EndStateBlock(IDirect3DStateBlock9** ppSB) override { return(m_pIDirect3DDevice9->EndStateBlock(ppSB)); }
    HRESULT __stdcall SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus) override { return(m_pIDirect3DDevice9->SetClipStatus(pClipStatus)); }
    HRESULT __stdcall GetClipStatus(D3DCLIPSTATUS9* pClipStatus) override { return(m_pIDirect3DDevice9->GetClipStatus(pClipStatus)); }
    HRESULT __stdcall GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture) override { return(m_pIDirect3DDevice9->GetTexture(Stage, ppTexture)); }
    HRESULT __stdcall SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture) override { return(m_pIDirect3DDevice9->SetTexture(Stage, pTexture)); }
    HRESULT __stdcall GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue) override { return(m_pIDirect3DDevice9->GetTextureStageState(Stage, Type, pValue)); }
    HRESULT __stdcall SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) override { return(m_pIDirect3DDevice9->SetTextureStageState(Stage, Type, Value)); }
    HRESULT __stdcall GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue) override { return(m_pIDirect3DDevice9->GetSamplerState(Sampler, Type, pValue)); }
    HRESULT __stdcall SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) override { return(m_pIDirect3DDevice9->SetSamplerState(Sampler, Type, Value)); }
    HRESULT __stdcall ValidateDevice(DWORD* pNumPasses) override { return(m_pIDirect3DDevice9->ValidateDevice(pNumPasses)); }
    HRESULT __stdcall SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries) override { return(m_pIDirect3DDevice9->SetPaletteEntries(PaletteNumber, pEntries)); }
    HRESULT __stdcall GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries) override { return(m_pIDirect3DDevice9->GetPaletteEntries(PaletteNumber, pEntries)); }
    HRESULT __stdcall SetCurrentTexturePalette(UINT PaletteNumber) override { return(m_pIDirect3DDevice9->SetCurrentTexturePalette(PaletteNumber)); }
    HRESULT __stdcall GetCurrentTexturePalette(UINT* PaletteNumber) override { return(m_pIDirect3DDevice9->GetCurrentTexturePalette(PaletteNumber)); }
    HRESULT __stdcall SetScissorRect(CONST RECT* pRect) override { return(m_pIDirect3DDevice9->SetScissorRect(pRect)); }
    HRESULT __stdcall GetScissorRect(RECT* pRect) override { return(m_pIDirect3DDevice9->GetScissorRect(pRect)); }
    HRESULT __stdcall SetSoftwareVertexProcessing(BOOL bSoftware) override { return(m_pIDirect3DDevice9->SetSoftwareVertexProcessing(bSoftware)); }
    BOOL    __stdcall GetSoftwareVertexProcessing(void) override { return(m_pIDirect3DDevice9->GetSoftwareVertexProcessing()); }
    HRESULT __stdcall SetNPatchMode(float nSegments) override { return(m_pIDirect3DDevice9->SetNPatchMode(nSegments)); }
    float   __stdcall GetNPatchMode(void) override { return(m_pIDirect3DDevice9->GetNPatchMode()); }
    HRESULT __stdcall DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) override { return(m_pIDirect3DDevice9->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount)); }
    HRESULT __stdcall DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount) override { return(m_pIDirect3DDevice9->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount)); }
    HRESULT __stdcall DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride) override { return(m_pIDirect3DDevice9->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride)); }
    HRESULT __stdcall DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride) override { return(m_pIDirect3DDevice9->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride)); }
    HRESULT __stdcall ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags) override { return(m_pIDirect3DDevice9->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags)); }
    HRESULT __stdcall CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl) override { return(m_pIDirect3DDevice9->CreateVertexDeclaration(pVertexElements, ppDecl)); }
    HRESULT __stdcall SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl) override { return(m_pIDirect3DDevice9->SetVertexDeclaration(pDecl)); }
    HRESULT __stdcall GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl) override { return(m_pIDirect3DDevice9->GetVertexDeclaration(ppDecl)); }
    HRESULT __stdcall SetFVF(DWORD FVF) override { return(m_pIDirect3DDevice9->SetFVF(FVF)); }
    HRESULT __stdcall GetFVF(DWORD* pFVF) override { return(m_pIDirect3DDevice9->GetFVF(pFVF)); }
    HRESULT __stdcall CreateVertexShader(CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader) override { return(m_pIDirect3DDevice9->CreateVertexShader(pFunction, ppShader)); }
    HRESULT __stdcall SetVertexShader(IDirect3DVertexShader9* pShader) override { return(m_pIDirect3DDevice9->SetVertexShader(pShader)); }
    HRESULT __stdcall GetVertexShader(IDirect3DVertexShader9** ppShader) override { return(m_pIDirect3DDevice9->GetVertexShader(ppShader)); }
    HRESULT __stdcall SetVertexShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount) override { return(m_pIDirect3DDevice9->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount)); }
    HRESULT __stdcall GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount) override { return(m_pIDirect3DDevice9->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount)); }
    HRESULT __stdcall SetVertexShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount) override { return(m_pIDirect3DDevice9->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount)); }
    HRESULT __stdcall GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount) override { return(m_pIDirect3DDevice9->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount)); }
    HRESULT __stdcall SetVertexShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount) override { return(m_pIDirect3DDevice9->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount)); }
    HRESULT __stdcall GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount) override { return(m_pIDirect3DDevice9->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount)); }
    HRESULT __stdcall SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride) override { return(m_pIDirect3DDevice9->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride)); }
    HRESULT __stdcall GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* OffsetInBytes, UINT* pStride) override { return(m_pIDirect3DDevice9->GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride)); }
    HRESULT __stdcall SetStreamSourceFreq(UINT StreamNumber, UINT Divider) override { return(m_pIDirect3DDevice9->SetStreamSourceFreq(StreamNumber, Divider)); }
    HRESULT __stdcall GetStreamSourceFreq(UINT StreamNumber, UINT* Divider) override { return(m_pIDirect3DDevice9->GetStreamSourceFreq(StreamNumber, Divider)); }
    HRESULT __stdcall SetIndices(IDirect3DIndexBuffer9* pIndexData) override { return(m_pIDirect3DDevice9->SetIndices(pIndexData)); }
    HRESULT __stdcall GetIndices(IDirect3DIndexBuffer9** ppIndexData) override { return(m_pIDirect3DDevice9->GetIndices(ppIndexData)); }
    HRESULT __stdcall CreatePixelShader(CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader) override { return(m_pIDirect3DDevice9->CreatePixelShader(pFunction, ppShader)); }
    HRESULT __stdcall SetPixelShader(IDirect3DPixelShader9* pShader) override { return(m_pIDirect3DDevice9->SetPixelShader(pShader)); }
    HRESULT __stdcall GetPixelShader(IDirect3DPixelShader9** ppShader) override { return(m_pIDirect3DDevice9->GetPixelShader(ppShader)); }
    HRESULT __stdcall SetPixelShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount) override { return(m_pIDirect3DDevice9->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount)); }
    HRESULT __stdcall GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount) override { return(m_pIDirect3DDevice9->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount)); }
    HRESULT __stdcall SetPixelShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount) override { return(m_pIDirect3DDevice9->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount)); }
    HRESULT __stdcall GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount) override { return(m_pIDirect3DDevice9->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount)); }
    HRESULT __stdcall SetPixelShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount) override { return(m_pIDirect3DDevice9->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount)); }
    HRESULT __stdcall GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount) override { return(m_pIDirect3DDevice9->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount)); }
    HRESULT __stdcall DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo) override { return(m_pIDirect3DDevice9->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo)); }
    HRESULT __stdcall DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo) override { return(m_pIDirect3DDevice9->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo)); }
    HRESULT __stdcall DeletePatch(UINT Handle) override { return(m_pIDirect3DDevice9->DeletePatch(Handle)); }
    HRESULT __stdcall CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery) override { return(m_pIDirect3DDevice9->CreateQuery(Type, ppQuery)); }

private:

    IDirect3DDevice9* m_pIDirect3DDevice9{nullptr};
};

ULONG __stdcall IDirect3D9Hook::Release(void)
{
    const auto count = m_pIDirect3D9->Release();
    if (!count)
        Delete(this);

    return count;
}

HRESULT  __stdcall IDirect3D9Hook::QueryInterface(REFIID riid, void** ppvObj)
{
    const auto result = m_pIDirect3D9->QueryInterface(riid, ppvObj);

    if (result == NOERROR)
        *ppvObj = this;

    return result;
}

HRESULT __stdcall IDirect3D9Hook::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface)
{
    const auto result = m_pIDirect3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

    const auto pDevice = *ppReturnedDeviceInterface;

    *ppReturnedDeviceInterface = New<IDirect3DDevice9Hook>(pDevice);

    D3D9Hook::Get().OnCreate(m_pIDirect3D9, pDevice);

    return result;
}

HRESULT IDirect3DDevice9Hook::QueryInterface(REFIID riid, void** ppvObj)
{
    const auto result = m_pIDirect3DDevice9->QueryInterface(riid, ppvObj);

    if (result == NOERROR)
        * ppvObj = this;

    return result;
}

ULONG IDirect3DDevice9Hook::Release(void)
{
    const auto count = m_pIDirect3DDevice9->Release();
    if (!count)
        Delete(this);

    return count;
}

HRESULT IDirect3DDevice9Hook::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    D3D9Hook::Get().OnReset(m_pIDirect3DDevice9);

    const auto result = m_pIDirect3DDevice9->Reset(pPresentationParameters);

    return result;
}

HRESULT IDirect3DDevice9Hook::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
    D3D9Hook::Get().OnPresent(m_pIDirect3DDevice9);

    D3DRECT rec = { 1, 1, 50, 50 };
    m_pIDirect3DDevice9->Clear(1, &rec, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 255, 0), 0, 0);

    const auto result = m_pIDirect3DDevice9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

    return result;
}

using TDirect3DCreate9 = IDirect3D9*(WINAPI*)(UINT);
static TDirect3DCreate9 RealDirect3DCreate9 = nullptr;

static IDirect3D9* WINAPI HookDirect3DCreate9(UINT SDKVersion)
{
    IDirect3D9* pIDirect3D9 = RealDirect3DCreate9(SDKVersion);
    const auto pD3D9 = New<IDirect3D9Hook>(pIDirect3D9);

    return pD3D9;
}

D3D9Hook::D3D9Hook() noexcept
{
}

void D3D9Hook::Install()
{
    if(RealDirect3DCreate9 == nullptr)
        RealDirect3DCreate9 = reinterpret_cast<TDirect3DCreate9>(TP_HOOK_SYSTEM("d3d9.dll", "Direct3DCreate9", HookDirect3DCreate9));
}

D3D9Hook& D3D9Hook::Get()
{
    static D3D9Hook s_instance;
    return s_instance;
}
