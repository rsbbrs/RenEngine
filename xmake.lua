includes("external/xmake_soloud.lua")
add_rules("mode.debug", "mode.release")
add_requires("glfw")
add_requires("soloud")
add_requires("sokol")
add_requires("glm")

set_policy("build.warning", true) -- show warnings
set_warnings("all") -- warn about many things

target("helloworld")
    set_kind("binary")
    set_languages("cxx17")

    add_deps("RenEngine")
    
    add_files("demo/helloworld.cpp")

    -- Copy assets
    after_build(function (target)
        cprint("Copying assets")
        os.cp("$(projectdir)/assets", path.directory(target:targetfile()))
    end)

target("RenEngine")
    set_kind("static")
    set_languages("cxx17")
    
    -- Declare our engine's header path.
    -- This allows targets that depend on the engine to #include them.
    add_includedirs("src", {public = true})
    
    -- Add all .cpp files in the `src` directory.
    add_files("src/*.cpp")

    -- Packages
    add_packages("glfw", {public = true})
    add_packages("soloud", {public = true})
    add_packages("sokol")
    add_packages("glm", {public = true})