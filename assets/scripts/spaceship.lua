local maxSpeed = 8
local turnSpeed = 3
local acceleration = 0.4
local spaceship = 2
local laserSpeed = 8

if(not keyPressed(input_code.space)) then
    wasPressed = false
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

if(keyPressed(input_code.w)) then
    angle = math.rad(getRotation(spaceship).angle + 90)
    getRigidBody(spaceship).force.x = 50
    getRigidBody(spaceship).force.y = 50
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

if(keyPressed(input_code.space) and wasPressed == false) then
    playSound("Gunshot")
    wasPressed = true
    newID = createEntity()

    getSprite(newID).name = "Laser"
    getPosition(newID).x = getPosition(spaceship).x
    getPosition(newID).y = getPosition(spaceship).y
    getPosition(newID).z = getPosition(spaceship).z
    getScale(newID).scale = 10
    getRotation(newID).angle = (getRotation(spaceship).angle + 90)
end

if(not keyPressed(input_code.w)) then
    getRigidBody(spaceship).force.x = -50
    getRigidBody(spaceship).force.y = -50
end