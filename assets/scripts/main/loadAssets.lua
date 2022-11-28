print("Loading assets...")

Image_loaded = 0
expected_Images = 14

Sound_loaded = 0
expected_Sounds = 8

-----------------------------
-----------------------------
-- Load Sprites --
print("----------------------------------------")
if (loadImage("AnnoyingDog", "sprites/annoyingDog.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Ball", "sprites/ball.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Fireball", "sprites/fireBall.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Laser", "sprites/laser.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Player", "sprites/Wizard.png")) then 
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded")end
if (loadImage("Pipe", "sprites/longer_pipe.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Spaceship", "sprites/Spaceship.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Boss", "sprites/TGJ_Minion.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Bg_Layer_0", "sprites/Background/Layer_0.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Bg_Layer_1", "sprites/Background/Layer_1.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Bg_Layer_2", "sprites/Background/Layer_2.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Bg_Layer_3", "sprites/Background/Layer_3.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Bg_Layer_4", "sprites/Background/Layer_4.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
if (loadImage("Crosshair", "sprites/Crosshairs_Red.png")) then
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded") end
print("----------------------------------------")
-----------------------------
-----------------------------

-----------------------------
-----------------------------
-- Load Sound --
print("----------------------------------------")
loadSound("Cannon", "sounds/cannon.mp3")
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Explosion", "sounds/explosion.wav")
setVolume("Explostion", 0.75)
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Flap", "sounds/flap.wav")
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Gunshot_1", "sounds/gunshot.mp3")
setVolume("Gunshot_1", 0.25)
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Gunshot_2", "sounds/gunshot_2.mp3")
setVolume("Gunshot_2", 0.25)
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Minecraft-OOF", "sounds/MinecraftOOF.wav")
setVolume("Minecraft-OOF", 1.25)
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Ouch", "sounds/Ouch_EditedUsingAudacity.mp3")
setVolume("Ouch", 0.50)
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Boss_Theme", "sounds/BossBattle4-ByEliteFerrex.mp3")
setVolume("Boss_Theme", 0.50)
setLooping("Boss_Theme", 1)
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
print("----------------------------------------")
-----------------------------
-----------------------------

-- Load Background Scripts --
if(loadScript("Background", "scripts/main/background.lua", false)) then
    print("background.lua loaded")
else
    print("Failed to load background.lua")
end

-----------------------------
-----------------------------
-- Load GameMaster and other stuff --

-- Game master handles basically everything, sorta
-- Game master should be the one creating entities to
-- prevent weird looping problems (i.e., player input)
gm_filepath = "scripts/main/GameMaster.lua"
if (loadScript("GameMaster", gm_filepath, true)) then
    print("GameMaster loaded")
else
    print("Failed to load Game Master")
end

-----------------------------
-----------------------------