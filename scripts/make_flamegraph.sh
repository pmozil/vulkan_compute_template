#!/usr/bin/env sh


sudo sh -c 'echo 0 > /proc/sys/kernel/kptr_restrict'
sudo sh -c 'echo 0 > /proc/sys/kernel/perf_event_paranoid'

perf record -F 77431 -a -g -- "$@"
perf script | c++filt | ./scripts/stackcollapse-perf.pl > out.perf-folded
./scripts/flamegraph.pl --cp out.perf-folded > perf.svg
rm out.perf-folded perf.data.old perf.data
