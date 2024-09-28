#!/bin/bash  

if [ "$#" -ne 1 ]; then  
    echo "Usage: $0 <name>"  
    exit 1  
fi  

name=$1  
  
# 检查file.txt是否存在  
if [ ! -f "basic.cpp" ]; then  
    echo "Error: basic.cpp does not exist."  
    exit 1  
fi  

cp "basic.cpp" "$name.cpp"  

echo "$name.cpp has been created."