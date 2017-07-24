#install python-pybluez
#connect via bluetoothctl
#trust via bluetoothctl
#pacaur -S python-mpd2
import bluetooth
from threading import Timer
import time
import select
from mpd import MPDClient


print("Connecting...")
bt_addr = "98:D3:31:80:65:07"
port = 1
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((bt_addr, port))
sock.setblocking(0)
print("Connected")

client = MPDClient()
client.connect("localhost",6600)
print(client.mpd_version)

def sendPlaying():
    global t
    sock.send("N"+client.currentsong().get("artist")+'\n')
    sock.send("T"+client.currentsong().get("title")+'\n')
    t = Timer(4, sendPlaying)
    t.start();

def sendMeta():
    global t
    t.cancel()
    seconds=float(client.status().get("elapsed"))
    m, s = divmod(seconds, 60)
    h, m = divmod(m, 60)
    seconds=float(client.status().get("duration"))
    md, sd = divmod(seconds, 60)
    hd, md = divmod(md, 60)
    sock.send("XVol: "+client.status().get("volume")+'\n')
    if(hd==0):
        sock.send("YT: "+"%02d:%02d" % (m, s)+'/'+"%02d:%02d" % (md, sd)+'\n')
    else:
        sock.send("YT: "+"%d:%02d:%02d" % (h, m, s)+'/'+"%d:%02d:%02d" % (hd, md, sd)+'\n')
    t = Timer(4, sendPlaying)
    t.start()

t = Timer(4, sendPlaying)
t.start()

while True:
    ready=select.select([sock], [],[],5)
    if ready[0]:
        data=int.from_bytes(sock.recv(1024), byteorder='big')
        if(data==0):
            client.previous()
            sendPlaying()
        elif(data==1):
            client.next()
            sendPlaying()
        elif(data==2):
            client.setvol(int(client.status().get("volume"))+5)
        elif(data==3):
            client.setvol(int(client.status().get("volume"))-5)
        elif(data==4):
            if(client.status().get("state")=="play"):
                client.pause(1)
            else: client.pause(0)
        elif(data==6):
            sendMeta()
