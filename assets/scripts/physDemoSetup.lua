-- Loads the ball sprite. --
if(loadImage("Ball", "sprites\\ball.png")) then
    print("Successfully loaded ball.png")
else
    print("Failed to load ball.png")
end

-- Creates the ball entity with initial parameters. --
ball = createEntity()

getSprite(ball).name = "Ball"

getPosition(ball).x = -140.0
getPosition(ball).y = -50.0
getPosition(ball).z = 1.0

getScale(ball).scale = 10

-- Loads and attaches the runtime script to the ball --
filepath = "scripts\\ball.lua"
if(loadScript("Ball", filepath, false)) then
    print("Successfully loaded ball.lua")
    getScript(ball).name = "Ball"
    getScript(ball).path = filePath(filepath)
else
    print("Failed to load ball.lua")
end