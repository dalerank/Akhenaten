#!/usr/bin/env bash
# Fail if UI scripts reintroduce anonymous/factory onclick patterns.
set -euo pipefail

root="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$root"

fail=0

check() {
  local label="$1"
  local pattern="$2"
  local hits
  hits="$(rg -n --glob 'src/scripts/**/*.js' -e "$pattern" || true)"
  if [[ -n "$hits" ]]; then
    echo "FAIL: $label"
    echo "$hits"
    fail=1
  else
    echo "OK: $label"
  fi
}

check 'anonymous onclick: function' 'onclick:\s*function'
check 'runtime .onclick =' '\.onclick\s*='
check 'factory onclick: name(' 'onclick:\s*\w+\('

if [[ "$fail" -ne 0 ]]; then
  echo "UI ES-only check failed. Prefer onclick_event + [es=…] handlers."
  exit 1
fi

echo "UI ES-only check passed."
