-- Keeps track of existing significant entities (i.e., player and boss)
EntityTable = {}
BgTable = {}

-- root path for scripts
rootpath = "scripts/main/"

-- Keeping track of time
startTime = 0.0
ticks = 0

-- Game states
PAUSED = -1
RUNNING = 0
ENDED = 1
WAITING = 2

game_state = PAUSED

isPlayerAlive = true
isBossAlive = true

-- EntityID Management for projectiles
-- fireBall_ID = {}
-- pipe_ID = {}

-- Player options
player_Master = {
    mass = 10,
    hopStrength = 90,
    mass = 5.0,
    damage = 5,
    posX = -95,
    posY = 10,
    posZ = 0.9,
    rotate_dir = 1,
    gravity_X = 3.0,
    --damage = 0.5
}

boss_Master = {
    phase = 0,
    isBobbing = true,
    retreated = false,
    retreating = false,
    returning = false,
    retreatedCounter = 0,
    tempHealth = 0.0,
    posX = 155,
    posY = 0,
    posZ = 1.0,
    angle = 180,
    healthPercent = 100.0,
    gravityY = 0.0,
    frequency = 0.5,
    amplitude = 75,
    skillCoolDown = 15.0,
    temp_fireRate = 0.5,
    fireRate = 0.6,
    pipeRate = 1.85,
    ballRate = 2.0,
    upDown_Ticks = 0,
    coolDown_Ticks = 0,
    fireRate_Ticks = 0,
    pipeRate_Ticks = 0,
    ballRate_Ticks = 0,
}

pipe_Master = {
    temp_pipeSpeed = -100.0,
    pipeSpeed = -100.0,
    temp_pipeGap = 45.0,
    pipeGap = 65.0
}

-- Retrieves y position relative to boss eye level
function getBossEyeLevel()
    return getPosition(EntityTable["Boss"]).y + 20
end

function getDeltaTime(elapsedTime)
    return elapsedTime - startTime
end

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
    -- Sky background layer.
    layer_0 = createEntity()
    BgTable[0] = layer_0
    getSprite(layer_0).name = "Bg_Layer_0"
    getSprite(layer_0).rigidBody = false
    getPosition(layer_0).x = 0.0
    getPosition(layer_0).y = 0.0
    getPosition(layer_0).z = 1.0
    getRotation(layer_0).angle = 180;
    getScale(layer_0).scale = 200

    -- Clouds background layer.
    layer_1_1 = createEntity()
    layer_1_2 = createEntity()
    BgTable[1] = layer_1_1
    BgTable[2] = layer_1_2

    getSprite(layer_1_1).name = "Bg_Layer_1"
    getSprite(layer_1_1).rigidBody = false
    getPosition(layer_1_1).x = 0.0
    getPosition(layer_1_1).y = 0.0
    getPosition(layer_1_1).z = 1.0
    getRotation(layer_1_1).angle = 180;
    getScale(layer_1_1).scale = 200

    getSprite(layer_1_2).name = "Bg_Layer_1"
    getSprite(layer_1_2).rigidBody = false
    getPosition(layer_1_2).x = 380.0
    getPosition(layer_1_2).y = 0.0
    getPosition(layer_1_2).z = 1.0
    getRotation(layer_1_2).angle = 180;
    getScale(layer_1_2).scale = 200

    -- White mountain layer.
    layer_2_1 = createEntity()
    layer_2_2 = createEntity()
    BgTable[3] = layer_2_1
    BgTable[4] = layer_2_2

    getSprite(layer_2_1).name = "Bg_Layer_2"
    getSprite(layer_2_1).rigidBody = false
    getPosition(layer_2_1).x = 0.0
    getPosition(layer_2_1).y = -15.0
    getPosition(layer_2_1).z = 1.0
    getRotation(layer_2_1).angle = 180;
    getScale(layer_2_1).scale = 200

    getSprite(layer_2_2).name = "Bg_Layer_2"
    getSprite(layer_2_2).rigidBody = false
    getPosition(layer_2_2).x = 360.0
    getPosition(layer_2_2).y = -15.0
    getPosition(layer_2_2).z = 1.0
    getRotation(layer_2_2).angle = 180;
    getScale(layer_2_2).scale = 200

    -- Brown mountain layer.
    layer_3_1 = createEntity()
    layer_3_2 = createEntity()
    BgTable[5] = layer_3_1
    BgTable[6] = layer_3_2

    getSprite(layer_3_1).name = "Bg_Layer_3"
    getSprite(layer_3_1).rigidBody = false
    getPosition(layer_3_1).x = 0.0
    getPosition(layer_3_1).y = -30.0
    getPosition(layer_3_1).z = 1.0
    getRotation(layer_3_1).angle = 180;
    getScale(layer_3_1).scale = 200

    getSprite(layer_3_2).name = "Bg_Layer_3"
    getSprite(layer_3_2).rigidBody = false
    getPosition(layer_3_2).x = 380.0
    getPosition(layer_3_2).y = -30.0
    getPosition(layer_3_2).z = 1.0
    getRotation(layer_3_2).angle = 180;
    getScale(layer_3_2).scale = 200

    -- Forest layer.
    layer_4_1 = createEntity()
    layer_4_2 = createEntity()
    BgTable[7] = layer_4_1
    BgTable[8] = layer_4_2

    getSprite(layer_4_1).name = "Bg_Layer_4"
    getSprite(layer_4_1).rigidBody = false
    getPosition(layer_4_1).x = 0.0
    getPosition(layer_4_1).y = -30.0
    getPosition(layer_4_1).z = 1.0
    getRotation(layer_4_1).angle = 180;
    getScale(layer_4_1).scale = 200

    getSprite(layer_4_2).name = "Bg_Layer_4"
    getSprite(layer_4_2).rigidBody = false
    getPosition(layer_4_2).x = -380.0
    getPosition(layer_4_2).y = -30.0
    getPosition(layer_4_2).z = 1.0
    getRotation(layer_4_2).angle = 180;
    getScale(layer_4_2).scale = 200

    -- Entity responsible for updating moving background.
    bgManager = createEntity()
    getScript(bgManager).name = "Background"
    getScript(bgManager).path = filePath("scripts/main/background.lua")
