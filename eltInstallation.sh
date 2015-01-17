#!/bin/bash
#success=`make -f Source/ELT.mak`

#if [ success -eq 0 ] ; then

	# copy includer header to user includer directory
#	sudo cp -r include/*.h /usr/include/ELT
	# copy ELT shared library to user library directory
	#sudo cp Build/libEngineEx.so /usr/lib/libEngineEx.so

#else

#fi

#if [ cd Source/ ] ; then
#	cd Source/
sudo 
	find Source/ -name '*.h' -exec cp --parents \{\} /usr/include/ELT/ \;
	#sudo cp -r Source/*.h /usr/include/ELT
	# ..  
#fi
