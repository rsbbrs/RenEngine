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
        boss_Master.fireRate_Ticks = 0
        return true
    end
    return false
end

function canSpawnPipe()
    if (getDeltaTime(pipeRate_TimeElapsed) >= boss_Master.pipeRate) then
        boss_Master.pipeRate_Ticks = 0
        return true
    end
    return false
end

-- type = 1 --> Laser
-- type = 2 --> pipes
-- type = 3 --> something else
function fire(type)
    
    -- Fire laser
    if (type == 1 and canFire()) then
        playSound("Gunshot_1")
        spawnLaser()
    end

    -- Spawn pipe
    if (type == 2 and canSpawnPipe()) then
        spawnPipe()
    end 
end

if (game_state == PAUSED) then
    boss_Master.upDown_Ticks = 0
    boss_Master.coolDown_Ticks = 0
    boss_Master.fireRate_Ticks = 0
    boss_Master.pipeRate_Ticks = 0
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
    if (boss_Master.isBobbing) then
        getPosition(bossID).y = math.sin(getDeltaTime(upDown_TimeElapsed) * boss_Master.frequency) * boss_Master.amplitude + boss_Master.posY
    end
    -----------------------------
    -----------------------------

    -----------------------------
    -----------------------------
    -- Check timers

    -- Cooldown
    -- if (skillCD_Done() and boss_Master.isCoolingDown and isPlayerAlive) then
    --     -- TODO: pick an ability
    --     print("Boss abilities are up")
    --     boss_Master.isCoolingDown = false
    -- end
    -----------------------------
    -----------------------------

    -----------------------------
    -----------------------------
    -- Activate phase 1
    if (getHealth(boss_ID).percent > 75.0) then
        boss_Master.phase = 1
    end

    -- Activate phase 2
    if (getHealth(boss_ID).percent <= 75.0 and getHealth(boss_ID).percent > 50.0) then
        boss_Master.phase = 2
    end
    -----------------------------
    -----------------------------

    if (not isPlayerAlive) then
        stopSound("Gunshot_1")
    end

end -- End of condition

-- Boss AI goes here
-- State machine based on health and player positioning.

function retreating()
    if (not boss_Master.retreated) then
        if (getPosition(boss_ID).y <= 10 and getPosition(boss_ID).y >= -10) then
            boss_Master.isBobbing = false
            getRigidBody(boss_ID).gravity.x = 5.0
            getRigidBody(boss_ID).force.x = 10.0
        end
    end
end

function retreatReturn()
    getPosition(boss_ID).y = 0

    getRigidBody(boss_ID).gravity.x = -8.0
    getRigidBody(boss_ID).force.x = 10.0
end


-----------------------------
-----------------------------
    -- Phase handling --

-- phase 1
if (boss_Master.phase == 1) then
    fire(1)
end

-- Phase 2
if (boss_Master.phase == 2) then

    if (not skillCD_Done() and not boss_Master.retreating and not boss_Master.returning and not boss_Master.retreated) then
        fire(1)
    end

    if (skillCD_Done() and not boss_Master.retreated) then
        boss_Master.retreating = true
        boss_Master.tempHealth = getHealth(boss_ID).percent
    end

    if (boss_Master.retreating) then
        getHealth(boss_ID).percent = boss_Master.tempHealth
        retreating()
        if (getPosition(boss_ID).x >= 300) then
            getPosition(boss_ID).x = 300
            getRigidBody(boss_ID).gravity.x = 0.0
            getRigidBody(boss_ID).velocity.x = 0.0
            getRigidBody(boss_ID).force.x = 0.0
            boss_Master.retreated = true
            boss_Master.retreating = false
            boss_Master.isBobbing = true
            boss_Master.coolDown_Ticks = 0

            boss_Master.retreatedCounter  = boss_Master.retreatedCounter + 1
            pipe_Master.pipeGap = pipe_Master.pipeGap - 5

            -- For now 10 is the cap
            -- Ai gets too smart after that
            if (boss_Master.retreatedCounter >= 10) then
                boss_Master.retreatedCounter = 10
            end
            if (pipe_Master.pipeGap <= 25) then
                pipe_Master.pipeGap = 25
            end

        end
    end

    if (boss_Master.retreated and not skillCD_Done()) then

        fire(2)
        -- approximate where player is located and fire lasers at them
        if ( (getBossEyeLevel() <= getPosition(player_ID).y + 10 + boss_Master.retreatedCounter) and (getBossEyeLevel() >= getPosition(player_ID).y - 10 + boss_Master.retreatedCounter)) then
            boss_Master.fireRate = 0.15
            fire(1)
        end

        -- if ( (getBossEyeLevel() >= getPosition(player_ID).y - 30)) then
        --     boss_Master.fireRate = 0.15
        --     fire(1)
        -- end
    end

    if (boss_Master.retreated and skillCD_Done() and not boss_Master.returning) then
        -- Return back to original position
        boss_Master.returning = true
        boss_Master.retreated = false
        retreatReturn()
    end

    if (boss_Master.returning) then
        if (getPosition(boss_ID).x <= boss_Master.posX) then
            
            boss_Master.fireRate = boss_Master.temp_fireRate
            getPosition(boss_ID).x = boss_Master.posX
            getRigidBody(boss_ID).gravity.x = 0.0
            getRigidBody(boss_ID).velocity.x = 0.0
            getRigidBody(boss_ID).force.x = 0.0
            boss_Master.upDown_Ticks = 0
            boss_Master.returning = false
            boss_Master.retreated = false
            boss_Master.retreating = false
        end
    end

end

-----------------------------
-----------------------------