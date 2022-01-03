# ARCHIVER
## _Tearm project 20.12.21_
Archiver in C++
## Features

- Compression of a text file type .txt
- User-friendly interface
- Handling exceptions
- A game of "Tag" during the archiving process
-  Playing music while the program is running



## Tech

- Compression - Huffman coding
- Interface - SFML
- Game "Tag" - created thanks to [guide](https://habr.com/ru/post/449596/)

## How to work with it?

Run the programm.

| Buttom | Functin |
| ------ | ------ |
| Create archive |Create <fileName>.ach, play "Tag"|
| Unarchive file |Decrypt <fileName>.ach |
| About the app |Information for testing the app|
| Exit | Finish the programm|

## FAQ
- Programm not be launched 
> Check the connection of the SFML library.
> Сheck the availability of all necessary files: **images/, files/, music/**

- I can't find the <fileName>.ach/<resultDecryption_fileName>.txt
> These files are saved in  **files/**
> You can change this manually in the code.
