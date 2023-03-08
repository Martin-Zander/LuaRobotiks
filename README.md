<img src="https://i.ibb.co/jzxFP6K/LR-Logo.jpg"  width="300" height="300">

# Robotiks (UE5-Lua-Runtime-Plugin)

Robotiks is an Unreal Engine Plugin, that adds Robotiks that can be programmed and interact with each other at runtime.
The Lua-Integration runs via an modified LuaMachine (originally by rdeioris [https://github.com/rdeioris/LuaMachine]).

## Documentation
### Robotiks-Functions
Robotik-Functions are always orange and always need an "self" as the first argument.
![[Pasted image 20230301145552.png]]
Functions:
```lua
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
```

Robotik-Override-Functions
Robotik-Functions are always greenish and always only have an "self" as the first argument.
![[Pasted image 20230301145914.png]]
```lua
--Gets Called by the Signal-Function
-- Functions -> [OnSignal0, OnSignal1, OnSignal2, OnSignal3, OnSignal4, OnSignal5
--OnSignal6, OnSignal7, OnSignal8, OnSignal9]
function OnSignal0(self)
    print("Im On!")
end
```




## Dependencies
Unreal Engine 5.1 [https://www.unrealengine.com/en-US/download] \
Modified LuaMachine [Already Included]
