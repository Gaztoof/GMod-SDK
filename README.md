# GMod-SDK


This is a module for [Garry's Mod](https://store.steampowered.com/app/4000/Garrys_Mod/) that works based on a SDK.

I've spent the past few days reversing a few modules of the game, in order to get as many interfaces as I could that would be useful to make any type of internal module for [Garry's Mod](https://store.steampowered.com/app/4000/Garrys_Mod/).

Note that this is still WIP!

This works in both x86, and x64.

I've uploaded every idb / dylib i've made while reversing the game, except x64 client.dll as it takes too much space for github.

The gui is an almost-perfect gamesense clone.

This also comes in with a built-in lua executor.

![](https://i.imgur.com/TecyXLF.png)
![](https://i.imgur.com/So6vWVn.png)
![](https://i.imgur.com/85YRzrO.png)
![](https://i.imgur.com/SouXE7G.png)
![](https://i.imgur.com/fBRleQL.png)

## Usage

Compile as x86/x64 Release. Debug works too.

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
* [IMGui](https://github.com/ocornut/imgui) - The GUI is just modified pure ImGui.

## Contributing

1. Fork the project (<https://github.com/Gaztoof/GMod-SDK>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
