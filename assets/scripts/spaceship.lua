local maxSpeed = 8
local turnSpeed = 3
local acceleration = 0.4
local spaceship = 2

if(keyPressed(input_code.w)) then
    position = getPosition(spaceship)
    angle = math.rad(getRotation(spaceship).angle + 90)
    rigidBody = getRigidBody(spaceship)
    dt = 0.5
    print(rigidBody.velocity.x)
    getRigidBody(spaceship).velocity.x = math.min(velocity.x + (acceleration * dt), maxSpeed)
    getRigidBody(spaceship).velocity.y = math.min(velocity.y + (acceleration * dt), maxSpeed)
    print("Hello world")
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
    velocity = getRigidBody(spaceship).velocity
    acc = 0.1

    getRigidBody(spaceship).velocity.x = math.max(velocity.x - (acc * dt), 0)
    getRigidBody(spaceship).velocity.y = math.max(velocity.y - (acc * dt), 0)

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