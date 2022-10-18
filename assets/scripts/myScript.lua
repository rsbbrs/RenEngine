local movementSpeed = 2
local turnSpeed = 2

if(keyPressed(input_code.w)) then
    position = getPosition(1)
    angle = math.rad(getRotation(1).angle + 90)
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

if(getPosition(1).x < -100) then
    position = getPosition(1)
    getPosition(1).x = winWidth() + 100
end