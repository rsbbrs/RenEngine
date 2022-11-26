-- Keeps track of existing significant entities (i.e., player and boss)
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

-- EntityID Management for projectiles
fireBall_ID = {}
pipe_ID = {}

-- Debugging
debug_number = 69420
debug_counter = 0

-- Player options
player_Master = {
    mass = 10,
    hopStrength = 80,
    mass = 5.0,
    damage = 10,
    posX = -95,
    posY = 10,
    posZ = 1.0,
    rotate_dir = 1,
    gravity_X = 3.0,
    damage = 5.0
}

boss_Master = 
{
    posX = 100,
    posY = 0,
    posZ = 1.0,
    angle = 180,
    healthPercent = 500.0
}

pipe_Master = {
    spawnTrigger_X = 50,
    hasSpawned = false,
    pipeSpeed = -40
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
        return
    end

    getSprite(player_ID).name = "Player"
    getPosition(player_ID).x = player_Master.posX
    getPosition(player_ID).y = player_Master.posY
    getPosition(player_ID).z = player_Master.posZ
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

function createBoss()
    boss_ID = createEntity()

    EntityTable["Boss"] = boss_ID

    boss_fp = rootpath .. "boss.lua"
    if (loadScript("Boss", boss_fp, false)) then
        getScript(boss_ID).name = "Boss"
        getScript(boss_ID).path = filePath(boss_fp)
    else
        print("\t--Failed to create Boss entity--")
        return
    end

    getSprite(boss_ID).name = "Boss"
    getPosition(boss_ID).x = boss_Master.posX
    getPosition(boss_ID).y = boss_Master.posY
    getPosition(boss_ID).z = boss_Master.posZ
    getRigidBody(boss_ID).velocity.x = 0.0
    getRigidBody(boss_ID).velocity.y = 0.0
    getRigidBody(boss_ID).acceleration.x = 0
    getRigidBody(boss_ID).acceleration.y = 0
    getRigidBody(boss_ID).gravity.x = 0.0
    getRigidBody(boss_ID).gravity.y = 0.0
    getRigidBody(boss_ID).force.x = 0.0
    getRigidBody(boss_ID).force.y = 0.0
    getRotation(boss_ID).angle = boss_Master.angle
    getRigidBody(boss_ID).mass = 10.0
    getRigidBody(boss_ID).static = true
    getRigidBody(boss_ID).trueRB = false
    getScale(boss_ID).scale = 35

    getRigidBody(boss_ID).min.x = 0.0
    getRigidBody(boss_ID).min.y = 0.0
    getRigidBody(boss_ID).max.x = 0.0
    getRigidBody(boss_ID).max.y = 0.0

    getBoxCollider(boss_ID, getRigidBody(boss_ID).min, getRigidBody(boss_ID).max)

    getHealth(boss_ID).percent = boss_Master.healthPercent
end

function createBackground()
    layer_0 = createEntity()
    layer_1 = createEntity()
    layer_2 = createEntity()
    layer_3 = createEntity()
    layer_4 = createEntity()


    getSprite(layer_0).name = "Bg_Layer_0"
    getSprite(layer_0).rigidBody = false
    getPosition(layer_0).x = 0.0
    getPosition(layer_0).y = 0.0
    getPosition(layer_0).z = 1.0
    getRotation(layer_0).angle = 180;
    getScale(layer_0).scale = 200

    getSprite(layer_1).name = "Bg_Layer_1"
    getSprite(layer_1).rigidBody = false
    getPosition(layer_1).x = 0.0
    getPosition(layer_1).y = 0.0
    getPosition(layer_1).z = 1.0
    getRotation(layer_1).angle = 180;
    getScale(layer_1).scale = 200

    getSprite(layer_2).name = "Bg_Layer_2"
    getSprite(layer_2).rigidBody = false
    getPosition(layer_2).x = 0.0
    getPosition(layer_2).y = 0.0
    getPosition(layer_2).z = 1.0
    getRotation(layer_2).angle = 180;
    getScale(layer_2).scale = 200

    getSprite(layer_3).name = "Bg_Layer_3"
    getSprite(layer_3).rigidBody = false
    getPosition(layer_3).x = 0.0
    getPosition(layer_3).y = 0.0
    getPosition(layer_3).z = 1.0
    getRotation(layer_3).angle = 180;
    getScale(layer_3).scale = 200

    getSprite(layer_4).name = "Bg_Layer_4"
    getSprite(layer_4).rigidBody = false
    getPosition(layer_4).x = 0.0
    getPosition(layer_4).y = 0.0
    getPosition(layer_4).z = 1.0
    getRotation(layer_4).angle = 180;
    getScale(layer_4).scale = 200
end

function resetGame()
    
    -- Reset states
    isPlayerAlive = true
    isBossAlive = true
    game_state = PAUSED
    PHASE_NUMBER = 0

    -- Destroy all existing objects
    for i = 1, #pipe_ID, 1 do
        destroyEntity(table.remove(pipe_ID))
    end
    
    for i = 1, #fireBall_ID, 1 do
        destroyEntity(table.remove(fireBall_ID))
    end

    EntityTable["Boss"] = nil    
    EntityTable["Player"] = nil

    -- Create player and boss
    createPlayer()
    createBoss()
end
-- Create EntityManager --
em_filepath = "scripts/main/EntityManager.lua"
if (loadScript("EntityManager", em_filepath, true)) then
    print("Entity Manager loaded")
else
    print("Failed to load Entity Manager")
end