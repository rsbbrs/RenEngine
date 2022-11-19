-- Loads the spaceship sprite. --
if(loadImage("Spaceship", "sprites\\spaceship.png")) then
    print("Successfully loaded spaceship.png")
else
    print("Failed to load spaceship.png")
end

if(loadImage("Ball", "sprites\\ball.png")) then
    print("Successfully loaded ball.png")
else
    print("Failed to load ball.png")
end

-- Creates the spaceship entity with initial parameters. --
spaceship = createEntity()

getSprite(spaceship).name = "Spaceship"

getPosition(spaceship).x = 0.0
getPosition(spaceship).y = 0.0
getPosition(spaceship).z = 1.0

getRigidBody(spaceship).velocity.x = 0.0
getRigidBody(spaceship).velocity.y = 0.0

getRigidBody(spaceship).acceleration.x = 0
getRigidBody(spaceship).acceleration.y = 0

getRigidBody(spaceship).gravity.x = 0.0
getRigidBody(spaceship).gravity.y = 0.0

getRigidBody(spaceship).force.x = 0.0
getRigidBody(spaceship).force.y = 0.0

getRigidBody(spaceship).mass = 100.0
getRigidBody(spaceship).static = true

getScale(spaceship).scale = 25

-- Ball entity --
ball = createEntity()

getSprite(ball).name = "Ball"

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

getRigidBody(ball).mass = 100.0

getScale(ball).scale = 10

-- Loads and attaches the runtime script to the spaceship --
filepath = "scripts\\physics.lua"
if(loadScript("Spaceship", filepath, false)) then
    print("Successfully loaded physics.lua")
    getScript(spaceship).name = "Spaceship"
    getScript(spaceship).path = filePath(filepath)
else
    print("Failed to load physics.lua")
end