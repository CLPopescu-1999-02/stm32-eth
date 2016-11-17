#!/bin/bash

set -ex

NAME=../size-lib.csv
NAME_IT=../size-it.csv

CSV_HEADER="unused,text,data,bss,total,hex,name"

cd build

echo "${CSV_HEADER}" > ${NAME}
make eth-stm32.size | grep -i totals >> ${NAME}
sed -i 's/[[:space:]]\+/,/g' ${NAME}

echo "${CSV_HEADER}" > ${NAME_IT}
make eth-stm32-it.size | grep -i totals >> ${NAME_IT}
sed -i 's/[[:space:]]\+/,/g' ${NAME_IT}

cd -
