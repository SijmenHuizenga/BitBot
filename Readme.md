BitBot
======
Dit is mijn uitwerking van de eindopdracht van het vak Embeded Software Development. 
Het doel was om een prototype voor een maan auto te maken. In het hoofdstuk opdracht is de volledigge
opdracht beschreven.

Project Structuur
-----
In het bestandje `BitBot.ino` begint de code. Hierin zijn de setup en loop functies te vinden.
BitBot.ino maakt gebruik van een aantal header files die zijn te vinden in de folders `controllers` en `headers`.
In het mapje controllers zitten alle hardware aansturings klasse, en in het mapje headers zitten alle 
project specefieke klasse. De uitwerking van deze klasse (de .cpp bestanden) zijn te vinden in het mapje `src`.


Opdarcht
-----
Alternatieve eindopdracht met Boebot: Komeet-onderzoeksrobot
De Boebot is door een ruimtesonde naar een komeet gebracht en daar inmiddels veilig en rechtop op geland. De Boebot heeft verschillende sensoren aan boord om onderzoek te doen naar het klimaat op de komeet, waaronder een kompas, accelerometer, gyroscoop, temperatuursensor, lichtsensor, infraroodsensor en een botssensor. Daarnaast beschikt de Boebot over audiovisuele outputmethoden om te communiceren met eventueel aangetroffen intelligente levensvormen.
De Boebot begint met rijden en zal op zoek gaan naar een plek met veel lichtinval, om ervoor te zorgen dat zijn (fictieve) zonnepanelen voldoende licht ontvangen. Als de Boebot ergens tegenaan botst moet hij een draai maken en verder rijden. De Boebot houdt daarbij zijn richting bij d.m.v. zijn digitale kompas (de komeet heeft een magneetveld vergelijkbaar met dat van de aarde). De Boebot meet continu de temperatuur van zijn omgeving. Hoe hoger de temperatuur wordt, hoe sneller het tikgeluid gaat dat hij steeds laat horen. Als de temperatuur boven 30 graden Celsius komt, moet hij er vanuit gaan dat hij in de buurt is van een levensvorm en starten met communiceren via een ledmatrix.
 
###Must
*Boebot kan recht vooruit rijden
*Boebot kan links en rechts draaien
*Boebot kan achteruit rijden
*Boebot onthoudt standrichting bij opstart
*Boebot houdt bij in welke richting hij is gedraaid
*Boebot toont draaiing m.b.v. vier ledjes
*Boebot meet temperatuur
*Boebot is in staat tikgeluiden te maken met drie verschillende snelheden, afhankelijk van temperatuur
*Botssensor registreert botsing
*Boebot stopt en draait (90 graden?) naar links of rechts na botsing
*Boebot toont lachende smiley op ledmatrix als temperatuur boven bepaalde waarde komt
 
###Should
*Boebot kan tijdens vooruit rijden naar links en rechts afbuigen
*Boebot rijdt klein stukje terug na botsing en draait dan
*Boebot toont draaiing m.b.v. meer dan vier ledjes (acht?)
*Boebot toont verdrietige smiley als temperatuur plotseling daalt en/of lichtinval plotseling minder wordt
 
###Could
*Boebot zoekt naar plek met veel lichtinval op basis van nader te bepalen algoritme
*Boebot onthoudt zoveel mogelijk informatie over zijn afgelegde route, zoals positie van obstakels (nader te bepalen wat precies en hoeveel)