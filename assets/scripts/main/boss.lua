local bossID = EntityTable["Boss"]
local playerID = EntityTable["Player"]

boss_Master.upDown_Ticks = boss_Master.upDown_Ticks + 1
boss_Master.coolDown_Ticks = boss_Master.coolDown_Ticks + 1
boss_Master.fireRate_Ticks = boss_Master.fireRate_Ticks + 1
boss_Master.pipeRate_Ticks = boss_Master.pipeRate_Ticks + 1
boss_Master.ballRate_Ticks = boss_Master.ballRate_Ticks + 1

local upDown_TimeElapsed = startTime + boss_Master.upDown_Ticks * (1/60)
local coolDown_TimeElapsed = startTime + boss_Master.coolDown_Ticks * (1/60)
local fireRate_TimeElapsed = startTime + boss_Master.fireRate_Ticks * (1/60)
local pipeRate_TimeElapsed = startTime + boss_Master.pipeRate_Ticks * (1/60)
local ballRate_TimeElapsed = startTime + boss_Master.ballRate_Ticks * (1/60)

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

function canFireBall()
    if (getDeltaTime(ballRate_TimeElapsed) >= boss_Master.ballRate) then
        boss_Master.ballRate_Ticks = 0
        return true
    end
    return false
end

-- type = 1 --> Laser
-- type = 2 --> pipes
-- type = 3 --> something else
function fire(type, offset, angle, velocity_Y)
    
    -- Fire laser
    if (type == 1 and canFire()) then
        playSound("Gunshot_1")
        spawnLaser(angle, velocity_Y)
    end

    -- Spawn pipe
    if (type == 2 and canSpawnPipe()) then
        spawnPipe(offset)
    end 

    if(type == 3 and canFireBall()) then
        spawnBall()
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
    if (boss_Master.isBobbing and not boss_Master.retreated) then
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
    if (getHealth(bossID).percent > 75.0) then
        boss_Master.phase = 1

        -- phase 0 does nothing
        if (not isPlayerAlive) then
            boss_Master.phase = 0
        end
    end

    -- Activate phase 2
    if (getHealth(bossID).percent <= 75.0 and getHealth(bossID).percent > 50.0) then
        boss_Master.phase = 2

        -- phase 0 does nothing
        if (not isPlayerAlive) then
            boss_Master.phase = 0
        end
    end

    -- Activate phase 3
    -----------------------------
    -----------------------------
    if(getHealth(bossID).percent <= 50) then
        boss_Master.phase = 3

        if (not isPlayerAlive) then
            boss_Master.phase = 0
        end
    end

    if (not isPlayerAlive) then
        stopSound("Gunshot_1")
    end

end -- End of condition

function retreating()
    if (not boss_Master.retreated) then
        if (getPosition(bossID).y <= 10 and getPosition(bossID).y >= -10) then
            boss_Master.isBobbing = false
            getRigidBody(bossID).gravity.x = 5.0
            getRigidBody(bossID).force.x = 10.0
        end
    end
end

function retreatReturn()
    getPosition(bossID).y = 0

    getRigidBody(bossID).gravity.x = -8.0
    getRigidBody(bossID).force.x = 10.0
end


-----------------------------
-----------------------------
    -- Phase handling --

-- phase 1
if (boss_Master.phase == 1) then
    fire(1, 0, boss_Master.angle, 0.0)
end

