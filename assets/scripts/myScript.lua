local movementSpeed = 2
local turnSpeed = 2
local acceleration = 0.5
local time

if(keyPressed(input_code.w)) then
    position = getPosition(1)
    angle = math.rad(getRotation(1).angle + 90)
    velocity = getVelocity(1)
    getPosition(1).x = position.x + math.cos(angle) * movementSpeed
    getPosition(1).y = position.y + math.sin(angle) * movementSpeed

end

if(keyPressed(input_code.a)) then
    angle = getRotation(1).angle
    if(math.abs(angle) >= 360) then
        angle = 0
    end
    getRotation(1).angle = angle + turnSpeed
end

if(keyPressed(input_code.d)) then
    angle = getRotation(1).angle
    if(math.abs(angle) >= 360) then
        angle = 0
    end
    getRotation(1).angle = angle - turnSpeed
end

if(keyPressed(input_code.escape)) then
    quit()
end

if(keyPressed(input_code.enter)) then
    loadSound("Success", "sounds\\success.mp3")
    playSound("Success")
end