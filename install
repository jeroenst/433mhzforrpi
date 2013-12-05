#!/bin/sh
echo "=== Extracting wiringPi ===\n"
tar xzvf wiringPi.tgz >/dev/null
echo "\n=== Building and installing wiringPi ===\n"
cd wiringPi
./build
cd ..
echo "\n=== Building Executeables ===\n"
echo "433mhzdaemon..."
g++ -o 433mhzdaemon 433mhzdaemon.cpp -I/usr/local/include  -L/usr/local/lib -lwiringPi -lrt
echo "433mhztool..."
g++ -o 433mhztool 433mhztool.cpp -lrt
echo "kaku..."
ln -sf 433mhztool kaku
echo "action..."
ln -sf 433mhztool action

echo "\n=== Installing Executeables ===\n"
sudo cp 433mhzdaemon /usr/sbin
sudo cp 433mhztool /usr/bin
#sudo chmod +s /usr/bin/433mhztool
sudo cp kaku /usr/bin
#sudo chmod +s /usr/bin/kaku
sudo cp action /usr/bin
#sudo chmod +s /usr/bin/action

echo "\n=== Installing Webpages ===\n"
mkdir -p /var/www/domotica
cp kaku.php /var/www/domotica/
cp action.php /var/www/domotica/
cp index.html /var/www/domotica/
echo "\n=== Finished, kaku&action installed in /usr/bin, type kaku or action at prompt to use it or goto http://<raspberrypip>/domotica  ==="
