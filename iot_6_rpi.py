import speech_recognition as sr
import keyboard
import threading
import multitimer
from gtts import gTTS
import os
import random
import time
import urllib.request

switch_ses_oc = True
switch2 = False
switch = True
switch3 = False
btnSesSwitch = False
btnisikSwitch = True
ds = 0


def Ses():
    global btnSesSwitch
    global switch
    global switch2
    global switch3
    if btnSesSwitch:
        start()
        switch = True
        switch2 = False
        switch3 = False
        btnSesSwitch = False

    else:
        stop()
        switch = False
        switch2 = False
        switch3 = False
        btnSesSwitch = True


def isikDurum():
    global btnisikSwitch
    if btnisikSwitch:
        btnisikSwitch = False

    else:
        btnisikSwitch = True


def gfg():
    pass
    global switch_ses_oc
    global switch
    global switch2
    global switch3
    global isikLvl

    if switch_ses_oc == True:
        switch_ses_oc = False
    else:

        switch_ses_oc = True


timer = multitimer.MultiTimer(0.1, gfg, args=None, kwargs=None, count=-1, runonstart=True)


def start():
    timer.start()


def stop():
    global switch_ses_oc
    print('Duraklatıldı')
    timer.stop()
    switch_ses_oc = False


r = sr.Recognizer()
m = sr.Microphone()


def is_integer(n):
    try:
        float(n)
    except ValueError:
        return False
    else:
        return float(n).is_integer()


def dinle():
    webUrl = urllib.request.urlopen("http://192.168.1.39/ledsignalon")

    # print("Say something!")
    # print('sw',switch)
    # print('sw2',switch2)
    # print('sw3',switch3)
    with m as source:
        audio = r.listen(source, phrase_time_limit=2)  # phrase_time_limit=2
    # print("Got it! Now to recognize it...")
    try:
        # recognize speech using Google Speech Recognition

        webUrl = urllib.request.urlopen("http://192.168.1.39/ledsignaloff")
        value = r.recognize_google(audio)

        # we need some special handling here to correctly print unicode characters to standard output
        if str is bytes:  # this version of Python uses bytes for strings (Python 2)
            print(u"You said {}".format(value).encode("utf-8"))

        else:  # this version of Python uses unicode for strings (Python 3+)
            print("You said {}".format(value))

        return value
    except sr.UnknownValueError:
        pass
        # print("Oops! Didn't catch that")
    except sr.RequestError as e:
        pass
        # print("Uh oh! Couldn't request results from Google Speech Recognition service; {0}".format(e))


def genel():
    global switch
    global switch2
    global switch3
    global response
    global btnisikSwitch
    if response == 'hello':
        switch2 = True
        print('system wake')
    if switch2:
        switch = False
        response = ''
        response2 = dinle()
        if response2 == 'open' or response2 == 'turn on':
            webUrl = urllib.request.urlopen("http://192.168.1.39/led1off")
            print('led1on')
            btnisikSwitch = True

        if response2 == 'turn off' or response2 == 'close':
            webUrl = urllib.request.urlopen("http://192.168.1.39/led1on")
            btnisikSwitch = False

        if response2 == 'open' or response2 == 'turn on the bedroom':
            webUrl = urllib.request.urlopen("http://192.168.1.39/led2on")

        if response2 == 'turn off the bedroom' or response2 == 'lights off':
            webUrl = urllib.request.urlopen("http://192.168.1.39/led2off")

        if response2 == 'open' or response2 == 'turn on the living room':
            webUrl = urllib.request.urlopen("http://192.168.1.39/led3on")

        if response2 == 'turn off the living room' or response2 == 'lights off':
            webUrl = urllib.request.urlopen("http://192.168.1.39/led3off")



        if response2 == 'settings' or response2 == 'setting':
            print('ışık ayarlarına geçildi')
            switch3 = True
            switch2 = False
            lamba_ayar()

        if response2 == 'exit' or response2 == 'exits':
            print('sistem uyku moduna alındı')
            switch2 = False
            switch = True


def lamba_ayar():
    global switch3
    global switch2
    global response2
    if switch3:
        response2 = ''
        response3 = ''
        response3 = dinle()
        if type(response3) is str:
            if is_integer(response3):
                num = int(response3)

        if response3 == 'exit' or response3 == 'exits':
            switch2 = True
            print('çıkış yapıldı')
            switch3 = False


begin_switch = True
try:
    print("A moment of silence, please...")
    with m as source:
        r.adjust_for_ambient_noise(source)
    if begin_switch:
        start()
        begin_switch = False

    while 1:
        if switch:
            ds = ds + 1
            print(ds)
            response = dinle()

        genel()
        lamba_ayar()

        # if keyboard.is_pressed('q'):
        #     break
except KeyboardInterrupt:
    pass

