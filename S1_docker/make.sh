#!/bin/bash

# if ./make install, runs ./make_install.sh
# if ./make run, runs ./make_run.sh

case "$1" in
	install)
		./src/make_install.sh
		;;
	run)
		./src/make_run.sh
		;;
	*)
		echo "Invalid argument"
		exit 1
		;;
esac

if [ $# -eq help ]; then
	echo "install or run are the only valid arguments"
	echo "install: to install the container"
	echo "run: to run the container"
	echo "./make.sh install"
	echo "./make.sh run"
	exit 1
fi