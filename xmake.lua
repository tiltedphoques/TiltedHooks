set_languages("cxx17")

set_xmakever("2.5.1")

-- direct dependency version pinning
add_requires("tiltedcore v0.2.7", "hopscotch-map v2.3.1", "catch2 2.13.9", "mem 1.0.0")

-- dependencies' dependencies version pinning
add_requireconfs("*.mimalloc", { version = "2.1.7"}) -- no override because TiltedReverse dependency
add_requireconfs("*.cmake", { version = "3.30.2"}) -- no override because TiltedReverse dependency

add_rules("mode.debug","mode.releasedbg", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

if is_mode("release") then
    add_ldflags("/LTCG", "/OPT:REF")
    add_cxflags("/Ot", "/GL", "/Ob2", "/Oi", "/GS-")
    add_defines("NDEBUG")
    set_optimize("fastest")
end

target("TiltedHooks")
    set_kind("static")
    set_group("Libraries")
    add_files("Code/hooks/src/*.cpp")
    add_files("Code/hooks/src/DInputHook.cpp", {unity_ignored = true})
    add_includedirs("Code/hooks/include/", {public = true})
    add_headerfiles("Code/hooks/include/*.hpp", {prefixdir = "TiltedHooks"})
    add_syslinks("dxguid", "dinput8", "d3d11")
    add_packages("tiltedcore", "mimalloc", "hopscotch-map", "mem")
    add_deps("TiltedReverse")

