Name: cuteNTR	
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
cd src
/usr/lib64/qt5/bin/qmake src.pro -o Makefile 

%build
cd src && make

%install
cd src && make install INSTALL_ROOT=%{buildroot}

mkdir -p $RPM_BUILD_ROOT/usr/local/share/applications/
mkdir -p $RPM_BUILD_ROOT/usr/local/share/icons/
mkdir -p $RPM_BUILD_ROOT/usr/local/share/pixmaps/

install -m 644 ../setup/gui/cutentr.desktop $RPM_BUILD_ROOT/usr/local/share/applications/cutentr.desktop
install -m 644 ../setup/gui/cutentr.svg $RPM_BUILD_ROOT/usr/local/share/icons/cutentr.svg
install -m 644 ../resources/linux/icon/cutentr.xpm $RPM_BUILD_ROOT/usr/local/share/pixmaps/cutentr.xpm

%files
/usr/local/bin/cutentr
/usr/local/share/applications/cutentr.desktop
/usr/local/share/icons/cutentr.svg
/usr/local/share/pixmaps/cutentr.xpm

%changelog
