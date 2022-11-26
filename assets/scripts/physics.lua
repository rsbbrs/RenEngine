-- Quits the engine --
if(keyPressed(input_code.escape)) then
    quit()
end

-- Initiates physics simulation --
if(keyPressed(input_code.enter)) then
    -- Ball 1 --
    getRigidBody(ball1).velocity.x = 0.0
    getRigidBody(ball1).velocity.y = 100.0

    getRigidBody(ball1).gravity.x = 0
    getRigidBody(ball1).gravity.y = -9.8

    getRigidBody(ball1).force.x = 0.0
    getRigidBody(ball1).force.y = 20.0

    -- Ball 2 --
    getRigidBody(ball2).velocity.x = -150.0
    getRigidBody(ball2).velocity.y = 100.0

    getRigidBody(ball2).gravity.x = 0
    getRigidBody(ball2).gravity.y = -9.8

    getRigidBody(ball2).force.x = -200.0
    getRigidBody(ball2).force.y = 20.0
end

-- Resets the simulation --
if(keyPressed(input_code.left_ctrl)) then
    -- Ball 1 --
    getPosition(ball1).x = -140.0
    getPosition(ball1).y = -50.0
    getPosition(ball1).z = 1.0

    getRigidBody(ball1).velocity.x = 0.0
    getRigidBody(ball1).velocity.y = 0.0
    
    getRigidBody(ball1).acceleration.x = 0.0
    getRigidBody(ball1).acceleration.y = 0.0

    getRigidBody(ball1).gravity.x = 0.0
    getRigidBody(ball1).gravity.y = 0.0

    getRigidBody(ball1).force.x = 0.0
    getRigidBody(ball1).force.y = 0.0

    -- Ball 2 --
    getPosition(ball2).x = 140.0
    getPosition(ball2).y = -50.0
    getPosition(ball2).z = 1.0

    getRigidBody(ball2).velocity.x = 0.0
    getRigidBody(ball2).velocity.y = 0.0
    
    getRigidBody(ball2).acceleration.x = 0.0
    getRigidBody(ball2).acceleration.y = 0.0

    getRigidBody(ball2).gravity.x = 0.0
    getRigidBody(ball2).gravity.y = 0.0

    getRigidBody(ball2).force.x = 0.0
    getRigidBody(ball2).force.y = 0.0
end