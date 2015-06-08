#!/bin/sh
NAME=shutdownd
DSCR=/etc/init.d/${NAME}
DEXE=/usr/local/sbin/${NAME}
PIDF=/var/run/${NAME}.pid

sudo ${DSCR} stop

sudo cp ./${NAME}.sh ${DSCR}
sudo chown root.root ${DSCR}
sudo chmod 755 ${DSCR}

sudo cp build/${NAME} ${DEXE}
sudo chown root.root ${DEXE}

sudo update-rc.d ${NAME} defaults

sudo ${DSCR} start
