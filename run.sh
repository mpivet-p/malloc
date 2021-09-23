#!/bin/sh
export LD_LIBRARY_PATH=`pwd`
export LD_PRELOAD=`pwd`/libft_malloc_x86_64_Linux.so
$@
