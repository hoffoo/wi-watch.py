wi-watch.py
-----------

Minimal script to reconnect wireless interface in if connection is lost.

Uses iwlib (pip install iwlib) to poll an interface, if the connection has been
lost it sets the ssid again.

notes
-----

The only way this is sufficient (or needed) is when using wpa_supplicant and
network interface configured in /etc/network/interfaces. The interface
disconnects but wpa_supplicant stays running, so all it takes is setting the
SSID again.

There are a wealth of tools out there that do this (wicd, network-manager).

```sh
wi-watch.py [device] [SSID]
example: wi-watch.py wlan0 Home
```
