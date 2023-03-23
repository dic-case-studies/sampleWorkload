#!/bin/bash

cd root

/usr/bin/time -f "%S%M%F" ./fft 216 2> run_result.txt
poweroff
