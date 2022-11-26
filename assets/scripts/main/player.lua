
-- Initiates physics simulation --
if(keyPressed(input_code.enter) and game_state == PAUSED) then


    getRigidBody(player_ID).velocity.x = 0.0
    getRigidBody(player_ID).velocity.y = 0.0

    getRigidBody(player_ID).gravity.x = 0
    getRigidBody(player_ID).gravity.y = -9.8

    getRigidBody(player_ID).force.x = 0.0
    getRigidBody(player_ID).force.y = 20.0

    game_state = RUNNING
end

if (game_state == RUNNING) then

    if (keyPressed(input_code.space) and not player_Input.hop) then
        print("Space pressed")
        player_Input.hop = true
        
    end

    if (keyReleased(input_code.space) and player_Input.hop) then
        player_Input.hop = false
    end
end