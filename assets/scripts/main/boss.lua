local bossID = EntityTable["Boss"]

boss_Master.upDown_Ticks = boss_Master.upDown_Ticks + 1
boss_Master.coolDown_Ticks = boss_Master.coolDown_Ticks + 1
local upDown_TimeElapsed = startTime + boss_Master.upDown_Ticks * (1/60)
local coolDown_TimeElapsed = startTime + boss_Master.coolDown_Ticks * (1/60)

function skillCD_Done()
    if (getDeltaTime(coolDown_TimeElapsed) >= boss_Master.skillCoolDown) then
        boss_Master.coolDown_Ticks = 0
        return true
    end
    return false
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
        destroyEntity(bossID)
        bossID = nil
        isBossAlive = false
    end
    -----------------------------
    -----------------------------

    -----------------------------
    -----------------------------
    -- Boss moves up and down --
    getPosition(bossID).y = math.sin(getDeltaTime(upDown_TimeElapsed) * boss_Master.frequency) * boss_Master.amplitude + boss_Master.posY
    -----------------------------
    -----------------------------

    -----------------------------
    -----------------------------
    -- Check cooldown timer
    if (skillCD_Done() and boss_Master.isCoolingDown) then
        -- TODO: pick an ability
        print("Boss abilities are up")
        boss_Master.isCoolingDown = false
    end
    
    -----------------------------
    -----------------------------
end