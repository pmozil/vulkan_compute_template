#!/bin/sh

sudo sh -c 'echo 0 > /proc/sys/kernel/kptr_restrict'
sudo sh -c 'echo 0 > /proc/sys/kernel/perf_event_paranoid'

perf stat -B -e cache-references,cache-misses,cycles,instructions,branches,faults,migrations -- "$@"
