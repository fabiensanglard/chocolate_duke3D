#!/bin/sh
rm -rf autom4te.cache build-aux aclocal.m4
autoreconf -ivf
rm -rf autom4te.cache
