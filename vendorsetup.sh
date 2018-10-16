#!/bin/bash
cd frameworks/native
git reset --hard && git clean -f -d
patch -p1 < ../../device/motorola/nicklaus/patches/0002-frameworks-native.patch
cd ../..
add_lunch_combo aosp_nicklaus-user
add_lunch_combo aosp_nicklaus-userdebug
add_lunch_combo aosp_nicklaus-eng