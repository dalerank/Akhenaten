#!/bin/bash
#
#

ScriptHome=$(echo $HOME)
MY_PATH="`dirname \"$0\"`"
cd "$MY_PATH"

function _helpDefaultRead()
{
    VAL=$1
    
    if [ ! -z "$VAL" ]; then
        defaults read "${ScriptHome}/Library/Preferences/de.slsoft.akhenaten.plist" "$VAL"
    fi
}

function _helpDefaultWrite()
{
    VAL=$1
    local VAL1=$2
    
    if [ ! -z "$VAL" ] || [ ! -z "$VAL1" ]; then
        defaults write "${ScriptHome}/Library/Preferences/de.slsoft.akhenaten.plist" "$VAL" "$VAL1"
    fi
}

function gog_install()
{
    gog_installer=$( _helpDefaultRead "GOGInstaller" )
    DataPath="$HOME/Library/Application Support/akhenaten"
    
    mkdir -p "$DataPath"
    
    ./innoextract --extract --include "app" "$gog_installer" -d "$DataPath"
    
    if [ $? = 0 ]; then
        defaults write "${ScriptHome}/Library/Preferences/de.slsoft.akhenaten" GOGInstalled -bool true
    fi
    
    cd "$DataPath"
    mv app/* .
    rm -rf "$DataPath"/app __support
    
    if [ ! -d  "$HOME/.config/akhenaten" ]; then
        mkdir -p "$HOME/.config/akhenaten"
    fi

    if [ ! -f "$HOME/.config/akhenaten/akhenaten.cfg" ]; then
        echo "data_directory=""$DataPath" > "$HOME/.config/akhenaten/akhenaten.cfg"
        echo "window_mode=0" >> "$HOME/.config/akhenaten/akhenaten.cfg"
        echo "renderer=metal" >> "$HOME/.config/akhenaten/akhenaten.cfg"
        echo "display_scale_percentage=100" >> "$HOME/.config/akhenaten/akhenaten.cfg"
        echo "cursor_scale_percentage=100" >> "$HOME/.config/akhenaten/akhenaten.cfg"
        echo "window_width=800" >> "$HOME/.config/akhenaten/akhenaten.cfg"
        echo "window_height=600" >> "$HOME/.config/akhenaten/akhenaten.cfg"
        
    fi
}

$1
