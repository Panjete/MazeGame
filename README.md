# MazeGame
A 2-player maze game designed for COP290


Be the first to overflow your progress bar, strategising your gameplay
with yulu-rides, pit-stops, recovery sessions and a lot of fun!

With a ticking clock, a strong opponent, vicious dogs,
angry bees and energy drain with movement
battle it out to emerge victorious

1) You lose the game if your energy reduces to zero
2) Money replenishes with time, use it at food joints for energy , or on a yulu for extra speed
3) Food at Hostel canteen costs lesser than the commercial joint :) Remember, though, only the night messes operate at night!
4) Dog bites are painful! A major hit on the energy, and a respawn after a 5 second recovery from the hospital.
5) Bee stings hurt less, a 5 second recovery period and a minor hit on the energy bar.
6) Yulu gets you fast, but drains wealth.  
7) Use the Zoom out command, for the bigger picture .

## Commands :-
A - The Left Movement key 
D - The Right Movement key
W- The Up Movement key
S - The Down Movement key
L - The Bigger picture command, displays the whole map
M - For the non-music enthusiasts
Space Bar in a Food joint zone - Energy replenishment, for the exchange of some money
Space Bar in a Yulu Zone - Hop on/off a Yulu, with a gradually emptying wallet 


Both the teammates operated on an Ubuntu environment, via a Virtual Machine on an HP and a Mac device. Since a VM could not run the server files appropriately, we ended up having to borrow a dual booted laptop to run the server, and the client was running from any other device.

## Installing the Libraries 

Installation of the SDL2 and its libraries was pretty simple on the Ubuntu systems, and the following commands were given on the terminal:- 

1.SDL2 using `sudo apt-get install libsdl2-dev`. \n
2.SDL_image using `sudo apt-get install libsdl2-image-dev` for image rendering. \n
3.SDL_ttf using `sudo apt-get install libsdl2-ttf-dev` for fonts rendering. \n
4.SDL_mixer using `sudo apt-get install libsdl2-mixer-dev` for audio. \n

## Playing Instructions

1. Clone the repository.
2. Run ```export SRC_DIR=$(pwd)``` after navigating to server folder on a device, and then run ```make```.
3. Run ```export SRC_DIR=$(pwd)``` after navigating to client folder on another device, and then run ```make```.
4. Run ```./play.out``` on both the devices.
5. Have fun!

## Acknowledgements

1. [Lazy foo productions](https://lazyfoo.net/) for the theoy.
2. [Tiled](https://thorbjorn.itch.io/tiled) for making the map.
3. [Google maps](https://www.google.co.in/maps/place/Indian+Institute+of+Technology+Delhi/@28.545718,77.1905792,17z/data=!3m1!4b1!4m5!3m4!1s0x390d1df6b9055fb5:0x81c10b266b1ea3c0!8m2!3d28.545718!4d77.1927679) for making IIT Delhi map.
4) [Let's make games](https://youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx) and his tutorials.



Developers- 
Kartik Sharma, 2020CS10351
Gurarmaan S. Panjeta, 2020CS50426
