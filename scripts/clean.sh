#!/bin/bash

#========================================================================================
# Script to clean the pod server.
#   1) Clean the built sub-module(s) (uWebSockets , etc..) / shared libs.
#   2) Delete everything inside 'lib' folder within the shared library's folder.
#   3) Run wio clean (cleans the folder where binary was made).
#========================================================================================
# After the last step we "should" have our binary file generated and linked properly.
#========================================================================================

#========================================================================================
# Helper functions.
#========================================================================================

UWS_DIR='./shared/uWebSockets';
UWS_LIB_DIR="${UWS_DIR}/lib";
UWS_LIB="${UWS_DIR}/libuWS.so";

#========================================================================================
# Begin script.
#========================================================================================

make clean -C "${UWS_DIR}";

if [ ${?} -eq 0 ]; then
    echo "Almost cleaned uWebsockets...";
    echo "Now deleting the '/uWebSockets/lib' folder (that has the .so/.dylib).";

    rm -rf "${UWS_LIB_DIR}";

    if [ ${?} -eq 0 ]; then
        echo "Successfully cleaned uWebsockets.";
    else
        echo "Couldn't delete the ../lib folder inside uWebSockets.";
    fi

else
    echo "Couldn't clean uWebsockets =(.";
    exit 22;
fi

sudo wio clean --hard;
