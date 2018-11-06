#!/bin/bash
cd frameworks/native
git reset --hard && git clean -f -d
patch -p1 < ../../device/motorola/nicklaus/patches/0002-frameworks-native.patch
cd ../..
cd system/netd
git reset --hard && git clean -f -d
patch -p1 < ../../device/motorola/nicklaus/patches/0010-wifi-tethering-fix.patch
cd ../..
add_lunch_combo dot_nicklaus-user
add_lunch_combo dot_nicklaus-userdebug
add_lunch_combo dot_nicklaus-eng
