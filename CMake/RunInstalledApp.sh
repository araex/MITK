#!/bin/sh
binpath=$(dirname "$(readlink -f "$0")")
appname=$(basename "$0" .sh)
export LD_LIBRARY_PATH="$binpath/bin":"$binpath/bin/plugins":$LD_LIBRARY_PATH
export QT_PLUGIN_PATH=/usr/lib/x86_64-linux-gnu/qt5/plugins:$QT_PLUGIN_PATH
"$binpath/bin/$appname" "$@"
