-- assigning key with value nil removes the key
-- EntityTable["EventListener"] = nil

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

