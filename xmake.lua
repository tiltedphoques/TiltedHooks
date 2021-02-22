set_languages("cxx17")

set_xmakever("2.5.1")

add_requires("tiltedcore", "mimalloc", "hopscotch-map")
add_requires("catch2")

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
    add_includedirs("Code/hooks/include/")
    add_headerfiles("Code/hooks/include/*.hpp", {prefixdir = "TiltedHooks"})
    add_syslinks("dxguid", "dinput8", "d3d11")
    add_packages("tiltedcore", "mimalloc", "hopscotch-map")
    add_deps("TiltedReverse")

