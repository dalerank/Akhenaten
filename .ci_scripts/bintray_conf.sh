#!/usr/bin/env bash

build_dir="$(pwd)/build"

VERSION=$(cat res/version.txt)
if [[ ! -z "$TRAVIS_TAG" ]]
then
  REPO=Ozymandias
elif [[ "$TRAVIS_BRANCH" == "master" ]]
then
  REPO=Ozymandias-unstable
elif [[ "$TRAVIS_BRANCH" =~ ^feature/ ]]
then
  REPO=Ozymandias-branches
  VERSION=${TRAVIS_BRANCH##feature/}-$VERSION
else
  echo "Unknown branch type $TRAVIS_BRANCH - skipping deploy to Bintray"
  exit
fi

if [ "$DEPLOY" = "linux" ]
then
cat > "bintray.json" <<EOF
{
  "package": {
    "subject": "keriew",
    "repo": "$REPO",
    "name": "linux",
    "licenses": ["AGPL-V3"],
    "vcs_url": "https://github.com/dalerank/ozymandias.git"
  },

  "version": {
    "name": "$VERSION",
    "released": "$(date +'%Y-%m-%d')",
    "desc": "Automated Linux build for Travis-CI job: $TRAVIS_JOB_WEB_URL"
  },

  "files": [
    {
      "includePattern": "${build_dir}/Ozymandias.zip",
      "uploadPattern": "Ozymandias-$VERSION-linux-x86_64.zip"
    }
  ],

  "publish": true
}
EOF
# Linux portable binary: https://appimage.org/
elif [ "$DEPLOY" = "appimage" ]
then
cat > "bintray.json" <<EOF
{
  "package": {
    "subject": "keriew",
    "repo": "$REPO",
    "name": "linux",
    "licenses": ["AGPL-V3"],
    "vcs_url": "https://github.com/dalerank/ozymandias.git"
  },

  "version": {
    "name": "$VERSION",
    "released": "$(date +'%Y-%m-%d')",
    "desc": "Automated Linux AppImage build for Travis-CI job: $TRAVIS_JOB_WEB_URL"
  },

  "files": [
    {
      "includePattern": "${build_dir}/ozymandias.AppImage",
      "uploadPattern": "ozymandias-$VERSION-linux.AppImage"
    }
  ],

  "publish": true
}
EOF
elif [ "$DEPLOY" = "mac" ]
then
cat > "bintray.json" <<EOF
{
  "package": {
    "subject": "keriew",
    "repo": "$REPO",
    "name": "mac",
    "licenses": ["AGPL-V3"],
    "vcs_url": "https://github.com/dalerank/ozymandias.git"
  },

  "version": {
    "name": "$VERSION",
    "released": "$(date +'%Y-%m-%d')",
    "desc": "Automated macOS build for Travis-CI job: $TRAVIS_JOB_WEB_URL"
  },

  "files": [
    {
      "includePattern": "${build_dir}/ozymandias.dmg",
      "uploadPattern": "ozymandias-$VERSION-mac.dmg",
      "listInDownloads": true
    }
  ],

  "publish": true
}
EOF
elif [ "$DEPLOY" = "vita" ]
then
cat > "bintray.json" <<EOF
{
  "package": {
    "subject": "keriew",
    "repo": "$REPO",
    "name": "vita",
    "licenses": ["AGPL-V3"],
    "vcs_url": "https://github.com/dalerank/ozymandias.git"
  },

  "version": {
    "name": "$VERSION",
    "released": "$(date +'%Y-%m-%d')",
    "desc": "Automated Vita build for Travis-CI job: $TRAVIS_JOB_WEB_URL"
  },

  "files": [
    {
      "includePattern": "${build_dir}/ozymandias.vpk",
      "uploadPattern": "ozymandias-$VERSION-vita.vpk",
      "listInDownloads": true
    }
  ],

  "publish": true
}
EOF
elif [ "$DEPLOY" = "switch" ]
then
cat > "bintray.json" <<EOF
{
  "package": {
    "subject": "keriew",
    "repo": "$REPO",
    "name": "switch",
    "licenses": ["AGPL-V3"],
    "vcs_url": "https://github.com/dalerank/ozymandias.git"
  },

  "version": {
    "name": "$VERSION",
    "released": "$(date +'%Y-%m-%d')",
    "desc": "Automated Switch build for Travis-CI job: $TRAVIS_JOB_WEB_URL"
  },

  "files": [
    {
      "includePattern": "${build_dir}/ozymandias.zip",
      "uploadPattern": "ozymandias-$VERSION-switch.zip",
      "listInDownloads": true
    }
  ],

  "publish": true
}
EOF
fi
