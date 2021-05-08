# GMod-SDK


This is a module for [Garry's Mod](https://store.steampowered.com/app/4000/Garrys_Mod/) that works based on a SDK.

I've spent the past few days reversing a few modules of the game, in order to get as many interfaces as I could that would be useful to make any type of internal module for [Garry's Mod](https://store.steampowered.com/app/4000/Garrys_Mod/).

Note that this is still WIP!

Note that for now, this only works in x86

I will eventually upload the latest dylibs and idb that I made while reversing the game.


## Usage

Compile as x86 Release. Debug works too.

Get yourself an injector, select Garry's Mod, and inject the compiled .DLL into the target process.

If you did this right, the cheat should loaded.

Press INSERT to open the menu.

## How to update

In case I stop working on this project, and you want to update it, feel free to fork this project.

Get the .dylibs using the game's macOs build [SteamDepotDownloader](https://github.com/SteamRE/DepotDownloader/), and make sure they're up-to-date when you compare them to the Windows build's interfaces.

Null functions can sometime be a pain, make sure they're not phasing out your entire interfaces. A single null function will stop everything from working.

## Contact

You can contact me on [Telegram](https://t.me/Gaztoof), at t.me/@Gaztoof

[This](https://www.youtube.com/channel/UCB7rQNzTsaoS2-I0Z4byUxA) is my YouTube channel.

## Made with

* [IDA Pro](http://www.dropwizard.io/1.0.2/docs/) - The software I used to reverse the game.
* [VMT Dumper](https://pastebin.com/eVHDkHZX) - The IDA script I used for dumping the VTables. I've found it on a forum and modified it.

## Contributing

1. Fork the project (<https://github.com/Gaztoof/GMod-SDK>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
