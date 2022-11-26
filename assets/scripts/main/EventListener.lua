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