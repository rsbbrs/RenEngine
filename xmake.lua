includes("external/xmake_soloud.lua")
add_rules("mode.debug", "mode.release")
add_requires("glfw >=3.4")
add_requires("soloud >=20200207")
add_requires("sokol >=2023.01.27")
add_requires("glm >=1.0.1")
add_requires("stb >=2023.12.15")
add_requires("lua >=5.4.6", "sol2 >=3.3.0")
add_requires("imgui >=1.90.8", {configs = {glfw_opengl3 = true}})

set_policy("build.warning", true) -- show warnings
set_warnings("all") -- warn about many things

target("main")
    set_kind("binary")
    set_languages("cxx17")

    add_deps("RenEngine")
    
    add_files("demo/main.cpp")

    -- Copy assets
    set_rundir("$(projectdir)")
    -- after_build(function (target)
        -- cprint("Copying assets")
        -- os.cp("$(projectdir)/assets", path.directory(target:targetfile()))
    -- end)

target("mainGame")
    set_kind("binary")
    set_languages("cxx17")

    add_deps("RenEngine")

    add_files("demo/mainGame.cpp")

    set_rundir("$(projectdir)")

target("physicsDemo")
    set_kind("binary")
    set_languages("cxx17")

    add_deps("RenEngine")

    add_files("demo/physicsDemo.cpp")

    set_rundir("$(projectdir)")

target("RenEngine")
    set_kind("static")
    set_languages("cxx17")
    
    -- Declare our engine's header path.
    -- This allows targets that depend on the engine to #include them.
    add_includedirs("src/headerFiles", {public = true})
    
    -- Add all .cpp files in the `src` directory.
    add_files("src/*.cpp")

    -- Packages
    add_packages("glfw", {public = true})
    add_packages("soloud", {public = true})
    add_packages("sokol")
    add_packages("glm", {public = true})
    add_packages("stb")
    add_packages("lua")
    add_packages("sol2", {public = true})
    add_packages("imgui", {public = true})