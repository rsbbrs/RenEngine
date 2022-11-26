-- Loads the ball sprite.
if(loadImage("Ball", "sprites\\ball.png")) then
    print("Successfully loaded ball.png")
else
    print("Failed to load ball.png")
end

-- Ball 1 --
ball1 = createEntity()

getSprite(ball1).name = "Ball"

getPosition(ball1).x = -140.0
getPosition(ball1).y = -50.0
getPosition(ball1).z = 1.0

getRigidBody(ball1).velocity.x = 0.0
getRigidBody(ball1).velocity.y = 0.0

getRigidBody(ball1).acceleration.x = 0
getRigidBody(ball1).acceleration.y = 0

getRigidBody(ball1).gravity.x = 0.0
getRigidBody(ball1).gravity.y = 0.0

getRigidBody(ball1).force.x = 0.0
getRigidBody(ball1).force.y = 0.0

getRigidBody(ball1).mass = 10.0

getRigidBody(ball1).static = false

getScale(ball1).scale = 10

-- Ball 2 --
ball2 = createEntity()

getSprite(ball2).name = "Ball"

getPosition(ball2).x = 140.0
getPosition(ball2).y = -50.0
getPosition(ball2).z = 1.0

getRigidBody(ball2).velocity.x = 0.0
getRigidBody(ball2).velocity.y = 0.0

getRigidBody(ball2).acceleration.x = 0
getRigidBody(ball2).acceleration.y = 0

getRigidBody(ball2).gravity.x = 0.0
getRigidBody(ball2).gravity.y = 0.0

getRigidBody(ball2).force.x = 0.0
getRigidBody(ball2).force.y = 0.0

getRigidBody(ball2).mass = 10.0

getRigidBody(ball2).static = true

getScale(ball2).scale = 10

-- Loads and attaches the runtime script to the spaceship --
filepath = "scripts\\physics.lua"
if(loadScript("physics", filepath, false)) then
    print("Successfully loaded physics.lua")
    getScript(ball1).name = "physics"
    getScript(ball2).name = "physics"

    getScript(ball1).path = filePath(filepath)
    getScript(ball2).path = filePath(filepath)
else
    print("Failed to load physics.lua")
end