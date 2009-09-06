#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, re, add, prepare, util

root = u'..'

r = re.compile('^\d\d-\d\d\d\d-\d\d-\d\d-.*.md$')
l = [x for x in os.listdir(root) if r.match(x)]
l.sort()

info = util.Info()

for f in l:
	name = os.path.join(root, f)
	title, doc = prepare.prepare(name)
	add.publish(info, title, doc)
