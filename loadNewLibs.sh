cd native/Box2D
./BuildDroid.sh
cd ../OpenBox
./BuildDroid.sh
cd ../../
cp native/OpenBox/libs/armeabi/* libs/armeabi/