-- Phase 2
if (boss_Master.phase == 2) then

    if (not skillCD_Done() and not boss_Master.retreating and not boss_Master.returning and not boss_Master.retreated) then
        fire(1, 0, boss_Master.angle, 0.0)
    end

    if (skillCD_Done() and not boss_Master.retreated) then
        boss_Master.retreating = true
        boss_Master.tempHealth = getHealth(bossID).percent
    end

    -- Boss retreats off screen.
    if (boss_Master.retreating) then
        getHealth(bossID).percent = boss_Master.tempHealth
        retreating()
        if (getPosition(bossID).x >= 300) then
            getPosition(bossID).x = 300
            getRigidBody(bossID).gravity.x = 0.0
            getRigidBody(bossID).velocity.x = 0.0
            getRigidBody(bossID).force.x = 0.0
            boss_Master.retreated = true
            boss_Master.retreating = false
            boss_Master.isBobbing = true
            boss_Master.coolDown_Ticks = 0

            boss_Master.retreatedCounter  = boss_Master.retreatedCounter + 1
            pipe_Master.pipeGap = pipe_Master.pipeGap - 3
            pipe_Master.pipeSpeed = pipe_Master.pipeSpeed - 2.0

            -- For now 10 is the cap
            if (boss_Master.retreatedCounter >= 10) then
                boss_Master.retreatedCounter = 10
            end
            if (pipe_Master.pipeGap <= 30) then
                pipe_Master.pipeGap = 30
            end

            if (isPlayerAlive) then
                spawnCrossHair()
            end
            
            boss_Master.upDown_Ticks = 0
        end
    end -- End of boss retreating.

    -- Boss retreated, handle aim ai and other stuff here --
    if (boss_Master.retreated and not skillCD_Done() and isPlayerAlive) then

        direction = 0
        
        -- Random pipe spawning at this phase.
        fire(2, math.random(50, 150), 0, 0.0)
        getPosition(EntityTable["Crosshair"]).y = getBossEyeLevel()

        -- Readjust boss to aim towards player
        if (getBossEyeLevel() > getPosition(EntityTable["Player"]).y) then
            direction = 1
            getRigidBody(bossID).gravity.y = -1.0 + (-1.0 * boss_Master.retreatedCounter)
            getRigidBody(bossID).force.y = 10.0

            if (getRigidBody(bossID).gravity.y >= 15) then
                getRigidBody(bossID).gravity.y = 15.0
            end
        end

        if (getBossEyeLevel() <= getPosition(EntityTable["Player"]).y) then
            direction = -1
            getRigidBody(bossID).gravity.y = 1.0 + (1.0 * boss_Master.retreatedCounter)
            getRigidBody(bossID).force.y = 10.0

            if (getRigidBody(bossID).gravity.y >= 15) then
                getRigidBody(bossID).gravity.y = 15.0
            end
        end

        -- getPosition(bossID).y = math.sin(getDeltaTime(upDown_TimeElapsed) * boss_Master.frequency) * 30 + getPosition(EntityTable["Player"]).y

        -- approximate where player is located and fire lasers at them
        if ( (getBossEyeLevel() <= getPosition(EntityTable["Player"]).y + 5) and (getBossEyeLevel() >= getPosition(EntityTable["Player"]).y - 5)) then
            boss_Master.fireRate = 0.5
            fire(1, 0, boss_Master.angle, 0.0)
            

            if (direction == 1) then
                getRigidBody(bossID).velocity.y = getPosition(bossID).y / (0.5 + (1.0 * boss_Master.retreatedCounter))
            end

            if (direction == -1) then
                getRigidBody(bossID).velocity.y = getPosition(bossID).y / (0.5 + (1.0 * boss_Master.retreatedCounter)) * direction
            end
        end

    end -- End of boss retreated, handle aim ai and other stuff here --

    if (boss_Master.retreated and skillCD_Done() and not boss_Master.returning) then
        -- Return back to original position
        boss_Master.returning = true
        boss_Master.retreated = false
        destroyEntity(EntityTable["Crosshair"])
        EntityTable["Crosshair"] = nil
        retreatReturn()
    end

    if (boss_Master.returning) then
        getRigidBody(bossID).gravity.y = 0.0
        getRigidBody(bossID).acceleration.y = 0.0
        getRigidBody(bossID).force.y = 0.0
        getRigidBody(bossID).velocity.y = 0.0

        if (getPosition(bossID).x <= boss_Master.posX) then
            
            boss_Master.fireRate = boss_Master.temp_fireRate
            getPosition(bossID).x = boss_Master.posX
            getRigidBody(bossID).gravity.x = 0.0
            getRigidBody(bossID).velocity.x = 0.0
            getRigidBody(bossID).force.x = 0.0
            getRigidBody(bossID).acceleration.x = 0.0
            boss_Master.upDown_Ticks = 0
            boss_Master.returning = false
            boss_Master.retreated = false
            boss_Master.retreating = false
        end
    end

end

-- Phase 3
if(boss_Master.phase == 3) then
    boss_Master.fireRate = 0.85

    -- Decision tree chooses next type of attack.
    bossPos = getBossEyeLevel()
    playerPos = getPosition(playerID).y

    opposite = getPosition(playerID).y - getPosition(bossID).y
    adjacent = getPosition(playerID).x - getPosition(bossID).x

    -- Player is above boss
    if(playerPos > bossPos) then
        -- If player is above boss level by 50
        -- Rapidly shoot upward to keep player in range.
        -- If not, spawn pipes near center of the screen
        -- to try and bring player's position further down.
        if(playerPos - bossPos > 75) then
            -- Fire burst to bring player down.
            boss_Master.fireRate = 0.4
            fire(1, 0, boss_Master.angle + (math.atan(opposite, adjacent) * 180/math.pi), (playerPos - bossPos))
        else
            fire(2, math.random(50, 100), 0.0, 0.0)
            fire(1, 0, boss_Master.angle, 0.0)
        end
    -- Player is below boss.
    elseif(playerPos < bossPos) then
        -- Player is below boss eye level by 50
        if(bossPos - playerPos > 75) then
            -- Fire burst to bring player up.
            boss_Master.fireRate = 0.4
            fire(1, 0, boss_Master.angle + (math.atan(opposite, adjacent) * 180/math.pi), (playerPos - bossPos))
            fire(3, 0, 0, 0)
        else
            fire(1, 0, boss_Master.angle, 0.0)
        end
    end
end
-----------------------------
-----------------------------