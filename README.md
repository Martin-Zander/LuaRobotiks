<img src="https://i.ibb.co/jzxFP6K/LR-Logo.jpg"  width="300" height="300">

# Robotiks (UE5-Lua-Runtime-Plugin) [Multiplayer]

Robotiks is an Unreal Engine Plugin, that adds Robotiks that can be programmed and interact with each other at runtime. \
The Lua-Integration runs via an modified LuaMachine (originally by rdeioris [https://github.com/rdeioris/LuaMachine]). \
Robotiks is completly working in Multiplayer(Tested in ListenServer).

# Get Started
<img src="https://i.ibb.co/6nYtNGF/Bild-2023-03-09-013059662.png" alt="Bild-2023-03-09-013059662" border="0"></a> \
The 10 Red Dots at the Left Side represent the Inputs/Connections this Robotiks has, Red means none, Green mean something. \
The 10 Blue Buttons on the Right Side are used to Trigger Signals on this Robotiks manually. \
The Green Button in the Right-Bottom corner is used to save your changes and to Reload Lua, so that your code can be executed. \
The Blue Button in the Left-Bottom corner is used to send this Robotiks to all other Robotiks as an Input. \
On which input this Robotiks will set itself on the other Robotiks depends on the ID that is set below. [0-9] \
The Input below that is the Frequency on which this Robotik should send itself to other Robotiks. Only Robotiks with the same Frequency will get this Robotiks as an Input when the "Send Self" Button is Pressed.
The Right Button in the Top-Right Corner is used for exiting the Robotik.\

# Functions
Robotik-Functions are always orange and always need an "self" as the first argument.
<img src="https://i.ibb.co/MfLWD0f/Bild-2023-03-09-010044616.png" alt="Bild-2023-03-09-010044616" border="0"></a>

Robotik-Override-Functions are always greenish and always only have an "self" as the first argument.
<img src="https://i.ibb.co/cJjxTqy/Bild-2023-03-09-010251908.png" alt="Bild-2023-03-09-010251908" border="0"></a> 

```lua
--Gets Called by the Signal-Function
-- Functions -> [OnSignal0, OnSignal1, OnSignal2, OnSignal3, OnSignal4, OnSignal5
--OnSignal6, OnSignal7, OnSignal8, OnSignal9]
function OnSignal0(self)
    print("Im On!")
end

Functions:
--Calls the OnSignal0-Function on the 5th input
-- 5 = InputIndex
-- 0 = SignalIndex
Signal(self, 5, 0)

--Destroys the Target-Object
-- target = Target to Detroy
Destroy(self, target)

--Calls the OnSignal5-Function on self
-- 5 = SignalIndex
SignalSelf(self, 5)

--Gets the Object Assigned at Input 5
-- 5 = InputIndex
target = GetInput(self, 5)

--Shows msg on an screen.
-- screen = Screen-Reference
-- msg = Message
msg = "Hello From Robotiks"
ShowMessage(self, screen, msg)

--Clears an screen.
-- screen = Screen-Reference
ClearScreen(self, screen)

--Clears an Input by Index.
-- 0 = Index
ClearInput(self, 0)

--Sets the Light-Intensity on an lamp.
-- lamp = Lamp-Reference
-- 1000 = Intensity
SetLampPower(self, lamp, 1000)

--Plays Music on an MusicBox.
-- musicBox = MusicBox-Reference
PlayMusic(self, musicBox)

--Stops Music on an MusicBox.
-- musicBox = MusicBox-Reference
StopMusic(self, musicBox)

--Sets an Value in the ValueBank (Needs to be in Level) at an Index for use in other Robotiks or for use at an later time.
-- 0 = Index
-- "Global Values Are Helpfull" = Value
Set(self, 0, "Global Values Are Helpfull")
Set(self, 1, 5)
Set(self, 2, screen)


--Gets an Value from ValueBank (Needs to be in Level).
-- 0 = Index
msg = Get(self, 0)
magicNumber = Get(self, 1)
coolScreen = Get(self, 2)

--Opens an Door.
-- door = Door-Reference
OpenDoor(self, door)

--Closes an Door.
-- door = Door-Reference
CloseDoor(self, door)
```




## Dependencies
Unreal Engine 5.1 [https://www.unrealengine.com/en-US/download] \
Modified LuaMachine [Already Included]
