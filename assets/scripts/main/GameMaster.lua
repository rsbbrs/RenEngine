-- Game states
PAUSED = -1
RUNNING = 0
ENDED = 1
game_state = PAUSED

debug_number = 69420
debug_counter = 0

-- Create EntityManager --
em_filepath = "scripts/main/EntityManager.lua"
if (loadScript("EntityManager", em_filepath, true)) then
    print("Entity Manager loaded")
else
    print("Failed to load Entity Manager")
end

function debug()
    debug_counter = debug_counter + 1
    print("Game master has been bothered: " .. debug_counter .. " times")
end