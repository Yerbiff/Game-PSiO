# stfml-template
stfml-template for 2d games cpp

#Make sure that you try to run this on x86 debugger

##If dosent work go to project properties and in configuration select Win32

##If still dosent work follow the setup indroduction below


#Setup indroduction:

#1. Select All Configurations | Platform: Win 32
  a) C/C++ -> General -> Additional includes Directiories -> add: " $(SolutionDir)\External\include " 
  b) Linker -> General -> Additional library Directiories -> add: " $(SolutionDir)\External\lib " 

#2. Select in Configuration, Release
  a) Linker -> Input -> Additional Dependecies -> add: 
  sfml-system.lib
  sfml-graphics.lib
  sfml-window.lib
  sfml-audio.lib
  sfml-network.lib
  
#3. Select in Configuration, Debug
  a) Linker -> Input -> Additional Dependecies -> add: 
  sfml-system-d.lib
  sfml-graphics-d.lib
  sfml-window-d.lib
  sfml-audio-d.lib
  sfml-network-d.lib
  
 #4. Apply and ok.
