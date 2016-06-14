#!/bin/bash

git add *
git commit -a -m "comment"
git push $1 master
