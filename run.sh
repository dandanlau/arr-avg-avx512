#!/bin/bash

# Check if the time period argument is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <time_period_in_seconds>"
  exit 1
fi

time_period=$1
end_time=$((SECONDS + time_period))

# Get the number of CPU cores
num_cores=$(nproc)

# Function to run a.out on a specific core
run_on_core() {
  core=$1
  while [ $SECONDS -lt $end_time ]; do
    taskset -c $core /home/amd/avx512/a.out
  done
}

# Run a.out on each core in parallel
for ((i=0; i<num_cores; i++)); do
  run_on_core $i &
done

# Wait for all background processes to finish
wait

echo "a.out executed on all cores for $time_period seconds."
