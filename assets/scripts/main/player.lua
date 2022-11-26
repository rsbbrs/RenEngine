
-- Initiates physics simulation --
if( (keyPressed(input_code.enter) or keyPressed(input_code.r)) and game_state == PAUSED) then
    getRigidBody(player_ID).velocity.x = 0.0
    getRigidBody(player_ID).velocity.y = 0.0

    getRigidBody(player_ID).gravity.x = 0.0
    getRigidBody(player_ID).gravity.y = -9.81

    getRigidBody(player_ID).force.x = 20.0
    getRigidBody(player_ID).force.y = 22.0

    player_Input.hop = false
    player_Input.shoot = false

    game_state = RUNNING
    playSound("Boss_Theme")
end

if (game_state == RUNNING) then

    -----------------------------
    -----------------------------
            -- Inputs --
    -- Hopping --
    if (keyPressed(input_code.space) and not player_Input.hop) then
        getRigidBody(player_ID).velocity.y = player_Master.hopStrength
        getRotation(player_ID).angle = 180
        playSound("Flap")

        player_Master.rotate_dir = player_Master.rotate_dir * -1

        player_Input.hop = true
    end
    if (keyReleased(input_code.space) and player_Input.hop) then
        player_Input.hop = false
    end
    
    getRotation(player_ID).angle = getRotation(player_ID).angle + (1 * player_Master.rotate_dir)

    -- Shooting --
    if (keyPressed(input_code.f) and not player_Input.shoot) then
        playSound("Gunshot_2")
        -- TODO: Instantiate projectile
        player_Input.shoot = true
    end
    if (keyReleased(input_code.f) and player_Input.shoot) then
        player_Input.shoot = false
    end

    -- Ceiling and Repositioning --
    if (getPosition(player_ID).y > 100) then
        getPosition(player_ID).y = 100

        -- Prevents player from getting "glued"
        getRigidBody(player_ID).velocity.y = 0
    end

    if (getPosition(player_ID).x < player_Master.posX) then
        getRigidBody(player_ID).gravity.x = 20.0
    end
    
    if (getPosition(player_ID).x > player_Master.posX) then
        getPosition(player_ID).x = player_Master.posX
        getRigidBody(player_ID).gravity.x = 0.0
    end
    
    -----------------------------
    -----------------------------
    
    -----------------------------
    -----------------------------
    -- Death Condition --
    if (getPosition(player_ID).x <= -178 or getPosition(player_ID).y <= -103) then
        playSound("Explosion")
        playSound("Minecraft-OOF")
        
        isPlayerAlive = false
        game_state = ENDED

        print("\t-- You lose! ): --")

        destroyEntity(EntityTable["Player"])
        stopSound("Boss_Theme")
    end
    -----------------------------
    -----------------------------
end