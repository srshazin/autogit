#!/bin/bash

cd build &&
ninja &&
./autogit $1 $2 $3 $4 $5 $6
