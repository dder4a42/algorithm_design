#!/bin/bash   

name=$1
outout=$2
  
  
if [ ! -f "$name" ]; then  
    echo "Error: $name does not exist."  
    exit 1  
fi  

g++ "$name" -o "./bin/$outout.out" -g

echo "$name has been compiled."