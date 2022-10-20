local movementSpeed = 2
local turnSpeed = 3
local acceleration = 0.5
local initTime = 0

if(keyPressed(input_code.w)) then
    position = getPosition(1)
    angle = math.rad(getRotation(1).angle + 90)
    velocity = getVelocity(1)
    dt = 0.5
    getPosition(1).x = position.x + (math.cos(angle) * velocity.x * dt)
    getPosition(1).y = position.y + (math.sin(angle) * velocity.y * dt)

    getVelocity(1).x = math.min(velocity.x + (acceleration * dt), 10)
    getVelocity(1).y = math.min(velocity.y + (acceleration * dt), 10)

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