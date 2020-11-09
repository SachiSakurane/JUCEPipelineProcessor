#!/bin/sh

# usage ./pachaging.sh PRODUCT_NAME PRODUCT_PATH

cd `dirname $0`
cd ../

mkdir pkg
PRODUCT_PATH="$1"
REPOSITORY_NAME="$2-win"

mkdir -p pkg/$REPOSITORY_NAME
cp -r $PRODUCT_PATH pkg/$REPOSITORY_NAME
cd pkg
ls | xargs -t -I FILE_NAME pwsh -Command "Compress-Archive FILE_NAME FILE_NAME.zip"
ls | grep -v -E ".zip$" | xargs rm -r
cd ../
