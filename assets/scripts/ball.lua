-- Quits the engine --
if(keyPressed(input_code.escape)) then
    quit()
end

-- Initiates physics simulation --
if(keyPressed(input_code.enter)) then
    getRigidBody(ball).velocity.x = 0.0
    getRigidBody(ball).velocity.y = 150.0

    getRigidBody(ball).gravity.x = 0
    getRigidBody(ball).gravity.y = -9.8

    getRigidBody(ball).force.x = 0.0
    getRigidBody(ball).force.y = 20.0

    getRigidBody(ball).mass = 5.0
end

-- Resets the simulation --
if(keyPressed(input_code.tab)) then
    getPosition(ball).x = -140.0
    getPosition(ball).y = -50.0
    getPosition(ball).z = 1.0

    getRigidBody(ball).velocity.x = 0.0
    getRigidBody(ball).velocity.y = 0.0
    
    getRigidBody(ball).acceleration.x = 0
    getRigidBody(ball).acceleration.y = 0

    getRigidBody(ball).gravity.x = 0.0
    getRigidBody(ball).gravity.y = 0.0

    getRigidBody(ball).force.x = 0.0
    getRigidBody(ball).force.y = 0.0
end