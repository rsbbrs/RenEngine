
-- Update time
ticks = ticks + 1
startTime = ticks * (1/60)
isPaused = false

-- Quit game
if (keyPressed(input_code.escape)) then
    quit()
end

if (game_state == ENDED or game_state == WAITING) then
    -- Restart
    if (keyPressed(input_code.r) or keyPressed(input_code.left_ctrl)) then
        resetGame()
    end
end

-- Clean up entities that have gone out of the screen --
for i = 1, #pipe_ID, 1 do
    if (getPosition(pipe_ID[i]).x < -200) then
        destroyEntity(table.remove(pipe_ID))
    end
end

for i = 1, #laser_ID, 1 do
    if (getPosition(laser_ID[i]).x < -200) then
        destroyEntity(table.remove(laser_ID))
    end
end

for i = 1, #fireBall_ID, 1 do
    if (getPosition(fireBall_ID[i]).x > 200) then
        destroyEntity(table.remove(fireBall_ID))
    end
end

for i = 1, #ball_ID, 1 do
    if(getPosition(ball_ID[i]).y < -200) then
        destroyEntity(table.remove(ball_ID))
    end
end