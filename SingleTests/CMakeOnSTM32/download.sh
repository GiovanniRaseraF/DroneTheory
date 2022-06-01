#!/bin/bash
# Immutable Project-Local Toolchain Setup
# Inspired by Python's virtualenv and npm
# See http://wp.me/pZZvH-an for more
# Run with `source ./armenv.sh`

# TODOs:
# Add upgrade option
# Cleaner toolchain versioning
# Detect different toolchain versions and warn if installing new?

# Toolchain base string
# Set this to change toolchain versions (though perhaps this is not the most intuitive method)
TOOLCHAIN_BASE="gcc-arm-none-eabi-10.3-2021.10"

# Parse useful information from the toolchain string
TOOLCHAIN_VERSION_MAJOR=10
TOOLCHAIN_VERSION_MINOR=3
TOOLCHAIN_YEAR=2021
TOOLCHAIN_MONTH=10
TOOLCHAIN_ARCHITECTURE=x86_64
# Toolchain base URL
# example: https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
TOOLCHAIN_ADDR="https://developer.arm.com/-/media/Files/downloads/gnu-rm/${TOOLCHAIN_VERSION_MAJOR}.${TOOLCHAIN_VERSION_MINOR}-${TOOLCHAIN_YEAR}.${TOOLCHAIN_MONTH}/"

# Toolchain folder name
# This must match that of the extracted archive
TOOLCHAIN_LOC=gcc-arm-none-eabi-${TOOLCHAIN_VERSION_MAJOR}.${TOOLCHAIN_VERSION_MINOR}-${TOOLCHAIN_YEAR}.${TOOLCHAIN_MONTH}-x86_64-linux.tar.bz2

WORKDIR=`pwd`
TOOLDIR="$WORKDIR/.env"

# Check if tools exist
TOOLTEST="$TOOLDIR/$TOOLCHAIN_LOC/bin/arm-none-eabi-gcc"

res=$?
if [ -f ${TOOLTEST} ] 
then
	export PATH=$TOOLDIR/$TOOLCHAIN_LOC/bin:$PATH
	echo "Toolchain loaded (already installed)"
	return
fi

# Create tool directory
mkdir .env

# Determine toolchain file names

echo "Determining required toolchain"
if [ "$(uname)" == "Darwin" ]; then
    # Do something under Mac OS X platform   
    OS="OSX"
    TOOLCHAIN_FILE="$TOOLCHAIN_BASE-mac.tar.bz2"
    TOOLCHAIN_DL="$TOOLCHAIN_ADDR$TOOLCHAIN_FILE"

elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    # Do something under Linux platform
    OS="LINUX"
    TOOLCHAIN_FILE="$TOOLCHAIN_BASE-$TOOLCHAIN_ARCHITECTURE-linux.tar.bz2"
    TOOLCHAIN_DL="$TOOLCHAIN_ADDR$TOOLCHAIN_FILE"

elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    # Do something under Windows NT platform
    OS="WIN"
    TOOLCHAIN_FILE="$TOOLCHAIN_BASE-win32.zip"
    TOOLCHAIN_DL="$TOOLCHAIN_ADDR$TOOLCHAIN_FILE"
fi

# Check if toolchain is cached

CACHED="$HOME/.env/$TOOLCHAIN_FILE"
if [ -f $CACHED ]; then
    echo "Toolchain found at: $CACHED"
else
    echo "Cached toolchain not found, downloading"
    wget $TOOLCHAIN_DL -P $HOME/.env
fi
cp $CACHED $TOOLDIR

#Extract toolchain

echo "Extracting toolchain"
if [ "$OS" == "OSX" ]; then
	tar -xf $TOOLDIR/$TOOLCHAIN_FILE -C $TOOLDIR
elif [ "$OS" == "LINUX" ]; then
	tar -xf $TOOLDIR/$TOOLCHAIN_FILE -C $TOOLDIR
elif [ "$OS" == "WIN" ]; then
	unzip $TOOLDIR/$TOOLCHAIN_FILE -d $TOOLDIR
fi

# Setup environment

if [ "$OS" == "OSX" ]; then
    ln -s $TOOLDIR/$TOOLCHAIN_FILE $TOOLDIR/gcc-arm-none-eabi
elif [ "$OS" == "LINUX" ]; then
    ln -s $TOOLDIR/$TOOLCHAIN_FILE $TOOLDIR/gcc-arm-none-eabi
elif [ "$OS" == "WIN" ]; then
    echo "Unimplemented"
    return -1;
fi

export PATH=$TOOLDIR/$TOOLCHAIN_LOC/bin:$PATH

echo "Toolchain loaded"
