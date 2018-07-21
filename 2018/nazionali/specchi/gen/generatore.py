#!/usr/bin/env pypy3

from limiti import *
from sys import argv, exit, stdout, stderr
from random import random, randint, choice, sample, shuffle, seed, triangular
import argparse
from collections import namedtuple, Counter
from math import sqrt

Specchio = namedtuple("Specchio", ["r", "c", "tipo"])
Query = namedtuple("Query", ["lato", "posizione"])
Punto = namedtuple("Punto", ["r", "c"])


def fastify(path):
    """Converte un file di input testuale in binario"""
    with open(path, "r") as f:
        lines = f.readlines()
        stampa(*list(map(int, lines[0].split())), slow=False, zerobasizza=False)
        for line in lines[1:]:
            tipo, a, b = line.split()
            a, b = int(a), int(b)
            stampa(tipo, a, b, slow=False, zerobasizza=False)


def run(args):
    if args.random:
        specchi, query = genera_specchi_random(args), genera_query_random(args)
    elif args.centro:
        specchi, query = genera_specchi_centro(args), genera_query_centro(args)
    elif args.cattivo:
        specchi, query = genera_cattivo(args)
    elif args.zigzag:
        specchi, query = genera_zigzag(args)
    elif args.completo:
        specchi, query = genera_specchi_completo(args), genera_query_completo(args)
    else:
        raise ValueError("È necessario specificare il tipo di generazione")

    specchi = applica_randomness(args, specchi)
    specchi = aggiungi_bordi(args, specchi)

    if args.flip_vert: flip_vert(args, specchi, query)
    if args.flip_oriz: flip_oriz(args, specchi, query)
    if args.flip_diag: flip_diag(args, specchi, query)

    if args.print:
        grid = [["." for _ in range(args.M)] for _ in range(args.N)]
        for specchio in specchi:
            assert ("." == grid[specchio.r][specchio.c])
            grid[specchio.r][specchio.c] = specchio.tipo
        for row in grid:
            print("".join(row), file=stderr)
        print(file=stderr)

    stampa(args.N, args.M, args.Qu+args.Qq, slow=args.slow)
    # numero di update da fare all'inizio
    pre_update = int(args.Qu * args.pre_update)
    # numero di query da fare alla fine
    post_query = int(args.Qq * args.post_query)
    # operazioni da eseguire: 0 = update; 1 = query
    ops = [0] * pre_update + shuf([0] * (args.Qu-pre_update) + [1] * (args.Qq-post_query)) + [1] * post_query
    i_specchi = 0
    i_query = 0
    for op in ops:
        if op == 0:
            s = specchi[i_specchi]
            i_specchi += 1
            stampa(s.tipo, s.r+1, s.c+1, slow=args.slow)
        else:
            q = query[i_query]
            i_query += 1
            stampa("?", q.lato, q.posizione+1, slow=args.slow)


def genera_specchi_random(args, rand=randint, used=set()):
    """
    Genera un insieme di specchi casualemente disposti nella matrice
    :param rand: Funzione da chiamare per generare un intero nell'intervallo [a,b]
    :param used: Set delle posizioni già usate
    """
    specchi = []
    for i in range(args.Qu):
        r, c = rand(0, args.N-1), rand(0, args.M-1)
        while (r,c) in used:
            r, c = rand(0, args.N-1), rand(0, args.M-1)
        used.add((r,c))
        tipo = choice(["/", "\\"])
        specchi.append(Specchio(r=r, c=c, tipo=tipo))
    return specchi


def genera_specchi_centro(args):
    """Genera una configurazione dove è più probabile trovare specchi al centro"""
    return genera_specchi_random(args, rand=lambda a,b: int(triangular(a,b)))


def genera_specchi_completo(args):
    """
    Genera una configurazione dove un particolare raggio colpisce O(NM) specchi
    Esempio:
    v
    \\/\/\/\
    ////////
    \\\\\\\\
    ////////
    \\\\\\\\
    ////////
    \\\\\\\\
    /\/\/\//
          v
    """
    # specchio iniziale
    specchi = [Specchio(r=0, c=0, tipo="\\")]
    # prima riga
    for c in range(args.M)[1:]:
        specchi.append(Specchio(r=0, c=c, tipo=["/", "\\"][c%2]))
    # righe centrali
    for r in range(args.N)[1:-1]:
        for c in range(args.M):
            specchi.append(Specchio(r=r, c=c, tipo=["\\", "/"][r%2]))
    # ultima riga
    for c in range(args.M)[:-1]:
        specchi.append(Specchio(r=args.N-1, c=c, tipo=["/", "\\"][(c%2+args.N%2)%2]))
    # specchio finale
    specchi.append(Specchio(r=args.N-1, c=args.M-1, tipo="/"))
    shuffle(specchi)
    return sample(specchi, args.Qu)


