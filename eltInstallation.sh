#!/bin/bash
#installation of ELT by comand prompt

success=`make -f Source/ELT.mak`

if [ success -eq 0 ] ; then

	# copy includer header to user includer directory
	sudo cp -r include/. /usr/include/ELT
	# copy ELT shared library to user library directory
	#sudo cp Build/libEngineEx.so /usr/lib/libEngineEx.so

else

fi

sudo cp -r include/. /usr/include/ELT
