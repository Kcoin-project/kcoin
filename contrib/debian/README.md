
Debian
====================
This directory contains files used to package kcoind/kcoin-qt
for Debian-based Linux systems. If you compile kcoind/kcoin-qt yourself, there are some useful files here.

## kcoin: URI support ##


kcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install kcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your kcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/kcoin128.png` to `/usr/share/pixmaps`

kcoin-qt.protocol (KDE)

