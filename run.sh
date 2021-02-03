#!/bin/bash

export DYLD_LIBRARY_PATH=/Users/azziz/Workspace/School/malloc
export DYLD_INSERT_LIBRARIES=/Users/azziz/Workspace/School/malloc/libft_malloc.so
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
