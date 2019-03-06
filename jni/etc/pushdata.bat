adb push timer_test /system/bin/.
adb shell chmod 777 /system/bin/timer_test
adb shell ls -l /system/bin/timer_test

adb shell "/system/bin/timer_test" && adb logcat -s ATEST