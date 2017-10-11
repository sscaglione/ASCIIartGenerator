#!/usr/bin/env python2.7
import os
import re
import sys
import requests

def main(argv=None):
	if argv is None:
		return 1
	if search(argv[1]) == 200:
		return 0
	return 1


def download(url, filename):
	response = requests.get(url)
	with open(filename, 'wb') as f:
		for chunk in response:
			f.write(chunk)
	return response.status_code

def search(query):
	url = "https://www.google.com/search?tbm=isch&source=hp&q=" + query + "&oq=" + query
	response = requests.get(url)
	filtered = re.findall("<img[^>]+>", response.text)
	image_url = re.findall('src=.([\w://.\-\?=]*).', filtered[0])
	return download(image_url[0], query + ".jpeg")

if __name__ == "__main__":
	sys.exit(main(sys.argv))
