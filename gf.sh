#!/bin/bash

echo "生成随机文件 大小：$1 数量：$2"

list=
for (( i=1; i<=$2; i++ )); do
  file_name=random_file_$i
  dd if=/dev/urandom of=$file_name bs=1K count=$1
  md5code=$(md5sum random_file_$i)
  name=${md5code:0:32}
  list=${list}"'$name|||/usr1/DServer/rf_$i.so',\n"
  mv $file_name $name
done

echo -e $list > /usr1/DServer/param

echo "生成完毕!"
