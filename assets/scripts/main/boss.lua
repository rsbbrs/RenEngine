local bossID = EntityTable["Boss"]


if (isBossAlive and game_state == RUNNING) then

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
    getPosition(bossID).y = math.sin(currentTime * boss_Master.frequency) * boss_Master.amplitude + boss_Master.posY
    -----------------------------
    -----------------------------
end