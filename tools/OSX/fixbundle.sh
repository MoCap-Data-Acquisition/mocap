copyFramework() {
  local f
  local todir="OS-MoCap.app/Contents/Frameworks/$(basename $1)"
  cp -R "$1" "$todir"
  for f in $(find "$todir" -type d -name Headers)
  do
    rm -rf "$f"
  done
  rm "$todir/Headers"
}

cp -R "OS-MoCap/html" "OS-MoCap.app/Contents/MacOS/html"

macdeployqt "OS-MoCap.app"
copyFramework "/Library/Frameworks/VLCQtCore.framework"
copyFramework "/Library/Frameworks/VLCQtWidgets.framework"
