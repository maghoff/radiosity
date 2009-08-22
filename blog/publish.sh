#!/bin/bash

make
scp style.css *.html 10.0.0.200:public_html/radiosityblog/
