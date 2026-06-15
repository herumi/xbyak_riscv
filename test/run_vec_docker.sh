#!/usr/bin/bash
# Run the (vector) tests inside a debian:testing container, which ships
# binutils >= 2.43 and can assemble the Zvfbfwma instructions (vfwmaccbf16)
# that the host's binutils 2.42 cannot.
#
# Modes:
#   ./run_vec_docker.sh up            # start persistent container + install deps
#   ./run_vec_docker.sh status        # report whether the container is up (exit 0/1)
#   ./run_vec_docker.sh shell         # open an interactive shell in the container
#                                     # (cwd = test dir); type `exit` to leave it
#   ./run_vec_docker.sh               # run the vector test (./test.sh vec)
#   ./run_vec_docker.sh <target>      # run `make <target>` (e.g. test, test_svc)
#   ./run_vec_docker.sh clean         # remove generated artifacts (keep container)
#   ./run_vec_docker.sh down          # clean + remove the container
#
# Persistent mode: once `up`, the `test`/`clean` commands reuse the running
# container so apt-get runs only once - fast for repeated edit/run cycles.
# Without `up`, `test` transparently does up -> run -> down on a throwaway
# container.
set -e

IMAGE=debian:testing
NAME=xbyak_vec
ROOT=$(cd "$(dirname "$0")/.." && pwd)
UIDGID="$(id -u):$(id -g)"
DEPS="make g++ binutils-riscv64-linux-gnu binutils-riscv64-unknown-elf python3 python3-yaml"

container_running() {
  [ "$(docker inspect -f '{{.State.Running}}' "$NAME" 2>/dev/null)" = "true" ]
}

# run a shell command inside the test dir of the persistent container
in_container() {
  docker exec "$NAME" sh -c "cd /work/test && $1"
}

do_up() {
  container_running && return 0
  docker rm -f "$NAME" >/dev/null 2>&1 || true
  docker run -d --name "$NAME" -v "$ROOT":/work -w /work/test "$IMAGE" sleep infinity >/dev/null
  docker exec "$NAME" sh -c "apt -y update && apt -y install $DEPS"
}

do_clean() {
  if container_running; then
    in_container "make clean >/dev/null 2>&1; chown -R $UIDGID /work/test" || true
  else
    (cd "$ROOT/test" && make clean >/dev/null 2>&1) || true
  fi
}

do_down() {
  do_clean
  docker rm -f "$NAME" >/dev/null 2>&1 || true
}

run_target() {
  # no argument -> run the vector test directly; an argument is a make target
  # (e.g. `test`, `test_svc`) run with `make`.
  if [ -n "$1" ]; then
    job="make $1"
  else
    job="./test.sh vec"
  fi
  # persistent mode if the container is already up (started via `up`): reuse it
  # and leave it running. Otherwise spin up a throwaway one and tear it down.
  keep=false
  container_running && keep=true
  do_up
  in_container "$job; chown -R $UIDGID /work/test"
  $keep || do_down
}

case "$1" in
up)
  if container_running; then
    echo "container '$NAME' is already up"
  else
    do_up
    echo "container '$NAME' is up (run './run_vec_docker.sh', 'down' to remove)"
  fi
  ;;
status)
  if container_running; then
    echo "container '$NAME' is up"
  else
    echo "container '$NAME' is down"
    exit 1
  fi
  ;;
shell)
  # open an interactive console inside the container for manual work.
  # starts the container first if it is not running; leaves it running on exit
  # (use `down` to remove it). Type `exit` in the shell to return.
  do_up
  docker exec -it "$NAME" bash
  ;;
clean)
  do_clean
  echo "cleaned generated artifacts"
  ;;
down)
  do_down
  echo "container '$NAME' removed"
  ;;
*)
  # no arg -> vector test (./test.sh vec); otherwise run `make <arg>`
  run_target "$1"
  ;;
esac
