function CreateHooksProject(basePath, reverseBasePath, coreBasePath)
    project ("Hooks")
        kind ("StaticLib")
        language ("C++")
        
        filter { "architecture:*86" }

            includedirs
            {
                "$(DXSDK_DIR)/Include"
            }

            libdirs 
            {
                "$(DXSDK_DIR)/Lib/x86",
                "$(VsInstallDir)DIA SDK/lib"
            }

            links
            {
                "d3d9.lib",
                "d3dx9.lib",
                "MSVCRT.LIB",
                "dxguid.lib",
            }

        filter { "architecture:*64" }

            includedirs
            {
                basePath .. "/ThirdParty/DirectXTK"
            }

            libdirs 
            {
                "$(VsInstallDir)DIA SDK/lib/amd64"
            }

            links
            {
                "d3d11.lib",
                basePath .. "/ThirdParty/DirectXTK.lib",
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
            basePath .. "/Code/hooks/include/**.h",
            basePath .. "/Code/hooks/src/**.cpp",
        }
        
        
end
