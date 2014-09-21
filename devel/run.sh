#!/bin/bash
test=$(dirname $0)/test${1}
shift
clear && rm -f ${test} && make ${test} && ${test} "${@}"
