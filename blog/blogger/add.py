#!/usr/bin/env python
# -*- coding: utf-8 -*-

from gdata import service
import gdata, atom, util

def CreatePublicPost(blogger_service, blog_id, title, content):
	entry = gdata.GDataEntry()
	entry.title = atom.Title('xhtml', title)
	entry.content = atom.Content(content_type='html', text=content)
	return blogger_service.Post(entry, '/feeds/%s/posts/default' % blog_id)

def publish(title, doc):
	blogger_service = util.get_blogger_service()
	blog_id = util.get_blog_id()
	blogEntry = CreatePublicPost(
		blogger_service, blog_id, 
		title = title,
		content = doc
	)

def main(argv):
	publish('I have the answer', 'Eureka! It is 42!')
	return 0


if __name__=='__main__':
	import sys
	sys.exit(main(sys.argv))
