if(keyPressed(input_code.w)) then
    ypos = getPosition(1).y
    getPosition(1).y = ypos + 1
end

if(keyPressed(input_code.s)) then
    ypos = getPosition(1).y
    getPosition(1).y = ypos - 1
end

if(keyPressed(input_code.d)) then
    xpos = getPosition(1).x
    getPosition(1).x = xpos + 1
end

if(keyPressed(input_code.a)) then
    xpos = getPosition(1).x
    getPosition(1).x = xpos - 1
end

if(keyPressed(input_code.up) and (getScale(1).scale < 100)) then
    scale = getScale(1).scale
    getScale(1).scale = scale + 1
end

if(keyPressed(input_code.down) and (getScale(1).scale > 0)) then
    scale = getScale(1).scale
    getScale(1).scale = scale - 1
end

if(keyPressed(input_code.left)) then
    angle = getRotation(1).angle
    getRotation(1).angle = angle + 1
end

if(keyPressed(input_code.right)) then
    angle = getRotation(1).angle
    getRotation(1).angle = angle - 1
end

if(keyPressed(input_code.escape)) then
    quit()
end

if(keyPressed(input_code.enter)) then
    loadSound("Success", "sounds\\success.mp3")
    playSound("Success")
end