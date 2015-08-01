#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/kcoin.png
ICON_DST=../../src/qt/res/icons/kcoin.ico
convert ${ICON_SRC} -resize 16x16 kcoin-16.png
convert ${ICON_SRC} -resize 32x32 kcoin-32.png
convert ${ICON_SRC} -resize 48x48 kcoin-48.png
convert kcoin-16.png kcoin-32.png kcoin-48.png ${ICON_DST}

