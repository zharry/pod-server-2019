#!/bin/bash

#========================================================================================
# Script to build the dummy server that follows these steps:
#   1) Make sure the sub-module(s) are/is properly cloned.
#   2) Build the sub-module(s) (uWebSockets , etc..), can be shared libs aswell.
#   3) Copy the shared lib(s) (.so) to our main directories 'bin/deps' folder.
#   4) Build our server using wio, while linking to the shared binary (.so file)
#       that was copied to the deps folder in (3) and built in (2).
#========================================================================================
# After the last step we "should" have our binary file generated and linked properly.
#========================================================================================

#========================================================================================
# Helper functions.
#========================================================================================
Exists() { which "${1}" 2>&1 > /dev/null; echo ${?}; }

#========================================================================================
# Begin script.
#========================================================================================
# Download up to 4 submodules at once, also download submodules of submodules, just
#  using 'git submodule update --init' would suffice, but maybe in future our submodules,
#  might start using submodules of their on, so better safe than sorry!
git submodule update --init --recursive --jobs 4;

if [ ${?} -eq 0 ]; then

    echo "Submodules are there, good to start building them =).";

else

    echo "Submodule are not there, or didn't clone properly =(.";
    exit 11;

fi

make -C ./shared/uWebsockets;

if [ ${?} -eq 0 ]; then

    echo "Successfully built uWebsockets now copying the .so to './bin/deps' folder.";

    if [ -f ./shared/uWebSockets/libiWS.so ]; then

        cp ./shared/uWebSockets/libiWS.so ./bin/deps

    else

        echo "Error copying the submodule binary to the bin folder.";

    fi

else

    echo "Couldn't build uWebsockets =(.";
    exit 22;

fi

wio build;
