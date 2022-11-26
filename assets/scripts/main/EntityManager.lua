-- assigning key with value nil removes the key
-- EntityTable["EventListener"] = nil


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

    fb_fp = rootpath .. "fireBall.lua"
    if (loadScript("Fireball", fb_fp, false)) then
        getScript(fb).name = "Fireball"
        getScript(fb).path = filePath(fb_fp)
    else
        print("\t--Failed to create Fireball entity--")
        return
    end

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
