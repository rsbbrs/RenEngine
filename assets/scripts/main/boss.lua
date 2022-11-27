local bossID = EntityTable["Boss"]

if (game_state == PAUSED) then
    boss_Master.upDown_Ticks = 0
end

boss_Master.upDown_Ticks = boss_Master.upDown_Ticks + 1
upDown_TimeElapsed = startTime + boss_Master.upDown_Ticks * (1/60)

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
end