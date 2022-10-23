local maxSpeed = 8
local turnSpeed = 3
local acceleration = 0.4
local spaceship = 2

if(keyPressed(input_code.w)) then
    position = getPosition(spaceship)
    angle = math.rad(getRotation(spaceship).angle + 90)
    velocity = getVelocity(spaceship)
    dt = 0.5

    getVelocity(spaceship).x = math.min(velocity.x + (acceleration * dt), maxSpeed)
    getVelocity(spaceship).y = math.min(velocity.y + (acceleration * dt), maxSpeed)

    getPosition(spaceship).x = position.x + (math.cos(angle) * velocity.x * dt)
    getPosition(spaceship).y = position.y + (math.sin(angle) * velocity.y * dt)

    mvAngle = angle
end

if(keyPressed(input_code.a)) then
    angle = getRotation(spaceship).angle
    if(math.abs(angle) >= 360) then
        angle = 0
    end
    getRotation(spaceship).angle = angle + turnSpeed
end

if(keyPressed(input_code.d)) then
    angle = getRotation(spaceship).angle
    if(math.abs(angle) >= 360) then
        angle = 0
    end
    getRotation(spaceship).angle = angle - turnSpeed
end

if(keyPressed(input_code.escape)) then
    quit()
end

if(not keyPressed(input_code.w)) then
    position = getPosition(spaceship)
    velocity = getVelocity(spaceship)
    acc = 0.1

    getVelocity(spaceship).x = math.max(velocity.x - (acc * dt), 0)
    getVelocity(spaceship).y = math.max(velocity.y - (acc * dt), 0)

    getPosition(spaceship).x = position.x + (math.cos(mvAngle) * velocity.x * dt)
    getPosition(spaceship).y = position.y + (math.sin(mvAngle) * velocity.y * dt)
end

if(getPosition(spaceship).x < -185) then
    getPosition(spaceship).x = 185
elseif(getPosition(spaceship).x > 185) then
    getPosition(spaceship).x = -185
end

if(getPosition(spaceship).y < -121) then
    getPosition(spaceship).y = 121
elseif(getPosition(spaceship).y > 121) then
    getPosition(spaceship).y = -121
end