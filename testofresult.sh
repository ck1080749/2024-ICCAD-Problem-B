if [ -z "$1" ]; then
  echo "Usage: $0 dirname"
  exit 1
fi

DIRNAME="./exec_result/$1"

# Create the directory if it doesn't exist
mkdir -p "$DIRNAME"

# Run the command 5 times
i=1
while [ $i -le 4 ]; do
#   echo "Running iteration: $i"
  echo "\e[1;30;43mRunning iteration: $i\e[0m"
  make "run$i" | tee "$DIRNAME/run$i.txt"
  i=$((i + 1))
done