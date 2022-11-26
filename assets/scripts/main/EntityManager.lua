EntityTable = {}

rootpath = "scripts/main/"

-- assigning key with value nil removes the key
-- EntityTable["EventListener"] = nil

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

-----------------------------
-----------------------------
-- Create Player Entity --
player_ID = createEntity()
EntityTable["Player"] = player_ID

player_fp = rootpath .. "player.lua"
if (loadScript("Player", player_fp, false)) then
    getScript(player_ID).name = "Player"
    getScript(player_ID).path = filePath(player_fp)
else
    print("\t--Failed to create Player entity--")
end

getSprite(player_ID).name = "Player"

getPosition(player_ID).x = -140.0
getPosition(player_ID).y = -50.0
getPosition(player_ID).z = 1.0

getRigidBody(player_ID).velocity.x = 0.0
getRigidBody(player_ID).velocity.y = 0.0
getRigidBody(player_ID).acceleration.x = 0
getRigidBody(player_ID).acceleration.y = 0

getRigidBody(player_ID).gravity.x = 0.0
getRigidBody(player_ID).gravity.y = 0.0
getRigidBody(player_ID).force.x = 0.0
getRigidBody(player_ID).force.y = 0.0

getRigidBody(player_ID).mass = 10.0
getRigidBody(player_ID).static = false
getScale(player_ID).scale = 10

-- ball2 = createEntity()

-- getSprite(ball2).name = "Ball"

-- getPosition(ball2).x = 140.0
-- getPosition(ball2).y = -50.0
-- getPosition(ball2).z = 1.0

-- getRigidBody(ball2).velocity.x = 0.0
-- getRigidBody(ball2).velocity.y = 0.0

-- getRigidBody(ball2).acceleration.x = 0
-- getRigidBody(ball2).acceleration.y = 0

-- getRigidBody(ball2).gravity.x = 0.0
-- getRigidBody(ball2).gravity.y = 0.0

-- getRigidBody(ball2).force.x = 0.0
-- getRigidBody(ball2).force.y = 0.0

-- getRigidBody(ball2).mass = 10.0

-- getRigidBody(ball1).static = false

-- getScale(ball2).scale = 10.0
-----------------------------
-----------------------------

