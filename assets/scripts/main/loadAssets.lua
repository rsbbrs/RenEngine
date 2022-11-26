print("Loading assets...")

Image_loaded = 0
expected_Images = 12

Sound_loaded = 0
expected_Sounds = 7

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
if (loadImage("Player", "sprites/Wizard.png")) then 
    Image_loaded = Image_loaded + 1
    print(Image_loaded .."/" .. expected_Images .. " image assets loaded")end
if (loadImage("Pipe", "sprites/pipe.png")) then
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
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Flap", "sounds/flap.wav")
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Gunshot_1", "sounds/gunshot.mp3")
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Gunshot_2", "sounds/gunshot_2.mp3")
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Minecraft-OOF", "sounds/MinecraftOOF.wav")
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
loadSound("Ouch", "sounds/Ouch_EditedUsingAudacity.mp3")
Sound_loaded = Sound_loaded + 1
print(Sound_loaded .."/" .. expected_Sounds .. " sound assets loaded")
print("----------------------------------------")
-----------------------------
-----------------------------

-----------------------------
-----------------------------
-- Create GameMaster Object --
GameMaster = createEntity()
gm_filepath = "scripts/main/GameMaster.lua"
if (loadScript("GameMaster", gm_filepath, false)) then
    getScript(GameMaster).name = "GameMaster"
    getScript(GameMaster).path = filePath(gm_filepath)
    print("GameMaster instantiated")
else
    print("Failed to instantiate GameMaster")
end

-----------------------------
-----------------------------