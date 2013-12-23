433mhzforrpi
============

Software for raspberry pi to control 433 mhz modules including old and new kaku (klik aan klik uit) modules


Stappenplan

Stap 1 - Sluit alles aan

    VCC van de transmitter op pin 4 van je Pi (VCC 5V)
    GND van de transmitter op pin 6 van je Pi (GND)
    ATAD of DATA van de transmitter op pin 8 van je Pi (TX)


Stap 2 - Installeer WiringPi

WiringPi is een prachtige library die veel arduino functionaliteit naar de
Raspberry Pi port. Omdat ik de draadloze library van een Arduino naar de Pi
heb geport, heb je deze library dus ook nodig.

Als je git nog niet hebt, installeer dat dan via:

code:

    sudo apt-get update
    sudo apt-get upgrade
    sudo apt-get install git-core


Daarna gaan we WiringPi downloaden en builden:

code:

    git clone git://git.drogon.net/wiringPi
    cd wiringPi
    git pull origin
    cd wiringPi
    ./build
    cd ..


Als alles goed gaat, heb je nu WiringPi geinstalleerd en kun je mijn code
downloaden!

Stap 3 - Installeer het tooltje

Voer deze code uit:

code:

    git clone git://git@github.com:jeroensteenhuis/433mhzforrpi.git
    cd 433mhzforrpi


Compileer nu de versie die jij nodig hebt:

KlikAanKlikUit
code:

    g++ -o kaku kaku.cpp -I/usr/local/include -L/usr/local/lib -lwiringPi


Action
code:

    g++ -o action action.cpp -I/usr/local/include -L/usr/local/lib -lwiringPi


Blokker
code:

    g++ -o blokker blokker.cpp -I/usr/local/include -L/usr/local/lib -lwiringPi


Elro
code:

    g++ -o elro elro.cpp -I/usr/local/include -L/usr/local/lib -lwiringPi


Nu kun je het zojuist gecompileerde tooltje uitvoeren om je lampen te
schakelen! Bijvoorbeeld:

code:

   sudo ./action 18 C on

of voor de nieuwe kaku modules:

    sudo ./kaku 123 1 on
    sudo ./kaku 123 1 dim 4

Voor de andere merken, voer sudo ./merk uit voor het juiste gebruik. (sudo is nodig omdat de GPIO pin low-level zijn)

Dit kun je voor alle gebruikers instellen door het sticky bit aan te zetten:
    sudo chmod +s merk

Optionele stap 4 - Tweaken

Bereik optimaliseren
Als je moeite hebt met het schakelen, is waarschijnlijk het bereik te klein.
Dit heeft meestal drie oorzaken:

1 De ontvanger zit in de buurt van veel electronica: verplaats deze naar een wat 'rustigere' plek
2 De antenne heeft niet de juiste lengte, dit moet een draad met een harde kern van exact 17,3 cm of een veelvoud hiervan zijn
3 Het vermogen is te laag, boost het vermogen van de transmitter naar maximaal 12V door die twee pinnen op een externe adapter aan te sluiten

Ontvanger
Ook kun je met de broncode aan de slag om de functionaliteiten uit te
bouwen. Voor de originele Arduino library klik hier. Een receiver
aankoppelen zou niet al te moeilijk moeten zijn!

Webserver
Koppel dit tooltje aan bijvoorbeeld een PHP of Node.js server om via je
browser of smartphone je lampen te schakelen met een mobiele website, NFC
tags bij de deur, Wi-Fi detectie.. you name it!

Bron: http://weejewel.tweakblogs.net/blog/8665/lampen-schakelen-met-een-raspberry-pi.html