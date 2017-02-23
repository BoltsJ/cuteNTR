# cuteNTR

cuteNTR is intended to be a cross platform debugger and streaming client for
NTR CFW for 3DS.

## Current status

- Starting a stream is implemented!
- The top screen and bottom screen are displayed in separate windows.
- Scaling the windows is implemented, and can be done without restarting the
  client.
- Stream windows can be hidden by setting the scale to zero and re-shown by
  setting the scale to a nonzero value.
- Stream settings can be set and will be saved when the stream is launched.
- Sending a unversal NFC patch is implemented. 
- Pokemon Sun and Moon 1.1 NFC patch.
- Other game specifice patches are in the works.

![screen shot](https://i.imgur.com/QrDcHoz.png "Screenshot")

## Packages

- Arch Linux - [cutentr-git](https://aur.archlinux.org/packages/cutentr-git/)
- Ubuntu packages are available in a PPA.
```
sudo add-apt-repository ppa:joenosie/3ds
sudo apt-get update
sudo apt-get install cutentr
```
- Fedora 25 RPM and source RPM available on the
  [tags](https://gitlab.com/BoltsJ/cuteNTR/tags) page.
- Debian and Raspbian Jessie packages are available on the
  [tags](https://gitlab.com/BoltsJ/cuteNTR/tags) page.

## [Building](https://gitlab.com/BoltsJ/cuteNTR/wikis/building)

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

### Icon
Icon by Kevin Navia
<kevin@pixelpush.io>

License: https://creativecommons.org/licenses/by/3.0/
