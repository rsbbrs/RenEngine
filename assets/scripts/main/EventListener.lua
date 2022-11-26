-- Quit game
if (keyPressed(input_code.escape)) then
    quit()
end

if (game_state == RUNNING and not event_State.themePlaying) then
    playSound("Boss_Theme")
    event_State.themePlaying = true
end

if (game_state == ENDED) then
    event_State.themePlaying = false

    -- Restart
    if (keyPressed(input_code.r) or keyPressed(input_code.left_ctrl)) then
        resetGame()
    end
end



-- Clean up entities that have gone out of the screen --
for i = 1, #pipe_ID, 1 do
    if (getPosition(pipe_ID[i]).x < -200) then
        
        print("Entity with ID: "..pipe_ID[i].." --> position.x = " .. getPosition(pipe_ID[i]).x)
        destroyEntity(table.remove(pipe_ID))
        
    end
end