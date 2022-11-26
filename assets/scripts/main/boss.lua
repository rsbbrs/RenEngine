
if (isBossAlive) then

    -- do stuff here while boss is alive

    -----------------------------
    -----------------------------
    -- Hit by fireball --
    for i = 1, #fireBall_ID, 1 do
        if (hasCollided(EntityTable["Boss"],fireBall_ID[i])) then
            destroyEntity(table.remove(fireBall_ID))
            getHealth(EntityTable["Boss"]).percent = getHealth(EntityTable["Boss"]).percent - player_Master.damage
            playSound("Ouch")
        end
    end

    if (getHealth(EntityTable["Boss"]).percent <= 0) then
        destroyEntity(EntityTable["Boss"])
        EntityTable["Boss"] = nil
    end
    -----------------------------
    -----------------------------
end