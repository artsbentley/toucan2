# Wait for an active ZMK build, or download the latest success if idle.
download:
    #!/bin/sh
    set -eu
    export GH_REPO=artsbentley/toucan2
    latest_run() {
        gh run list --workflow build.yml --status "$1" --limit 1 --json databaseId --jq '.[0].databaseId // empty'
    }
    run_id=$(latest_run in_progress)
    if [ -z "$run_id" ]; then
        run_id=$(latest_run queued)
    fi
    if [ -n "$run_id" ]; then
        printf 'Waiting for ZMK build %s…\n' "$run_id"
        gh run watch "$run_id" --exit-status
    else
        run_id=$(latest_run success)
        if [ -z "$run_id" ]; then
            echo 'No successful ZMK firmware build found.' >&2
            exit 1
        fi
    fi
    dest="/Users/arar/Downloads/firmware-$(date '+%d-%H%M%S')"
    gh run download "$run_id" --name firmware --dir "$dest"
    printf 'Firmware extracted to %s\n' "$dest"
