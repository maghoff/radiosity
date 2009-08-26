#!/usr/bin/env python
# -*- coding: utf-8 -*-

from gdata import service
import gdata, atom, util

def PrintUserBlogTitles(blogger_service):
	query = service.Query()
	query.feed = '/feeds/default/blogs'
	feed = blogger_service.Get(query.ToUri())

	print feed.title.text
	for entry in feed.entry:
		print "\t" + entry.title.text, "blog_id:", entry.GetSelfLink().href.split("/")[-1]


def main(argv):
	blogger_service = util.get_blogger_service()
	PrintUserBlogTitles(blogger_service)
	return 0


if __name__=='__main__':
	import sys
	sys.exit(main(sys.argv))
