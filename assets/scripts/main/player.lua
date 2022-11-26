
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