#!/usr/bin/env python
# -*- coding: utf-8 -*-

from gdata import service
import gdata, atom, util

def CreatePublicPost(blogger_service, blog_id, title, content):
	entry = gdata.GDataEntry()
	entry.title = atom.Title('xhtml', title)
	entry.content = atom.Content(content_type='html', text=content)
	return blogger_service.Post(entry, '/feeds/%s/posts/default' % blog_id)

def publish(info, title, doc):
	blogEntry = CreatePublicPost(
		info.blogger_service,
		info.blog_id, 
		title = title,
		content = doc
	)

def main(argv):
	info = util.Info()
	publish(info, 'I have the answer', 'Eureka! It is 42!')
	return 0


if __name__=='__main__':
	import sys
	sys.exit(main(sys.argv))
