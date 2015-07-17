# Hitmon - v1.0.0

![Logo](doc/assets/logo.png)

Hitmon is a Win32 program that counts your daily keyboard hits. It can also serve as a good example for C++ beginners who would like to learn a thing or two about Windows programming and C++ Templates.

## <a name="toc"/> Table of Contents
 * [Table Of Contents](#toc)
 * [Team Members](#team)
 * [Usage](#usage)
 * [Requirements](#requirements)
 * [Building the Samples](#building)
 * [Changelog](#changelog)
 * [TODO](#todo)
 * [Contributing](#contributing)
 * [Licensing](#licensing)

## <a name="team"/> Team Members
 * "Vlachakis Dimitris" <dimitrisvlh@gmail.com>

## <a name="usage"/> Usage

When you open the executable a small icon appears in system tray. Hitmon now counts your keyboard hits. Every once in a while it will notify you that you reached a certain amount of hits (for example 10.000). Additionally, you can view your current hit count at any time by clicking on the icon and choosing the appropriate option. To shutdown Hitmon just choose exit from menu.

Additionally, Hitmon creates a save file right next to the executable. On shutdown, Hitmon saves the current date and hit count on this file. On startup, it reads the file, and if there are previous hits from today, loads them. That means that you can start Hitmon in the morning, shutdown your PC a few hours after to go out pretending you have a life, and when you come back Hitmon will recover your hit count!

## <a name="requirements"/> Requirements
 * For building the project you need to have msvc compiler (I built it with Visual Studio 2013).

## <a name="building"/> Building

To build the project you just have to open the /VisualStudio/Hitmon.sln file.

## <a name="changelog"/> Change Log
 * TODO: Track Major release history after first release

## <a name="todo"/> TODO
 * Add option to save hit records to a file (which will be loaded at start).

## <a name="contributing"/> Contributing
 * For bug fixes, any well checked pull requests are welcome

## <a name="licensing"/> Licensing

Copyright 2015 Vlachakis Dimitris

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

You can also read the license [here](LICENSE).

Copyright (C) 2015 Vlachakis Dimitris <dimitrisvlh@gmail.com>  
All rights reserved.
