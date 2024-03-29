-- Keeps track of existing significant entities (i.e., player and boss)
EntityTable = {}
-- EntityID Management for projectiles
fireBall_ID = {}
laser_ID = {}
pipe_ID = {}
ball_ID = {}

-----------------------------
-----------------------------
-- Create Player Entity --
-- keeps track of player input
-- any new input needs to be recorded on this table
player_Input = {
    hop = false,
    shoot = false
}
createBackground()
createPlayer()
createBoss()
-----------------------------
-----------------------------

-----------------------------
-----------------------------
-- Spawn Fireball --
function spawnFireball()
    fb = createEntity()

    table.insert(fireBall_ID, 1, fb)

    getSprite(fb).name = "Fireball"

    getPosition(fb).x = getPosition(player_ID).x + 3.0
    getPosition(fb).y = getPosition(player_ID).y
    getPosition(fb).z = 0.6

    getRigidBody(fb).velocity.x = 250.0
    getRigidBody(fb).velocity.y = 0.0
    getRigidBody(fb).acceleration.x = 0.0
    getRigidBody(fb).acceleration.y = 0.0
    getRigidBody(fb).gravity.x = 0.0
    getRigidBody(fb).gravity.y = 0.0
    getRigidBody(fb).force.x = 0.0
    getRigidBody(fb).force.y = 0.0
    getRigidBody(fb).mass = 10.0

    getRigidBody(fb).static = true
    getRigidBody(fb).trueRB = false
    
    getScale(fb).scale = 8

    getRigidBody(fb).min.x = 0.0
    getRigidBody(fb).min.y = 0.0
    getRigidBody(fb).max.x = 0.0
    getRigidBody(fb).max.y = 0.0
    getBoxCollider(fb, getRigidBody(fb).min, getRigidBody(fb).max)

end
-----------------------------
-----------------------------

-----------------------------
-----------------------------
-- Spawn Boss laser --
function spawnLaser(angle, velocity_Y)
    laser = createEntity()

    table.insert(laser_ID, 1, laser)

    getSprite(laser).name = "Laser"

    getPosition(laser).x = getPosition(boss_ID).x - 10.0
    getPosition(laser).y = getPosition(boss_ID).y + 20
    getPosition(laser).z = 0.6
    getRotation(laser).angle = angle
    getRigidBody(laser).velocity.x = -250.0
    getRigidBody(laser).velocity.y = velocity_Y
    getRigidBody(laser).acceleration.x = 0.0
    getRigidBody(laser).acceleration.y = 0.0
    getRigidBody(laser).gravity.x = 0.0
    getRigidBody(laser).gravity.y = 0.0
    getRigidBody(laser).force.x = 0.0
    getRigidBody(laser).force.y = 0.0
    getRigidBody(laser).mass = 10.0

    getRigidBody(laser).static = true
    getRigidBody(laser).trueRB = false
    
    getScale(laser).scale = 25

    getRigidBody(laser).min.x = 0.0
    getRigidBody(laser).min.y = 0.0
    getRigidBody(laser).max.x = 0.0
    getRigidBody(laser).max.y = 0.0
    getBoxCollider(laser, getRigidBody(laser).min, getRigidBody(laser).max)
end
-----------------------------
-----------------------------

