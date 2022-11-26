EntityTable = {}

local rootpath = "scripts/main/"

local origPos_X = -105
local origPos_Y = 10

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
getPosition(player_ID).x = origPos_X
getPosition(player_ID).y = origPos_Y
getPosition(player_ID).z = 1.0
getRigidBody(player_ID).velocity.x = 0.0
getRigidBody(player_ID).velocity.y = 0.0
getRigidBody(player_ID).acceleration.x = 0
getRigidBody(player_ID).acceleration.y = 0
getRigidBody(player_ID).gravity.x = 0.0
getRigidBody(player_ID).gravity.y = 0.0
getRigidBody(player_ID).force.x = 0.0
getRigidBody(player_ID).force.y = 0.0
getRotation(player_ID).angle = 180
getRigidBody(player_ID).mass = 10.0
getRigidBody(player_ID).static = false
getScale(player_ID).scale = 10

getRigidBody(player_ID).min.x = 0.0
getRigidBody(player_ID).min.y = 0.0
getRigidBody(player_ID).max.x = 0.0
getRigidBody(player_ID).max.y = 0.0


getBoxCollider(player_ID, getRigidBody(player_ID).min, getRigidBody(player_ID).max)

-----------------------------
-----------------------------

