# stout-pr-reviewer-test

Throwaway firmware repo used to validate Stout's PR Reviewer end-to-end against PRD-2 (nRF5340 DK + J-Link Plus).

## What this firmware does

Boots, then prints `<MESSAGE> <counter>` over Segger RTT once per `BLINK_PERIOD_MS`. Both the message and the period are constants in `src/main.c`. Each PR changes one of them. The Stout PR Reviewer's generated Lager Python test should:

1. Flash `built/firmware.hex` onto PRD-2 via the `debug1` net (J-Link).
2. Reset the chip.
3. Read RTT for ~5 seconds.
4. Assert the messages match the new expected format/rate.

## How CI works

`.github/workflows/build.yml` builds via the Zephyr CI Docker image, uploads `firmware.hex` as a workflow artifact, **and commits the hex back to the PR branch under `built/firmware.hex`**. The committed hex is what the PR Reviewer's generated script will fetch via `raw.githubusercontent.com`.

The auto-commit uses `[skip ci]` to avoid loops. Each PR ends up with two PR Reviewer runs:

- **First run** (your push): no `built/firmware.hex` yet — script will fail to fetch.
- **Second run** (CI's auto-commit): hex is in place — flash + RTT validation runs.

This noise is deliberate while we're testing what's built. A future fix is to retrigger the reviewer only on `workflow_run.completed`.

## Build target

`nrf5340dk/nrf5340/cpuapp` (Zephyr board target for the official Nordic nRF5340 DK).

## Local build (optional, for humans)

You don't need this to use the repo — CI handles all builds. If you want a local build:

```bash
west init -l .
west update
west build -b nrf5340dk/nrf5340/cpuapp
```

Requires nRF Connect SDK + west tooling.
