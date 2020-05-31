#!/bin/bash

start_ts=`date +%s`

if ! cmake ..; then
  notify-send -u critical OpenASN "Failed at step: cmake .."
  exit 1
fi

if ! make $1; then
  notify-send -u critical OpenASN "Failed at step: make $1"
  exit 1
fi

if ! make test; then
  notify-send -u critical OpenASN "Failed at step: make test"
  exit 1
fi

if ! ./src/app/asn1c -a ../examples/TestModule.asn1 -p; then
  notify-send -u critical OpenASN "Failed at step: asn1c"
  exit 1
fi

end_ts=`date +%s`
diff=$((end_ts-start_ts))
h=$((diff/3600))
m=$(((diff%3600)/60))
s=$((diff%60))

res=$(printf "Build passed in %02d:%02d:%02d\n" $h $m $s)
echo $res
notify-send -u normal OpenASN "$res"
