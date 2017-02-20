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

## Building
### Debian
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
$ cutentr
```
### CentOS 7 
Requirements(yum install these):
- gcc-c++
- qt5-qtbase
- qt5-qtbase-gui
- qt5-qtbase-devel
- rpm-build

```
[root@centos-7-amd64 SRCDIR]# mkdir -p ~/rpmbuild/SOURCES
[root@centos-7-amd64 SRCDIR]# tar -zcf ~/rpmbuild/SOURCES/cuteNTR.tar.gz cuteNTR 
[root@centos-7-amd64 SRCDIR]# rpmbuild -bb cuteNTR/rpm/cuteNTR.spec 
Executing(%prep): /bin/sh -e /var/tmp/rpm-tmp.CgzRqg
+ umask 022
+ cd /root/rpmbuild/BUILD
+ cd /root/rpmbuild/BUILD
+ rm -rf cuteNTR
[...]
Checking for unpackaged file(s): /usr/lib/rpm/check-files /root/rpmbuild/BUILDROOT/cuteNTR-0.3.1-1.el7.centos.x86_64
Wrote: /root/rpmbuild/RPMS/x86_64/cuteNTR-0.3.1-1.el7.centos.x86_64.rpm
Wrote: /root/rpmbuild/RPMS/x86_64/cuteNTR-debuginfo-0.3.1-1.el7.centos.x86_64.rpm
Executing(%clean): /bin/sh -e /var/tmp/rpm-tmp.dL0Dq6
+ umask 022
+ cd /root/rpmbuild/BUILD
+ cd cuteNTR
+ /usr/bin/rm -rf /root/rpmbuild/BUILDROOT/cuteNTR-0.3.1-1.el7.centos.x86_64
+ exit 0
[root@centos-7-amd64 SRCDIR]# ls -l ~/rpmbuild/RPMS/x86_64/total 716
-rw-r--r--. 1 root root  47332 Feb 20 00:12 cuteNTR-0.3.1-1.el7.centos.x86_64.rpm
-rw-r--r--. 1 root root 681304 Feb 20 00:12 cuteNTR-debuginfo-0.3.1-1.el7.centos.x86_64.rpm
[root@centos-7-amd64 SRCDIR]# 
```

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
