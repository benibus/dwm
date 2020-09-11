dwm - dynamic window manager
============================
Personal fork of suckless.org's dwm - an extremely fast, small, and dynamic window manager for X.


Patches
------------
* actualfullscreen
* attachaside
* bottomstack
* center
* deck
* dwmc
* gridmode
* inplacerotate
* killunsel
* namedscratchpads
* noborder
* pertag
* push_no_master
* savefloats
* statuscmd_signal (requires seperate dwmblocks patch)
* swallow
* systray
* titlecolor
* warp (modified)
* ...and a variety of other personal tweaks


Requirements
------------
In order to build dwm you need the Xlib header files.
This build also requires dwmblocks for the status bar.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Configuration
-------------
The configuration of dwm is done by editing config.h and
(re)compiling the source code.
