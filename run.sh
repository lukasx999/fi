#!/bin/sh
set -euxo pipefail

pio run -t upload
pio run -t monitor
