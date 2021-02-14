workspace "JumpV.Main"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    startproject "JumpV.Main"

include "realiti2D/r2dstandalone.lua"

project "JumpV.Main"
    location "JumpV.Main"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "realiti2D/Realiti2D/src",
        "realiti2D/Realiti2D/thirdparty/spdlog/include",
        "realiti2D/Realiti2D/thirdparty/SDL2-2.0.12/include",
        "realiti2D/Realiti2D/thirdparty/glew-2.1.0/include",
        "realiti2D/Realiti2D/thirdparty/soil-0.0.3/include",
        "realiti2D/Realiti2D/thirdparty/glm",
        "realiti2D/Realiti2D/thirdparty/rapidjson-1.1.0/include"
    }

    links
    {
        "Realiti2D"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
        }

    filter "configurations:Debug"
        defines "R2D_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "R2D_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "R2D_DIST"
        optimize "On"