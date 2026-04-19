#!/bin/sh

set -u

LOG_DIR="tests/logs"

run_suite()
{
	suite="$1"
	cmd="$2"
	out_log="$LOG_DIR/$suite.stdout.log"
	err_log="$LOG_DIR/$suite.stderr.log"

	if sh -c "$cmd" >"$out_log" 2>"$err_log"
	then
		echo "[PASS] $suite"
		return 0
	fi
	echo "[FAIL] $suite"
	echo "  logs: $out_log $err_log"
	cat "$err_log"
	return 1
}

mkdir -p "$LOG_DIR"
status=0

if [ "$#" -eq 0 ]
then
	run_suite "redirections" "./tests/integration/run_redirections_tests.sh" \
		|| status=1
elif [ "$#" -eq 1 ]
then
	if [ "$1" = "redirections" ]
	then
		run_suite "redirections" \
			"./tests/integration/run_redirections_tests.sh" || status=1
	else
		echo "Unknown test suite: $1"
		echo "Available: redirections"
		exit 1
	fi
else
	echo "Usage: ./tests/run_all_tests.sh [suite]"
	exit 1
fi
exit "$status"
