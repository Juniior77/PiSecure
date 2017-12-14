#!/usr/bin/python

import sys
import urllib.request

url = "https://smsapi.free-mobile.fr/sendmsg?user=96912590&pass=XG2SvNtocuWRnC&msg=Intrusion%20detect%C3%A9e%20par%20le%20syst%C3%A8me%20PISECURE%20!"
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

