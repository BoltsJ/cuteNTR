Name: cutentr
Version: 0.3.1
Release: 1%{?dist}
Summary: N3DS streaming client

Group: X11
License: GPL
URL: https://gitlab.com/BoltsJ/cuteNTR
Source0: %{name}-%{version}.tar.gz

BuildRequires: git, gcc-c++, qt5-qtbase, qt5-qtbase-gui, qt5-qtbase-devel, rpm-build
Requires: qt5-qtbase

%description
N3DS streaming client
 A streaming client for NTR CFW on N3DS. Written in Qt it aims to be a
 cross-platform streaming solution for broadcasting 3DS games to twitch or
 other services.


%prep
%setup -q -n %{name}-%{version}
# qmake-qt5 isn't updating the Makefile if it already exists.
rm -f Makefile src/Makefile

%build
%{qmake_qt5} PREFIX=%{_prefix}
make

%install
make install INSTALL_ROOT=%{buildroot}

desktop-file-install \
    --dir=%{buildroot}%{_datadir}/applications \
    %{buildroot}%{_datadir}/applications/cutentr.desktop

%files
%{_bindir}/cutentr
%{_datadir}/applications/cutentr.desktop
%{_datadir}/icons/cutentr.svg
%{_datadir}/pixmaps/cutentr.xpm

%changelog
* Mon Feb 20 2017 James J <jayninja@fazey.org> 0.3.1-1
- RPM Spec added targeting CentOS 7 support
