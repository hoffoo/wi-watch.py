import os
import sys
import iwlib
import time

def usage():
    print("wi-watch.py [device] [SSID]")
    print("example: wi-watch.py wlan0 Home")

if len(sys.argv) != 3:
    usage()
    sys.exit(1)

device = sys.argv[1]
ssid = sys.argv[2]

# do it once to make sure the interface is right
try:
    iwlib.get_iwconfig(device)
except Exception as ex:
    print(ex)
    sys.exit(1)

def poll():
    config = iwlib.get_iwconfig(device)
    if config["Access Point"] == "00:00:00:00:00:00":
        # connection lost, set ssid again and hope for the best
        print("kicking")
        iwlib.iwconfig.set_essid(device, ssid)

while True:
    poll()
    time.sleep(5)
