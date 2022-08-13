#!/usr/bin/env bash
cd $(dirname $0)

ANDROID_SDK_ROOT=${1:-SDK}
ANDROID_NDK_VERSION=${2:-23.2.8568313}

if [ -e "$ANDROID_SDK_ROOT" ] ; then
  echo "Error: file or directory \"$ANDROID_SDK_ROOT\" already exists. Delete it manually to proceed."
  exit 1
fi

source ./check-environment.sh || exit 1

SDKMANAGER="./sdkmanager"
if [[ "$OS_NAME" == "win" ]] ; then
  SDKMANAGER="./sdkmanager.bat"
fi

echo "Downloading SDK Manager..."
mkdir -p "$ANDROID_SDK_ROOT" || exit 1
cd "$ANDROID_SDK_ROOT" || exit 1
$WGET "https://dl.google.com/android/repository/commandlinetools-$OS_NAME-8512546_latest.zip" || exit 1
mkdir -p cmdline-tools || exit 1
unzip -qq "commandlinetools-$OS_NAME-8512546_latest.zip" -d cmdline-tools || exit 1
rm "commandlinetools-$OS_NAME-8512546_latest.zip" || exit 1
mv cmdline-tools/* cmdline-tools/latest/ || exit 1

echo "Installing required SDK tools..."
cd cmdline-tools/latest/bin/ || exit 1
yes | $SDKMANAGER --licenses >/dev/null || exit 1
$SDKMANAGER --install "ndk;$ANDROID_NDK_VERSION" "cmake;3.22.1" "build-tools;33.0.0" "platforms;android-33" > /dev/null || exit 1
