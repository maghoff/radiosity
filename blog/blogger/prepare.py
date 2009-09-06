#!/usr/bin/env python
# -*- coding: utf-8 -*-

import codecs, perlmd
from xml.dom import minidom
from xml.dom import *

def text_content(node):
	assert len(node.childNodes) == 1
	assert node.firstChild.nodeType == Node.TEXT_NODE
	return node.firstChild.data

def prepare(f, autolinks):
	input_file = codecs.open(f, mode="r", encoding="utf8")
	md = input_file.read()

	md += autolinks

	links = codecs.open("../links.md", mode="r", encoding="utf8")
	md += links.read()

	html = u"<div>%s</div>" % perlmd.markdown(md)

	doc = minidom.parseString(html)

	# The first h1 is the blog post title
	h1s = doc.getElementsByTagName('h1')
	assert len(h1s) >= 1
	title = text_content(h1s[0])
	h1s[0].parentNode.removeChild(h1s[0])
	h1s = None

	# Adjust the hx-tags; blogger uses h1, h2 outside of the blog post
	for i in range(4, 0, -1):
		src = 'h%i' % i
		trg = 'h%i' % (i + 2)
		hs = doc.getElementsByTagName(src)
		for h in hs:
			h.tagName = trg

	return (title, doc.toxml('utf8').replace('\n', ' '))

def main(argv):
	title, doc = prepare("../02-2009-08-22-GL_PROJECTION-abuse.md", "")
	print 'Title:', title
	print doc

if __name__=='__main__':
	import sys
	sys.exit(main(sys.argv))
