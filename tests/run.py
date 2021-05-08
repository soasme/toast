"""
Example Usage:

    $ python tests/run.py json

"""
import sys
import json
from glob import glob
import subprocess as proc
from pathlib import Path
import os

dirname = Path(os.path.dirname(__file__))

def main(lang):
    total, failed = 0, 0
    for path in glob(f'{dirname}/{lang}/*'):
        total += 1
        filename = Path(path).name

        process = proc.run([f'{dirname}/../toast', 'json', path], capture_output=True)

        if process.returncode != 0:
            if not (filename.startswith('n_') or filename.startswith('i_')):
                sys.stdout.write(f'FAILED: {filename} (Exit {process.returncode}) Error: {process.stderr.decode("utf-8")}')
                sys.stdout.flush()
                failed += 1
                continue
            sys.stdout.write(f'PASS: {filename} (Exit {process.returncode}) Error: {process.stderr.decode("utf-8")}')
            sys.stdout.flush()
        else:
            # TODO: check expected ast output?
            output = process.stdout

            sys.stdout.write(f'PASS: {filename} Output: {output.decode("utf-8")}\n')
            sys.stdout.flush()

    print("-" * 30)
    print(f'Total {total}, PASS {total-failed}, FAILED {failed}')

if __name__ == '__main__':
    lang = sys.argv[1]
    main(lang)
