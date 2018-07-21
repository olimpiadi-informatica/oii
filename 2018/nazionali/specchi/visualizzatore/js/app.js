'use strict';

var app = angular.module('specchi-vis', []);

app.controller("mainCtrl", ["$scope", function ($scope) {
    $scope.input =
        "4 5 5\n" +
        "/ 1 2\n" +
        "\\ 1 4\n" +
        "? 1 1\n" +
        "/ 3 4\n" +
        "? 3 3";
    $scope.error = "";
    $scope.N = 4;
    $scope.M = 5;
    $scope.scale = 100;
    $scope.num_specchi = 3;
    $scope.specchi = [
        { r: 1, c: 2, t: "/" },
        { r: 1, c: 4, t: "\\" },
        { r: 3, c: 4, t: "/" }
    ];
    $scope.specchi_input = [
        { r: 1, c: 2, t: "/" },
        { r: 1, c: 4, t: "\\" },
        { r: 3, c: 4, t: "/" }
    ];
    $scope.query = [
        { lato: 2, posizione: 1, num_specchi: 2 },
        { lato: 4, posizione: 3, num_specchi: 3 }
    ];
    $scope.raggi = [];

    $scope.posizione = 1;
    $scope.lato = "1";
    $scope.time_scale = 0.05;
    $scope.timeout = 20;
    $scope.risposta = {lato: "?", posizione: "?"};
    $scope.LATI = ["SOPRA", "DESTRA", "SOTTO", "SINISTRA"];

    var delta = [ [0, -1], [1, 0], [0, 1], [-1, 0] ];
    var dir = 0;

    var loop = function () {
        // raggio corrente
        var raggio = $scope.raggi[$scope.raggi.length-1];

        // fai avanzare il raggio fino a non più della sua lunghezza
        raggio.t += $scope.time_scale;
        if (raggio.t >= raggio.T) raggio.t = raggio.T;
        applica_t(raggio);
        $scope.$apply();

        // se il raggio è finito
        if (raggio.t >= raggio.T) {
            var r = raggio.target[1]|0, c = raggio.target[0]|0;

            // se era l'ultimo trova la risposta
            if (raggio.last) {
                $scope.risposta.lato = $scope.LATI[dir-1];
                if (dir == 1 || dir == 3)
                    $scope.risposta.posizione = c;
                else
                    $scope.risposta.posizione = r;
                $scope.$apply();
                return;
            }

            var cella = "";
            for (var i in $scope.specchi)
                if ($scope.specchi[i].r == r && $scope.specchi[i].c == c)
                    cella = $scope.specchi[i].t;
            if (cella == "/")
                dir = dir == 1 ? 2 : dir == 2 ? 1 : dir == 3 ? 4 : 3;
            if (cella == "\\")
                dir = dir == 1 ? 4 : dir == 2 ? 3 : dir == 3 ? 2 : 1;

            // calcola la nuova destinazione basandosi sulla direzione
            var target = [raggio.target[0] + delta[dir-1][0], raggio.target[1] + delta[dir-1][1]];
            // fa partire un nuovo raggio dal punto corrente fino alla destinazione
            var nuovo_raggio = {
                x1: raggio.target[0], y1: raggio.target[1], x2: raggio.target[0], y2: raggio.target[1],
                target: target, t: 0, T: 1, last: true
            };

            // controlla se il raggio esce dalla griglia
            if (target[0] < 0)              nuovo_raggio.target[0] = 0;
            else if (target[0] >= $scope.M) nuovo_raggio.target[0] = $scope.M;
            else if (target[1] < 0)         nuovo_raggio.target[1] = 0;
            else if (target[1] >= $scope.N) nuovo_raggio.target[1] = $scope.N;
            // se non esce allora non è l'ultimo
            else                            nuovo_raggio.last = false;

            // se è l'ultimo allora dura la metà
            if (nuovo_raggio.last) nuovo_raggio.T = 0.5;
            $scope.raggi.push(nuovo_raggio);
            $scope.$apply();
        }
        setTimeout(loop, $scope.timeout);
    };
    var applica_t = function (raggio) {
        raggio.x2 = interpola(raggio.x1, raggio.target[0], raggio.t, raggio.T);
        raggio.y2 = interpola(raggio.y1, raggio.target[1], raggio.t, raggio.T);
    };
    var interpola = function (from, to, t, T) {
        return from + (to-from) * (t/T);
    };
    $scope.avvia = function() {
        var start;
        var pos = +$scope.posizione;
        var lato = +$scope.lato;

        // controlla che la posizione sia nell'intervallo
        if (pos < 0) { alert("Valore minimo: 0"); return; }
        if (pos > $scope.get_max_pos()-1) { alert("Valore massimo: " + $scope.get_max_pos()-1); return; }

        // trova il punto di partenza
        if (lato == 1) start = [pos+0.5,  0];
        if (lato == 2) start = [$scope.M, pos+0.5];
        if (lato == 3) start = [pos+0.5,  $scope.N];
        if (lato == 4) start = [0,        pos+0.5];
        // la direzione è l'opposto del lato
        dir = (lato + 1) % 4 + 1;

        var target = [start[0] + delta[dir-1][0]/2, start[1] + delta[dir-1][1]/2];

        $scope.raggi = [
            {x1: start[0], y1: start[1], x2: start[0], y2: start[1], target: target, t: 0, T: 0.5, last: false}
        ];
        $scope.risposta = {lato: "?", posizione: "?"};
        setTimeout(loop, $scope.timeout);
    };

    $scope.avvia_query = function (index) {
        if (index < 0 || index >= $scope.query.length) return;
        var query = $scope.query[index];
        $scope.lato = query.lato+"";
        $scope.posizione = query.posizione+"";
        $scope.num_specchi = query.num_specchi;
        $scope.update_num_specchi();
        $scope.avvia()
    };

    var parse_int = function(x, name, min, max) {
        var val = parseInt(x);
        if (isNaN(val)) throw name + " non è un intero: '" + x + "'";
        if (min !== undefined && val < min) throw name + " < " + min;
        if (max !== undefined && val > max) throw name + " > " + max;
        return val;
    };

    $scope.update_input = function () {
        $scope.error = "";
        try {
            var lines = $scope.input.trim().split("\n");
            if (lines.length == 0) throw "il file è vuoto";
            var first = lines[0].split(" ");
            if (first.length != 3) throw "la prima riga non ha 3 interi";
            $scope.N = parse_int(first[0], "N", 0);
            $scope.M = parse_int(first[1], "M", 0);
            $scope.Q = parse_int(first[2], "Q", 0);
            if (lines.length != $scope.Q + 1) throw "numero errato di righe: trovate " + lines.length + " invece di " + ($scope.Q + 1);
            $scope.specchi = [];
            $scope.specchi_input = [];
            $scope.query = [];
            $scope.raggi = [];
            for (var i = 1; i < $scope.Q+1; i++) {
                var riga = lines[i].trim().split(" ");
                if (riga.length != 3) throw "la riga " + (i+1) + " non ha 3 valori";
                var cmd = riga[0];
                if (cmd != "/" && cmd != "\\" && cmd != "?") throw "la riga " + (i+1) + " non ha il primo carattere valido: " + cmd;
                if (cmd == "/" || cmd == "\\") {
                    var r = parse_int(riga[1], "[riga " + (i+1) + " valore 2]", 0, $scope.N-1);
                    var c = parse_int(riga[2], "[riga " + (i+1) + " valore 3]", 0, $scope.M-1);
                    $scope.specchi_input.push({r: r, c: c, t: cmd});
                } else {
                    var lato = parse_int(riga[1], "[riga " + (i+1) + " valore 2]", 0, 3);
                    lato += 1;
                    var posizione;
                    if (lato == 1 || lato == 3)
                        posizione = parse_int(riga[2], "[riga " + (i+1) + " valore 3]", 0, $scope.M-1);
                    else
                        posizione = parse_int(riga[2], "[riga " + (i+1) + " valore 3]", 0, $scope.N-1);
                    $scope.query.push({lato: lato, posizione: posizione, num_specchi: $scope.specchi_input.length})
                }
            }
        } catch (ex) {
            $scope.error = ex;
        }
    };

    $scope.update_num_specchi = function () {
        var num_specchi = +$scope.num_specchi;
        if (isNaN(num_specchi)) return;
        $scope.specchi = $scope.specchi_input.slice(0, $scope.num_specchi);
        $scope.raggi = [];
    };

    $scope.get_max_pos = function () {
        if ($scope.lato == 1 || $scope.lato == 3) return $scope.M;
        if ($scope.lato == 2 || $scope.lato == 4) return $scope.N;
    };

    $scope.range = function(min, max, step) {
        step = step || 1;
        var input = [];
        for (var i = min; i <= max; i += step) {
            input.push(i);
        }
        return input;
    };
}]);

angular.forEach(['x', 'y', 'x1', 'x2', 'y1', 'y2', 'width', 'height'], function(name) {
    var ngName = 'ng' + name[0].toUpperCase() + name.slice(1);
    app.directive(ngName, function() {
        return function(scope, element, attrs) {
            attrs.$observe(ngName, function(value) {
                attrs.$set(name, value);
            })
        };
    });
});

app.directive('stringToNumber', function() {
    return {
        require: 'ngModel',
        link: function(scope, element, attrs, ngModel) {
            ngModel.$parsers.push(function(value) {
                return '' + value;
            });
            ngModel.$formatters.push(function(value) {
                return parseFloat(value);
            });
        }
    };
});
