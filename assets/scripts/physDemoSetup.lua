-- Loads the ball sprite. --
if(loadImage("Ball", "sprites\\ball.png")) then
    print("Successfully loaded ball.png")
else
    print("Failed to load ball.png")
end

-- Creates the ball entity with initial parameters. --
ball = createEntity()

getSprite(ball).name = "Ball"

getPosition(ball).x = 0.0
getPosition(ball).y = 0.0
getPosition(ball).z = 1.0

getScale(ball).scale = 10

-- Loads and attaches the runtime script to the ball --
if(loadScript("Ball", "scripts\\ball.lua", false)) then
    print("Successfully loaded ball.lua")
else
    print("Failed to load ball.lua")