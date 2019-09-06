function CreateHooksProject(basePath, reverseBasePath, coreBasePath)
    project ("Hooks")
        kind ("StaticLib")
        language ("C++")
        
        links
        {
            "dxguid.lib",
            "dinput8.lib",
            "d3d9.lib",
            "d3d11.lib",
            "d3dx9.lib",
            "MSVCRT.LIB",
            "DirectXTK.lib"
        }
        
        includedirs
        {
            "$(DXSDK_DIR)/Include",
            basePath .. "/ThirdParty/DirectXTK/include"
        }
        
        filter { "architecture:*86" }
            libdirs 
            {
                "$(DXSDK_DIR)/Lib/x86",
                "$(VsInstallDir)DIA SDK/lib",
                basePath .. "/ThirdParty/DirectXTK/lib/x32"
            }

        filter { "architecture:*64" }
            libdirs 
            {
                "$(DXSDK_DIR)/Lib/x64",
                "$(VsInstallDir)DIA SDK/lib/amd64",
                basePath .. "/ThirdParty/DirectXTK/lib/x64"
            }
            
        filter {}

        includedirs
        {
            reverseBasePath .. "/Code/reverse/include/",
            coreBasePath .. "/Code/core/include/",
            basePath .. "/Code/hooks/include/",
            basePath .. "/ThirdParty/",
        }

        files
        {
            basePath .. "/Code/hooks/include/**.hpp",
            basePath .. "/Code/hooks/src/**.cpp",
        }
        
        
end
