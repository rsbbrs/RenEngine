-- Keeps track of existing significant entities (i.e., player and boss)
EntityTable = {}
-- EntityID Management for projectiles
fireBall_ID = {}
laser_ID = {}
pipe_ID = {}

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
function spawnLaser()
    laser = createEntity()

    table.insert(laser_ID, 1, laser)

    getSprite(laser).name = "Laser"

    getPosition(laser).x = getPosition(boss_ID).x - 10.0
    getPosition(laser).y = getPosition(boss_ID).y + 20
    getPosition(laser).z = 0.6

    getRigidBody(laser).velocity.x = -250.0
    getRigidBody(laser).velocity.y = 0.0
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
function spawnPipe(x, y)
    pipe = createEntity()

    table.insert(pipe_ID, 1, pipe)
    -- print("Pipe table size: " .. #pipe_ID)
    -- for i = 1, #pipe_ID, 1 do
    --     print("Pipe id: " .. pipe_ID[i])
    -- end

    getSprite(pipe).name = "Pipe"

    getPosition(pipe).x = x
    getPosition(pipe).y = y
    getPosition(pipe).z = 0.5

    getRigidBody(pipe).velocity.x = -40.0
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

    getScale(pipe).scale = 50

    getRigidBody(pipe).min.x = 0.0
    getRigidBody(pipe).min.y = 0.0
    getRigidBody(pipe).max.x = 0.0
    getRigidBody(pipe).max.y = 0.0
    getBoxCollider(pipe, getRigidBody(pipe).min, getRigidBody(pipe).max)
end
-----------------------------
-----------------------------

-----------------------------
-----------------------------
-- Create EventListener Entity --
event_State = {
    themePlaying = false
}
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
