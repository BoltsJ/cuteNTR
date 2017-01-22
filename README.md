# cuteNTR

cuteNTR is intended to be a cross platform debugger and streaming client for
NTR CFW for 3DS.

## Current status

- Starting a stream is implemented!
- The top screen and bottom screen are displayed in separate windows.
- Scaling the windows is not supported.
- Stream settings can be set and will be saved when the stream is launched.
- Stopping the stream is not implemented. To exit close _all_ windows or type
  control-c into the terminal.

## Building

Requirements:
- qmake
- libQt5Core
- libQt5Gui
- libQt5Widgets
- libQt5Network

```
$ qmake
$ make
$ sudo make install
$ cuteNTR
```

No installation script is provided yet, but the binary can be manually placed
in your `$PATH`.

## Copyright

Copyright (C) 2017 Joseph R. Nosie

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see http://www.gnu.org/licenses/.
