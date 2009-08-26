#!/usr/bin/env python
# -*- coding: utf-8 -*-

from gdata import service
import gdata
import atom

def whole_file(name):
	f = open(name, "rb")
	data = f.read()
	f.close()
	return data

def get_token():
	return whole_file("token")

def get_blog_id():
	return whole_file("blog_id")

def get_blogger_service():
	token = get_token()
	blogger_service = service.GDataService()
	blogger_service.source = 'duck-bloggerintegration-1.0'
	blogger_service.service = 'blogger'
	blogger_service.account_type = 'GOOGLE'
	blogger_service.server = 'www.blogger.com'
	blogger_service.SetClientLoginToken(token)
	return blogger_service

