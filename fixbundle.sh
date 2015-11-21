copyFramework() {
  local f
  local todir="player.app/Contents/Frameworks/$(basename $1)"
  cp -R "$1" "$todir"
  for f in $(find "$todir" -type d -name Headers)
  do
    rm -rf "$f"
  done
  rm "$todir/Headers"
}

cp -R "vidplayer/html" "player.app/Contents/MacOS/html"

macdeployqt "player.app"
copyFramework "/Library/Frameworks/VLCQtCore.framework"
copyFramework "/Library/Frameworks/VLCQtWidgets.framework"
