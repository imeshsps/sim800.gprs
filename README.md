# SIM800L Arduino GPRS Connection Test

This Sketch will setup SIM800L to connect to GPRS, setup http connection and read a text file at given URL.
Then it will display text data in serial monitor and close the http and GPRS connections.

Please uncomment "mySerial.println("AT+HTTPSSL=1")" if your connection is https.
