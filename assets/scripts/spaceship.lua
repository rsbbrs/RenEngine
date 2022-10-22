local maxSpeed = 8
local turnSpeed = 3
local acceleration = 0.4

if(keyPressed(input_code.w)) then
    position = getPosition(1)
    angle = math.rad(getRotation(1).angle + 90)
    velocity = getVelocity(1)
    dt = 0.5

    getVelocity(1).x = math.min(velocity.x + (acceleration * dt), maxSpeed)
    getVelocity(1).y = math.min(velocity.y + (acceleration * dt), maxSpeed)

    getPosition(1).x = position.x + (math.cos(angle) * velocity.x * dt)
    getPosition(1).y = position.y + (math.sin(angle) * velocity.y * dt)

    mvAngle = angle
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
    velocity = getVelocity(1)
    acc = 0.1

    getVelocity(1).x = math.max(velocity.x - (acc * dt), 0)
    getVelocity(1).y = math.max(velocity.y - (acc * dt), 0)

    getPosition(1).x = position.x + (math.cos(mvAngle) * velocity.x * dt)
    getPosition(1).y = position.y + (math.sin(mvAngle) * velocity.y * dt)
end

if(getPosition(1).x < -185) then
    getPosition(1).x = 185
elseif(getPosition(1).x > 185) then
    getPosition(1).x = -185
end

if(getPosition(1).y < -121) then
    getPosition(1).y = 121
elseif(getPosition(1).y > 121) then
    getPosition(1).y = -121
end

if(keyPressed(input_code.space)) then
    position = getPosition(1)
    angle = getRotation(1).angle
    if(math.abs(angle) >= 360) then
        angle = 0
    end

    blasterEntity[arrIndex] = createEntity()    
    print(createEntity())

    arrIndex = arrIndex + 1
end