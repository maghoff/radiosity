#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, re

r = re.compile('^((\d\d)-\d\d\d\d-\d\d-\d\d-.*).md$')
buf = ''

for f in os.listdir(os.curdir):
	m = r.match(f)
	if m:
		buf += '[%s]: %s.html\n' % (m.groups()[1], m.groups()[0])

def should_write():
	try:
		f = open('autolinks.md', 'rb')
		old = f.read()
		f.close()
		return old != buf
	except:
		return True

if should_write():
	open('autolinks.md', 'wb').write(buf)
