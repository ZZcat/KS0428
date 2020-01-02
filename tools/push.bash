#!/bin/bash

# Call like this  --> bash tools/push.bash "test script" <--

git add -A
git commit -m "$1"
git push
