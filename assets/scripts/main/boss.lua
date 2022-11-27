local bossID = EntityTable["Boss"]

boss_Master.upDown_Ticks = boss_Master.upDown_Ticks + 1
boss_Master.coolDown_Ticks = boss_Master.coolDown_Ticks + 1
boss_Master.fireRate_Ticks = boss_Master.fireRate_Ticks + 1
boss_Master.pipeRate_Ticks = boss_Master.pipeRate_Ticks + 1

local upDown_TimeElapsed = startTime + boss_Master.upDown_Ticks * (1/60)
local coolDown_TimeElapsed = startTime + boss_Master.coolDown_Ticks * (1/60)
local fireRate_TimeElapsed = startTime + boss_Master.fireRate_Ticks * (1/60)
local pipeRate_TimeElapsed = startTime + boss_Master.pipeRate_Ticks * (1/60)

function skillCD_Done()
    if (getDeltaTime(coolDown_TimeElapsed) >= boss_Master.skillCoolDown) then
        boss_Master.coolDown_Ticks = 0
        return true
    end
    return false
end

function canFire()
    if (getDeltaTime(fireRate_TimeElapsed) >= boss_Master.fireRate) then
        return true
    end
    return false
end

function canSpawnPipe()
    if (getDeltaTime(pipeRate_TimeElapsed) >= boss_Master.pipeRate) then
        return true
    end
    return false
end

-- type = 1 --> FIREBALL or basic projectile
-- type = 2 --> pipes
-- type = 3 --> something else
function fire(type)
    if (type == 1) then
        playSound("Gunshot_1")
        spawnLaser()
        boss_Master.fireRate_Ticks = 0
    end

    if (type == 2) then
        spawnPipe()
        boss_Master.pipeRate_Ticks = 0
    end    
end

if (game_state == PAUSED) then
    boss_Master.upDown_Ticks = 0
    boss_Master.coolDown_Ticks = 0
    boss_Master.fireRate_Ticks = 0
end

if (isBossAlive and (game_state == RUNNING or game_state == ENDED)) then

    -- do stuff here while boss is alive

    -----------------------------
    -----------------------------
    -- Hit by fireball --
    for i = 1, #fireBall_ID, 1 do
        if (hasCollided(bossID, fireBall_ID[i])) then
            destroyEntity(table.remove(fireBall_ID))
            getHealth(bossID).percent = getHealth(bossID).percent - player_Master.damage
            playSound("Ouch")
        end
    end

    if (getHealth(bossID).percent <= 0) then
        isBossAlive = false
        state = ENDED
        destroyEntity(EntityTable["Boss"])
        EntityTable["Boss"] = nil
        youWin()
    end
    -----------------------------
    -----------------------------

    -----------------------------
    -----------------------------
    -- Boss bobs up and down --
    getPosition(bossID).y = math.sin(getDeltaTime(upDown_TimeElapsed) * boss_Master.frequency) * boss_Master.amplitude + boss_Master.posY
    -----------------------------
    -----------------------------

    -----------------------------
    -----------------------------
    -- Check timers

    -- Cooldown
    if (skillCD_Done() and boss_Master.isCoolingDown) then
        -- TODO: pick an ability
        print("Boss abilities are up")
        boss_Master.isCoolingDown = false
    end
    
    -- Firerate
    if (canFire() and isPlayerAlive) then
        -- fire(1)
    end

    if (canSpawnPipe() and isPlayerAlive) then
        fire(2)
    end
    -----------------------------
    -----------------------------

    if (not isPlayerAlive) then
        stopSound("Gunshot_1")
    end
end

-- Boss AI goes here
-- State machine based on health and player positioning.