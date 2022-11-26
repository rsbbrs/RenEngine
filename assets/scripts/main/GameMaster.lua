-- Game states
PAUSED = -1
RUNNING = 0
ENDED = 1
game_state = 0

-- Create EntityManager
em_filepath = "scripts/main/EntityManager.lua"
if (loadScript("EntityManager", em_filepath, true)) then
    print("Entity Manager loaded")
else
    print("Failed to load Entity Manager")
end