end

function resetGame()
    
    -- Reset states
    isPlayerAlive = true
    isBossAlive = true
    
    boss_Master.phase = 0
    boss_Master.isCoolingDown = false
    boss_Master.isSpawningPipes = false
    boss_Master.isBobbing = true
    boss_Master.retreated = false
    boss_Master.retreatedCounter = 0
    boss_Master.retreating = false
    boss_Master.returning = false
    boss_Master.fireRate = boss_Master.temp_fireRate

    pipe_Master.pipeGap = pipe_Master.temp_pipeGap
    pipe_Master.pipeSpeed = pipe_Master.temp_pipeSpeed
    
    game_state = PAUSED

    -- Destroy all existing objects
    for i = 1, #pipe_ID, 1 do
        destroyEntity(table.remove(pipe_ID))
    end
    
    for i = 1, #fireBall_ID, 1 do
        destroyEntity(table.remove(fireBall_ID))
    end

    for i = 1, #laser_ID, 1 do
        destroyEntity(table.remove(laser_ID))
    end

    for i = 1, #ball_ID, 1 do
        destroyEntity(table.remove(ball_ID))
    end

    if (EntityTable["Boss"]) then
        destroyEntity(EntityTable["Boss"])
        EntityTable["Boss"] = nil
    end

    if (EntityTable["Player"]) then
        destroyEntity(EntityTable["Player"])
        EntityTable["Player"] = nil
    end

    if (EntityTable["Crosshair"]) then
        destroyEntity(EntityTable["Crosshair"])
        EntityTable["Crosshair"] = nil
    end

    -- Create player and boss
    createPlayer()
    createBoss()
end

function youWin()
    for i = 1, #pipe_ID, 1 do
        destroyEntity(table.remove(pipe_ID))
    end
    
    for i = 1, #laser_ID, 1 do
        destroyEntity(table.remove(laser_ID))
    end

    for i = 1, #ball_ID, 1 do
        destroyEntity(table.remove(ball_ID))
    end

    print("\t-- YOU WIN! --")
end

function youLose()
    stopSound("Boss_Theme")

    if (isBossAlive) then
        print("\t-- YOU LOSE! --")
    end
end

-- Create EntityManager --
em_filepath = "scripts/main/EntityManager.lua"
if (loadScript("EntityManager", em_filepath, true)) then
    print("Entity Manager loaded")
else
    print("Failed to load Entity Manager")
end