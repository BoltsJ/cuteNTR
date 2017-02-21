Name: cutentr
Version: 0.3.1
Release: 1%{?dist}
Summary: N3DS streaming client

Group: X11
License: GPL
URL: https://gitlab.com/BoltsJ/cuteNTR
Source0: cuteNTR.tar.gz

BuildRequires: git, gcc-c++, qt5-qtbase, qt5-qtbase-gui, qt5-qtbase-devel, rpm-build
Requires: qt5-qtbase

%description
N3DS streaming client
 A streaming client for NTR CFW on N3DS. Written in Qt it aims to be a
 cross-platform streaming solution for broadcasting 3DS games to twitch or
 other services.


%prep
%setup -q -n cuteNTR
# qmake-qt5 isn't updating the Makefile if it already exists.
rm -f Makefile src/Makefile
qmake-qt5 PREFIX=/usr cutentr.pro -o Makefile

%build
make

%install
make install INSTALL_ROOT=%{buildroot}

mkdir -p $RPM_BUILD_ROOT/usr/share/applications/
mkdir -p $RPM_BUILD_ROOT/usr/share/icons/
mkdir -p $RPM_BUILD_ROOT/usr/share/pixmaps/

install -m 644 setup/gui/cutentr.desktop $RPM_BUILD_ROOT/usr/share/applications/cutentr.desktop
install -m 644 setup/gui/cutentr.svg $RPM_BUILD_ROOT/usr/share/icons/cutentr.svg
install -m 644 resources/linux/icon/cutentr.xpm $RPM_BUILD_ROOT/usr/share/pixmaps/cutentr.xpm

%files
/usr/bin/cutentr
/usr/share/applications/cutentr.desktop
/usr/share/icons/cutentr.svg
/usr/share/pixmaps/cutentr.xpm

%changelog
* Mon Feb 20 2017 James J <jayninja@fazey.org> 0.3.1-1
- RPM Spec added targeting CentOS 7 support
