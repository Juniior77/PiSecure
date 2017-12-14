#!/usr/bin/python

import sys
import urllib.request

url = "https://smsapi.free-mobile.fr/sendmsg?user=96912590&pass=XG2SvNtocuWRnC&msg=Une%20vidéo%20a%20été%20enregistrer%20sur%20le%20système%20PiSecure%20http://192.168.1.22/enregistrement.php"
try:
  req = urllib.request.urlopen(url)
  print('SMS sended.')
except Exception as e:
  if hasattr(e, 'code'):
    if e.code == 400:
      raise Exception('Some parameter is missing.')
    if e.code == 402:
      raise Exception('Too many sms in a short periode.')
    if e.code == 403:
      raise Exception('Service not activated or user/password incorrect.')
    if e.code == 500:
      raise Exception('Try later.')

