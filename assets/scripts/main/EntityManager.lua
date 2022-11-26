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
createPlayer()
-----------------------------
-----------------------------

-----------------------------
-----------------------------
-- Spawn Fireball --

-- this table handles resource management
fireBall_ID = {}
function spawnFireball()
    
end
-----------------------------
-----------------------------

-----------------------------
-----------------------------
-- Spawn Pipe --
pipe_ID = {}
function spawnPipe(x, y)
    pipe = createEntity()


    table.insert(pipe_ID, pipe)
    print("Pipe table size: " .. #pipe_ID)
    for i = 1, #pipe_ID, 1 do
        print("Pipe id: " .. pipe_ID[i])
    end

    getSprite(pipe).name = "Pipe"

    getPosition(pipe).x = x
    getPosition(pipe).y = y
    getPosition(pipe).z = 1.0

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
