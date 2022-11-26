-- Keeps track of existing entities
EntityTable = {}

-- root path for scripts
rootpath = "scripts/main/"

-- Game states
PAUSED = -1
RUNNING = 0
ENDED = 1
PHASE_NUMBER = 0

game_state = PAUSED

isPlayerAlive = true
isBossAlive = true

-- Debugging
debug_number = 69420
debug_counter = 0

-- Player options
player_Master = {
    mass = 10,
    hopStrength = 80,
    mass = 5.0,
    damage = 10,
    posX = -75,
    posY = 10,
    rotate_dir = 1,
    gravity_X = 3.0
}

pipe_Master = {
    spawnTrigger_X = 50,
    hasSpawned = false,
}

-- Useful for resetting game
function createPlayer()
    player_ID = createEntity()
    EntityTable["Player"] = player_ID

    player_fp = rootpath .. "player.lua"
    if (loadScript("Player", player_fp, false)) then
    getScript(player_ID).name = "Player"
    getScript(player_ID).path = filePath(player_fp)
    else
    print("\t--Failed to create Player entity--")
    end

    getSprite(player_ID).name = "Player"
    getPosition(player_ID).x = player_Master.posX
    getPosition(player_ID).y = player_Master.posY
    getPosition(player_ID).z = 1.0
    getRigidBody(player_ID).velocity.x = 0.0
    getRigidBody(player_ID).velocity.y = 0.0
    getRigidBody(player_ID).acceleration.x = 0
    getRigidBody(player_ID).acceleration.y = 0
    getRigidBody(player_ID).gravity.x = 0.0
    getRigidBody(player_ID).gravity.y = 0.0
    getRigidBody(player_ID).force.x = 0.0
    getRigidBody(player_ID).force.y = 0.0
    getRotation(player_ID).angle = 180
    getRigidBody(player_ID).mass = player_Master.mass
    getRigidBody(player_ID).static = false
    getRigidBody(player_ID).trueRB = true
    getScale(player_ID).scale = 5

    getRigidBody(player_ID).min.x = 0.0
    getRigidBody(player_ID).min.y = 0.0
    getRigidBody(player_ID).max.x = 0.0
    getRigidBody(player_ID).max.y = 0.0

    getBoxCollider(player_ID, getRigidBody(player_ID).min, getRigidBody(player_ID).max)
end

function resetGame()
    isPlayerAlive = true
    isBossAlive = true
    game_state = PAUSED
    createPlayer()
end
-- Create EntityManager --
em_filepath = "scripts/main/EntityManager.lua"
if (loadScript("EntityManager", em_filepath, true)) then
    print("Entity Manager loaded")
else
    print("Failed to load Entity Manager")
end