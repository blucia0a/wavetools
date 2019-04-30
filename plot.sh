#!/bin/bash

export DISPLAY="localhost:0.0"
gnuplot -p -e 'plot "/dev/stdin"'
