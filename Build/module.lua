premake.extensions.hooks = {}

function hooks_parent_path()
    local str = debug.getinfo(2, "S").source:sub(2)
    local dir =  str:match("(.*/)"):sub(0,-2)
    local index = string.find(dir, "/[^/]*$")
    return dir:sub(0, index)
end

function hooks_generate()
    if premake.extensions.hooks.generated == true then
        return
    end

    local basePath = premake.extensions.hooks.path
    local coreBasePath = premake.extensions.core.path
    local reverseBasePath = premake.extensions.reverse.path

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

    premake.extensions.hooks.generated = true
end

premake.extensions.hooks.path = hooks_parent_path()
premake.extensions.hooks.generate = hooks_generate
