
Debian
====================
This directory contains files used to package bitnod/bitno-qt
for Debian-based Linux systems. If you compile bitnod/bitno-qt yourself, there are some useful files here.

## bitno: URI support ##


bitno-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitno-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitno-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitno128.png` to `/usr/share/pixmaps`

bitno-qt.protocol (KDE)

