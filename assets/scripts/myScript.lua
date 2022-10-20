local maxSpeed = 8
local turnSpeed = 3
local acceleration = 0.4
local initTime = 0

if(keyPressed(input_code.w)) then
    position = getPosition(1)
    mvAngle = math.rad(getRotation(1).angle + 90)
    velocity = getVelocity(1)
    dt = 0.5
    getPosition(1).x = position.x + (math.cos(mvAngle) * velocity.x * dt)
    getPosition(1).y = position.y + (math.sin(mvAngle) * velocity.y * dt)

    getVelocity(1).x = math.min(velocity.x + (acceleration * dt), maxSpeed)
    getVelocity(1).y = math.min(velocity.y + (acceleration * dt), maxSpeed)

    getRotation(2).angle = getRotation(1).angle + 90
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

if(not keyPressed(input_code.w)) then
    position = getPosition(1)
    velocity = getVelocity(1);
    mvAngle = math.rad(getRotation(2).angle)
    acc = 0.1

    getPosition(1).x = position.x + (math.cos(mvAngle) * velocity.x * dt)
    getPosition(1).y = position.y + (math.sin(mvAngle) * velocity.y * dt)

    getVelocity(1).x = math.max(velocity.x - (acc * dt), 0)
    getVelocity(1).y = math.max(velocity.y - (acc * dt), 0)
end