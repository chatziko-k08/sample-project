#!/bin/bash

if [ -z "$CODE_DEBUG" ]
then
	echo " *  Executing: $CODE_RUN"
	echo

	cd "$CODE_DIR"
	eval $CODE_RUN
else
	echo " *  Executing: $CODE_DEBUG"
	echo

	eval "exec $CODE_DEBUG"
fi

