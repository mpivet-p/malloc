#!/bin/sh
#export LD_LIBRARY_PATH=`pwd`
export LD_PRELOAD=`pwd`/libft_malloc.so
$@
