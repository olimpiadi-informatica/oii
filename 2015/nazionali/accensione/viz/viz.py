#!/usr/bin/env python2

import sys
import json

def ex(data, valid=False):
    print >>sys.stderr, json.dumps(data) if valid else data,
    print 1.0 if valid else 0.0
    sys.exit(0)

if __name__ == "__main__":
    fin = open(sys.argv[1])
    fcor = open(sys.argv[2])
    fout = open(sys.argv[3])

    # button pressed
    pressed = map(int, fout.readlines()[0].split())

    # initial status
    status = map(int, fin.readlines()[1].split())

    # list of events
    events = []

    button_id = 0
    for i in pressed:
        button_id += 1

        if i == 1:
            # pressed
            events.append({
                "type": "press",
                "what": button_id
            })

            for j in xrange(1, button_id + 1):
                if button_id % j == 0:
                    # toggle all divisors
                    events.append({
                        "type": "toggle",
                        "what": j
                    })

                    status[j - 1] = 1 - status[j - 1]

    if 0 in status:
        events.append({
            "type": "error",
            "error": 1  # 1 = not all PCs are on
        })
    else:
        events.append({
            "type": "success"
        })

    ex(events, 1)
