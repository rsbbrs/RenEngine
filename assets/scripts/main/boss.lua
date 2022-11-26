
if (isBossAlive) then

    -- do stuff here while boss is alive

    -----------------------------
    -----------------------------
    -- Hit by fireball --
    for i = 1, #fireBall_ID, 1 do
        if (hasCollided(EntityTable["Boss"],fireBall_ID[i])) then
            destroyEntity(table.remove(fireBall_ID))
            playSound("Ouch")
        end
    end
    -----------------------------
    -----------------------------
end