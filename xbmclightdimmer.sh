#!/bin/bash
xbmcurl="http://pc-tv/jsonrpc"


previousvideoplaying=0
while [ 1 ]
do


wget -q -O- --header='Content-Type: application/json' --post-data='{"jsonrpc": "2.0", "method": "Player.GetActivePlayers", "id": 1}' $xbmcurl | grep -v '"video"' > /dev/null
video=$?
wget -q -O- --header='Content-Type: application/json' --post-data='{"jsonrpc": "2.0", "method": "Player.GetProperties", "params": { "playerid": 1, "properties": ["speed"] }, "id": 1}' $xbmcurl | grep '"speed":0' > /dev/null
playing=$?
#echo "video=$video playing=$playing"


if [ $video == 1 ] && [ $playing = 1 ]; then
#	echo "Video Playing!"
	if [ $previousvideoplaying == 1 ]; then 
		echo "Video Playing, dimming ligths!"
		kaku 123 1 dim 4
	fi
	previousvideoplaying=1
else
	if [ $previousvideoplaying == 1 ]; then 
		echo "Video Stopped, brighting ligths!"
		kaku 123 1 dim 8; 
	fi
	previousvideoplaying=0
fi

done
