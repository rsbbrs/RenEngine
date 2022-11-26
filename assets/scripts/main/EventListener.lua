-- Quit game
if (keyPressed(input_code.escape)) then
    quit()
end

if (game_state == RUNNING and not event_State.themePlaying) then
    playSound("Boss_Theme")
    event_State.themePlaying = true
end