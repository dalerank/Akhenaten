#!/usr/bin/env bash
set -euo pipefail

source_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
build_dir="$(mkdir -p "${1:-$source_dir/build/ios}" && cd "${1:-$source_dir/build/ios}" && pwd)"
team="${AKHENATEN_IOS_TEAM:-}"

cmake -S "$source_dir" -B "$build_dir" -G Xcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DAKHENATEN_IOS_TEAM="$team"

if [ -n "$team" ]; then
    signing=(-allowProvisioningUpdates)
else
    signing=(CODE_SIGNING_ALLOWED=NO CODE_SIGNING_REQUIRED=NO CODE_SIGN_IDENTITY="")
fi
xcodebuild -project "$build_dir/akhenaten.xcodeproj" -target akhenaten -configuration Release -sdk iphoneos \
    -jobs "$(sysctl -n hw.ncpu)" -quiet "${signing[@]}" build

app="$(find "$build_dir" -maxdepth 2 -path "*Release-iphoneos/akhenaten.app" -type d | head -n 1)"
if [ -z "$app" ]; then
    echo "akhenaten.app was not built" >&2
    exit 1
fi
echo "app: $app"
ls "$app"
for required in akhenaten Info.plist data/neucha.ttf data/pharaoh_fonts_pack.sgx; do
    if [ ! -e "$app/$required" ]; then
        echo "akhenaten.app has no $required" >&2
        exit 1
    fi
done

ipa="$build_dir/Akhenaten.ipa"
stage="$build_dir/ipa"
rm -rf "$stage" "$ipa"
mkdir -p "$stage/Payload"
cp -R "$app" "$stage/Payload/"
(cd "$stage" && zip -qry "$ipa" Payload)
rm -rf "$stage"
echo "ipa: $ipa"
