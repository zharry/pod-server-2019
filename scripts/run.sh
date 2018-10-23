
UWS_DIR='./shared/uWebSockets';
UWS_LIB_DIR="${UWS_DIR}/lib";

unamestr=`uname`;
if [[ "$unamestr" == 'Darwin' ]]; then
        export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$UWS_LIB_DIR;
elif [[ "$unamestr" == 'Linux' ]]; then
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$UWS_LIB_DIR;
fi

wio run;
