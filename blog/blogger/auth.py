#!/usr/bin/env python
# -*- coding: utf-8 -*-

from gdata import service
import gdata
import atom

user = "maghoff@gmail.com"

passwd = raw_input("Password for %s: " % user)

blogger_service = service.GDataService(user, passwd)
blogger_service.source = 'duck-bloggerintegration-1.0'
blogger_service.service = 'blogger'
blogger_service.account_type = 'GOOGLE'
blogger_service.server = 'www.blogger.com'
blogger_service.ProgrammaticLogin()

#token = blogger_service.current_token.get_token_string()
token = blogger_service.GetClientLoginToken()

f = open('token', 'wb')
f.write(token)
f.close()
