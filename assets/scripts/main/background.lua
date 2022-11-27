function updateBackgroundPos(e1, e2, speed, wrapPos)
    position = getPosition(BgTable[e1])
    getPosition(BgTable[e1]).x = position.x - speed
    if(getPosition(BgTable[e1]).x <= -wrapPos) then
        getPosition(BgTable[e1]).x = wrapPos
    end

    position = getPosition(BgTable[e2])
    getPosition(BgTable[e2]).x = position.x - speed
    if(getPosition(BgTable[e2]).x <= -wrapPos) then
        getPosition(BgTable[e2]).x = wrapPos
    end
end

if(game_state == RUNNING or game_state == ENDED) then

    -- Clouds
    updateBackgroundPos(BgTable[1], BgTable[2], 0.125, 380)

    -- Two mountain layers
    updateBackgroundPos(BgTable[3], BgTable[4], 0.25, 360)
    updateBackgroundPos(BgTable[5], BgTable[6], 0.5, 380)

    -- Handles the forest portion of the background.
    updateBackgroundPos(BgTable[7], BgTable[8], 1, 380)
end