-----------------------------
-----------------------------
-- Spawn Pipe --
function spawnPipe(offset)
    pipe = createEntity()
    pipe2 = createEntity()

    table.insert(pipe_ID, 1, pipe)
    table.insert(pipe_ID, 1, pipe2)

    --offset = math.random(20, 170)

    getSprite(pipe).name = "Pipe"

    getPosition(pipe).x = 200
    getPosition(pipe).y = 190 - offset
    getPosition(pipe).z = 0.5

    getRotation(pipe).angle = 180

    getRigidBody(pipe).velocity.x = pipe_Master.pipeSpeed
    getRigidBody(pipe).velocity.y = 0.0

    getRigidBody(pipe).acceleration.x = 0.0
    getRigidBody(pipe).acceleration.y = 0.0

    getRigidBody(pipe).gravity.x = 0.0
    getRigidBody(pipe).gravity.y = 0.0

    getRigidBody(pipe).force.x = 0.0
    getRigidBody(pipe).force.y = 0.0

    getRigidBody(pipe).mass = 10.0

    getRigidBody(pipe).static = true
    getRigidBody(pipe).trueRB = true

    getScale(pipe).scale = 90

    getRigidBody(pipe).min.x = 0.0
    getRigidBody(pipe).min.y = 0.0
    getRigidBody(pipe).max.x = 0.0
    getRigidBody(pipe).max.y = 0.0
    getBoxCollider(pipe, getRigidBody(pipe).min, getRigidBody(pipe).max)

    getSprite(pipe2).name = "Pipe"

    getPosition(pipe2).x = 200
    getPosition(pipe2).y = 15 - pipe_Master.pipeGap - offset
    getPosition(pipe2).z = 0.5

    getRigidBody(pipe2).velocity.x = pipe_Master.pipeSpeed
    getRigidBody(pipe2).velocity.y = 0.0

    getRigidBody(pipe2).acceleration.x = 0.0
    getRigidBody(pipe2).acceleration.y = 0.0

    getRigidBody(pipe2).gravity.x = 0.0
    getRigidBody(pipe2).gravity.y = 0.0

    getRigidBody(pipe2).force.x = 0.0
    getRigidBody(pipe2).force.y = 0.0

    getRigidBody(pipe2).mass = 10.0

    getRigidBody(pipe2).static = true
    getRigidBody(pipe2).trueRB = true

    getScale(pipe2).scale = 90

    getRigidBody(pipe2).min.x = 0.0
    getRigidBody(pipe2).min.y = 0.0
    getRigidBody(pipe2).max.x = 0.0
    getRigidBody(pipe2).max.y = 0.0
    getBoxCollider(pipe2, getRigidBody(pipe2).min, getRigidBody(pipe2).max)
end
-----------------------------
-----------------------------

function spawnBall()
    ball = createEntity()

    table.insert(ball_ID, 1, ball)

    getSprite(ball).name = "Ball"
    
    getPosition(ball).x = getPosition(boss_ID).x
    getPosition(ball).y = getPosition(boss_ID).y
    getPosition(ball).z = 1.0

    getRigidBody(ball).velocity.x = -180.0
    getRigidBody(ball).velocity.y = 100.0

    getRigidBody(ball).acceleration.x = 0
    getRigidBody(ball).acceleration.y = 0

    getRigidBody(ball).gravity.x = 0
    getRigidBody(ball).gravity.y = -9.8

    getRigidBody(ball).force.x = -50.0
    getRigidBody(ball).force.y = 20.0

    getRigidBody(ball).mass = 10.0

    getRigidBody(ball).static = false

    getScale(ball).scale = 10
end

-----------------------------
-----------------------------
-- Spawn Crosshair --
function spawnCrossHair()
    
    crossHair = createEntity()    
    EntityTable["Crosshair"] = crossHair
    getSprite(crossHair).name = "Crosshair"

    getPosition(crossHair).x = getPosition(EntityTable["Player"]).x
    getPosition(crossHair).y = getPosition(EntityTable["Boss"]).y
    getPosition(crossHair).z = 0.1
    getRotation(crossHair).angle = 0.0
    getScale(crossHair).scale = 10

    getRigidBody(crossHair).velocity.x = 0.0
    getRigidBody(crossHair).velocity.y = 0.0
    getRigidBody(crossHair).acceleration.x = 0.0
    getRigidBody(crossHair).acceleration.y = 0.0
    getRigidBody(crossHair).gravity.x = 0.0
    getRigidBody(crossHair).gravity.y = 0.0
    getRigidBody(crossHair).force.x = 0.0
    getRigidBody(crossHair).force.y = 0.0
    getRigidBody(crossHair).mass = 10.0
    getRigidBody(crossHair).static = true
    getRigidBody(crossHair).trueRB = false

    getRigidBody(crossHair).min.x = 0.0
    getRigidBody(crossHair).min.y = 0.0
    getRigidBody(crossHair).max.x = 0.0
    getRigidBody(crossHair).max.y = 0.0
    getBoxCollider(crossHair, getRigidBody(crossHair).min, getRigidBody(crossHair).max)
end
-----------------------------
-----------------------------


-----------------------------
-----------------------------
-- Create EventListener Entity --
eventListener_ID = createEntity()
eventListener_filepath = rootpath .. "EventListener.lua"
if (loadScript("EventListener", eventListener_filepath, false)) then
    print("Event Listener entity created")
    getScript(eventListener_ID).name = "EventListener"
    getScript(eventListener_ID).path = filePath(eventListener_filepath)
    EntityTable["EventListener"] = eventListener_ID
else
    print("Failed to create Event Listener entity")
end
-----------------------------
-----------------------------