def genera_cattivo(args):
    """Genera una configurazione di specchi dove i percorsi sono mediamente molto lunghi"""
    LIBERO = 0 # cella non usata
    FORW = 1   # /
    BACK = 2   # \
    USED = 3   # cella usata da un percorso

    grid = [ [ LIBERO for _ in range(args.M) ] for _ in range(args.N) ]
    delta = [ Punto(-1,0), Punto(0,1), Punto(1,0), Punto(0,-1) ]
    next_d = { FORW: [2, 1, 4, 3], BACK: [4, 3, 2, 1] }
    specchi = []
    specchi_generati = 0
    # tuple con gli inizi "buoni" (lunghezza percorso, punto di inizio, direzione iniziale)
    inizi = []
    # numero massimo di inizi da generare
    max_inizi = min((args.M + args.N) * 2, 50)

    def genera_percorso(inizio, d):
        nonlocal specchi_generati
        """Genera un percorso partendo da inizio con direzione d"""
        def genera_lunghezza():
            """Genera una lunghezza casuale prima di svoltare obbligatoriamente"""
            return randint(0, min(args.N, args.M)//2)
        def genera_specchio(pos, d):
            """Genera uno specchio da mettere in una certa posizione"""
            # sul bordo cerca di non uscire
            if pos[0] == 0:
                if d == 2: return BACK
                if d == 4: return FORW
            if pos[0] == args.N-1:
                if d == 2: return FORW
                if d == 4: return BACK
            if pos[1] == 0:
                if d == 1: return FORW
                if d == 3: return BACK
            if pos[1] == args.M-1:
                if d == 1: return BACK
                if d == 3: return FORW
            # se non è il bordo prendi una direzione a caso
            return choice([FORW, BACK])

        # lista degli specchi del percorso
        percorso = []
        # lunghezza rimanente prima di svoltare
        lunghezza = genera_lunghezza()
        pos = list(inizio)
        # lunghezza totale del percorso attuale
        lunghezza_tot = 0
        # indica se sono finiti gli specchi
        fine = False
        dir_iniziale = d
        while 0 <= pos[0] < args.N and 0 <= pos[1] < args.M:
            r = pos[0]
            c = pos[1]
            # se ho finito il rettilineo o sono arrivato ad un bordo prova a svoltare
            if lunghezza <= 0 or ((r == 0 or r == args.N-1 or c == 0 or c == args.M-1) and lunghezza_tot > 0):
                # metti uno specchio se il punto è ancora libero
                if grid[r][c] == LIBERO:
                    # se non posso mettere specchi perchè li ho finiti
                    if specchi_generati >= args.Qu:
                        fine = True
                        break
                    # metti uno specchio
                    grid[r][c] = genera_specchio(pos, d)
                    percorso.append(Specchio(r=r, c=c, tipo="/" if grid[r][c] == FORW else "\\"))
                    specchi_generati += 1
            # se sono finito su uno specchio cambia direzione
            if grid[r][c] == FORW or grid[r][c] == BACK:
                d = next_d[grid[r][c]][d-1]
                # appena cambio direzione ricomincia il rettilineo
                lunghezza = genera_lunghezza()
            elif grid[r][c] == LIBERO:
                grid[r][c] = USED

            # faccio avanzare il punto
            pos[0] += delta[d-1].r
            pos[1] += delta[d-1].c
            lunghezza -= 1
            lunghezza_tot += 1

        # punto di ingresso del raggio
        if len(percorso) > 0:
            inizi.append((lunghezza_tot, inizio, dir_iniziale, percorso, len(inizi)))
        return fine

    punti_inizio = []
    for i in range(args.N):
        punti_inizio.append((Punto(r=i, c=0), 2))
        punti_inizio.append((Punto(r=i, c=args.M-1), 4))
    for i in range(args.M):
        punti_inizio.append((Punto(r=0, c=i), 3))
        punti_inizio.append((Punto(r=args.N-1, c=i), 1))

    shuffle(punti_inizio)
    for inizio, d in punti_inizio:
        if genera_percorso(inizio, d):
            break

    # se non ha finito gli specchi
    if specchi_generati < args.Qu:
        try:
            for r in range(args.N):
                for c in range(args.M):
                    # metti uno specchio nelle celle non usate dai percorsi
                    if grid[r][c] == LIBERO:
                        specchi.append(Specchio(r=r, c=c, tipo=choice(["/", "\\"])))
                        # se finisce gli specchi esce dai due for
                        if specchi_generati + len(specchi) >= args.Qu:
                            raise Exception("done")
        except:
            pass

    args.Qu = sum([ len(inizio[3]) for inizio in inizi ]) + len(specchi)
    # tra tutti i percorsi generati prende solo quelli abbastanza lunghi
    inizi.sort(reverse=True)
    # ne prende almeno due più quelli lunghi almeno la metà del secondo
    min_len = inizi[1][0] // 2 if len(inizi) >= 2 else inizi[0][0]
    scartati = list(filter(lambda x: x[0] < min_len, inizi))
    inizi = list(filter(lambda x: x[0] >= min_len, inizi))

    operazioni = Counter()
    query_fatte = 0
    num_query = [0] * len(inizi)
    for i, inizio in enumerate(reversed(inizi)):
        num = min(len(inizio[3]), (args.Qq-query_fatte) // (len(inizi)-i))
        num_query[len(inizi)-i-1] = num
        query_fatte += num
    query_fatte = 0

    for num_q, inizio in sorted(zip(num_query, inizi), key=lambda x: x[1][4]):
        lung, punto, d, percorso, prio = inizio
        pre = max(0, len(percorso) - num_q)
        i = 0
        # mette prima pre specchi
        for _ in range(pre):
            operazioni.update([(len(operazioni), percorso[i].tipo, percorso[i].r+1, percorso[i].c+1)])
            i += 1
        # gli ultimi specchi li alterna a delle query cattive
        while i < len(percorso):
            operazioni.update([(len(operazioni), percorso[i].tipo, percorso[i].r+1, percorso[i].c+1)])
            i += 1
            if d == 1 or d == 3: pos, lato = punto.c, 4-d
            if d == 2 or d == 4: pos, lato = punto.r, 6-d
            operazioni.update([(len(operazioni), "?", lato, pos+1)])
            query_fatte += 1

    for scartato in scartati:
        for s in scartato[3]:
            operazioni.update([(0, s.tipo, s.r+1, s.c+1)])
    for s in specchi:
        operazioni.update([(randint(0, len(operazioni)), s.tipo, s.r+1, s.c+1)])
    for _ in range(args.Qq - query_fatte):
        lato = random_lato(args)
        pos = randint(1,args.N) if lato == 2 or lato == 4 else randint(1,args.M)
        operazioni.update([(randint(0, len(operazioni)), "?", lato, pos)])

    if args.debug:
        print("Lunghezze: (min %d)" % min_len, file=stderr)
        for inizio in inizi:
            print("  - lung: %d   specchi: %d %s %s" % (inizio[0], len(inizio[3]), str(inizio[1]), str(inizio[2])), file=stderr)
        print("numero di specchi finale: ", args.Qu, file=stderr)
        print("specchi generati %d -- specchi random %d" % (specchi_generati, len(specchi)), file=stderr)
        print("numero di query finale: ", args.Qq, file=stderr)
        print("query_fatte: ", query_fatte, file=stderr)
        print("numero di operazioni finale: ", len(operazioni.elements()), file=stderr)

    if args.ordine_cattivo:
        stampa(args.N, args.M, args.Qu+args.Qq, slow=args.slow)
        for op in sorted(operazioni.elements()):
            _, a, b, c = op
            stampa(a, b, c, slow=args.slow)
        exit(0)
    else:
        query = []
        update = []
        for op in sorted(operazioni.elements()):
            _, a, b, c = op
            if a == "?":
                query.append(Query(lato=b, posizione=c-1))
            else:
                update.append(Specchio(tipo=a, r=b-1, c=c-1))
        return update, query

def genera_zigzag(args):
    halfN = (args.N-1)//2
    Qu = 6*halfN+1
    Qq = 5*halfN+1
    extraQ = args.Qq - Qu - Qq + 1
    stampa(args.N, args.M, args.Qq, slow=args.slow)
    for i in range(1, halfN+1):
        stampa("/", 2*i, 1, slow=args.slow)
        stampa("\\", 2*i+1, 1, slow=args.slow)
        stampa("?", 2, 2*i + randint(0, 1), slow=args.slow)
    for i in range(1, halfN+1):
        stampa("\\", 2*i-1, args.M, slow=args.slow)
        stampa("?", 4, 1, slow=args.slow)
        stampa("/", 2*i, args.M, slow=args.slow)
        stampa("?", 4, 1, slow=args.slow)
    data = [("/", args.N, args.M-1)]
    for i in range(1, halfN+1):
        data.append(("\\", 2*i-1, args.M-1))
        data.append(("/", 2*i, args.M-1))
        data.append(("?", 4, 1))
        data.append(("?", 4, 1))
    while extraQ > 0:
        data.append(("?", 4, 1))
        extraQ -= 1
    shuffle(data)
    for mirror in data:
        stampa(*mirror, slow=args.slow)
    exit(0)

def genera_query_random(args, rand=randint):
    """genera delle query in posizioni casuali"""
    query = []
    for i in range(args.Qq):
        # sceglie un lato casuale e una posizione su questo
        lato = random_lato(args)
        if lato == 1 or lato == 3:
            posizione = rand(0, args.M-1)
        else:
            posizione = rand(0, args.N-1)
        query.append(Query(lato, posizione))
    return query

def genera_query_centro(args):
    """genera delle query casuali perferendo le posizioni centrali"""
    return genera_query_random(args, rand=lambda a,b: int(triangular(a,b)))

def genera_query_completo(args):
    """genera delle query per il caso completo"""
    query = []
    for i in range(args.Qq):
        # se la query deve essere per il caso completo
        if random() < args.completo:
            query.append(Query(lato=1, posizione=0))
        # altrimenti query random
        else:
            lato = random_lato(args)
            if lato == 1 or lato == 3:
                posizione = randint(0, args.M-1)
            else:
                posizione = randint(0, args.N-1)
            query.append(Query(lato, posizione))
    return query

def applica_randomness(args, specchi):
    """toglie degli specchi e li sostituisce con specchi casuali"""
    num_random = int(args.Qu * args.randomness)
    specchi = sample(specchi, args.Qu - num_random)

    args2 = argparse.Namespace(N=args.N, M=args.M, Qu=num_random)
    used = { (s.r, s.c) for s in specchi }
    specchi += genera_specchi_random(args2, used=used)
    shuffle(specchi)
    return specchi

def aggiungi_bordi(args, specchi):
    """
    aggiunge dei bordi in alto e in basso sostituendo degli specchi
    /\/\/\/\/\
    ..........
    /\/\/\/\/\
    """
    if not args.bordi: return specchi
    # larghezza dei bordi
    width = int(args.M * args.bordi)
    # punto di inizio dei bordi
    start = randint(0, args.M-width)

    bordi = []
    used = set()
    # aggiunge i bordi
    for c in range(width):
        bordi.append(Specchio(r=0, c=c+start, tipo=["/", "\\"][c%2]))
        bordi.append(Specchio(r=args.N-1, c=c+start, tipo=["/", "\\"][c%2]))
        used.add((0,c+start))
        used.add((args.N-1,c+start))

    i = 0
    # finchè i bordi + alcuni specchi non sono abbastanza
    while len(bordi) < args.Qu:
        # aggiunge uno specchio se questo non è già messo
        if (specchi[i].r, specchi[i].c) not in used:
            bordi.append(specchi[i])
            used.add((specchi[i].r, specchi[i].c))
        i += 1
    shuffle(bordi)
    return bordi[:args.Qu]


def flip_vert(args, specchi, query):
    """flippa griglia e query lungo un asse verticale"""
    for i,s in enumerate(specchi):
        specchi[i] = Specchio(r=s.r, c=args.M-s.c-1, tipo=flip_tipo(s.tipo))
    for i,q in enumerate(query):
        if q.lato == 1 or q.lato == 3:
            query[i] = Query(lato=q.lato, posizione=args.M-q.posizione-1)

def flip_oriz(args, specchi, query):
    """flippa griglia e query lungo un asse orizzontale"""
    for i,s in enumerate(specchi):
        specchi[i] = Specchio(r=args.N-s.r-1, c=s.c, tipo=flip_tipo(s.tipo))
    for i,q in enumerate(query):
        if q.lato == 2 or q.lato == 4:
            query[i] = Query(lato=q.lato, posizione=args.N-q.posizione-1)

def flip_diag(args, specchi, query):
    """flippa griglia e query lungo la diagonale principale"""
    assert(args.N == args.M)
    for i,s in enumerate(specchi):
        specchi[i] = Specchio(r=s.c, c=s.r, tipo=s.tipo)
    for i,q in enumerate(query):
        query[i] = Query(lato=5-q.lato, posizione=q.posizione)

def shuf(x):
    """mescola un vettore e lo ritorna"""
    shuffle(x)
    return x

def choices(choices, weights):
    """sceglie un elemento casuale da una lista pesando i vari valori"""
    total = sum(weights)
    r = randint(0, total)
    upto = 0
    for c, w in zip(choices, weights):
        if upto + w >= r:
            return c
        upto += w
    assert False, "Shouldn't get here"

def random_lato(args):
    """sceglie un lato casuale pesando secondo i paramentri"""
    return choices([1,2,3,4], weights=args.query_bias)

def flip_tipo(tipo):
    """scambia / con \ """
    return "\\" if tipo == "/" else "/"

def stampa(*args, slow=False, zerobasizza=True):
    """stampa dei valori in formato testuale o binario"""
    args = list(args)
    if not isinstance(args[0], int) and zerobasizza:
        args[1] -= 1
        args[2] -= 1
    if slow:
        print(*args)
    else:
        for arg in args:
            if isinstance(arg, int):
                stdout.buffer.write(arg.to_bytes(4, 'little'))
            elif isinstance(arg, str):
                stdout.buffer.write(arg.encode('ascii'))

if __name__ == "__main__":
    if argv[1] == "--fastify":
        fastify(argv[2])
        exit(0)

    parser = argparse.ArgumentParser(description="Generatore di specchi")
    parser.add_argument("N", type=int, help="Altezza della griglia")
    parser.add_argument("M", type=int, help="Larghezza della griglia")
    parser.add_argument("Qu", type=int, help="Numero di update")
    parser.add_argument("Qq", type=int, help="Numero di query")
    parser.add_argument("--seed", type=int, help="Seed", default=None, action="store")
    parser.add_argument("--bordi", type=float, help="Cerca di costruire dei bordi che fanno rimbalzare su e giù",
                        action="store", default=None, metavar="PERC_COPERTURA")
    parser.add_argument("--randomness", type=float, help="Percentuale di specchi da mettere a caso [0.0-1.0]", action="store", default=0)
    parser.add_argument("--query-bias", type=float, help="Quattro valori che indicano la distribuzione della direzione delle query",
                        action="store", nargs=4, metavar=("SU","DX","GIU","SX"), default=[1,1,1,1])
    parser.add_argument("--print", help="Stampa la griglia finale", action="store_true", default=False)
    parser.add_argument("--slow", help="Stampa il file di input in formato testuale", action="store_true", default=False)
    parser.add_argument("--pre-update", type=float, help="Percentuale di update da fare all'inizio", action="store", default=0.5)
    parser.add_argument("--post-query", type=float, help="Percentuale di query da fare alla fine", action="store", default=0.5)
    parser.add_argument("--ordine-cattivo", help="Dispone le query e gli update in un ordine cattivo (sovrascrive pre-update, post-query)", action="store_true", default=False)
    parser.add_argument("--debug", help="Stampa cose di debug", action="store_true", default=False)

    flips = parser.add_mutually_exclusive_group(required=False)
    flips.add_argument("--flip-vert", help="Flippa tutto lungo un asse vericale", action="store_true", default=False)
    flips.add_argument("--flip-oriz", help="Flippa tutto lungo un asse orizzontale", action="store_true", default=False)
    flips.add_argument("--flip-diag", help="Flippa tutto lungo un asse diagonale, N==M!", action="store_true", default=False)

    types = parser.add_mutually_exclusive_group(required=True)
    types.add_argument("--random", help="Genera una configurazione completamente casuale", action="store_true")
    types.add_argument("--centro", help="Tende a generare più specchi vicino al centro", action="store_true")
    types.add_argument("--completo", type=float, help="Costruisce una struttura che tende a colpire tutti i gli specchi (da entrambi i lati)",
                       action="store", default=0.3, metavar="PERC_QUERY_BRUTTE")
    types.add_argument("--cattivo", help="Genera una griglia con percorsi abbastanza lunghi", action="store_true")
    types.add_argument("--zigzag", help="Rimbalza a destra e a sinistra alternando le query. Ignora Qu e Qq.", action="store_true")
    args = parser.parse_args()

    assert (1 <= args.N <= MAXN)
    assert (1 <= args.M <= MAXN)
    if not args.zigzag:
        assert (1 <= args.Qu+args.Qq <= MAXQ)
        assert (args.Qu <= args.N*args.M)
    seed(args.seed)
    run(args)
