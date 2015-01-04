#!/usr/bin/env python2

import re, os, sys

def extract_input(cmsbooklet=False):
    if cmsbooklet:
        t = '\n'.join(open(os.path.join('testo','italian.tex'), "r").readlines())
        t = re.sub('[@%]','',t)
        t = re.sub('\exmp{([^}]*)}','@%\\1@',t)
    else:
        taskname = os.path.basename(os.getcwd())
        if os.path.exists(os.path.join('testo', taskname+'.tex')):
            t = '\n'.join(open(os.path.join('testo',taskname+'.tex'), "r").readlines())
        else:
            t = '\n'.join(open(os.path.join('testo','testo.tex'), "r").readlines())
        t = re.sub('[@%]','',t)
        t = re.sub('\esempio{([^}]*)}','@%\\1@',t)
    t = re.sub('@[^%]*@','','@' + t + '@')
    t = re.sub('([%\n])\n*','\\1',t)
    t = re.sub('  *',' ',t)
    return t[1:].split('%')
