#!/usr/bin/ruby
# -*- coding: undecided -*-
# Generatore per matita:
# Scelgo un nodo a caso come inizio ed ad ogni step scelgo un vicino a caso
# Alla fine riordino gli archi in maniera casuale
# NOTA BENE: c'e la possibilita di finire in un nodo senza uscita! in quel caso il programma va in ciclo infinito. non mi é ancora capitato, in caso diminuire il numero di archi o cambiare il seed
require 'set'
N=ARGV[0].to_i
M=ARGV[1].to_i
S=ARGV[2].to_i
srand(S)

edges=Set.new()

#scelgo l'inizio
X=cur=rand(N)+1
M.times do |i|
  #scelgo un vicino usando un arco non ancora presente nella lista
  #se e l'ultimo arco, faccio attenzione a non finire nel vertice di partenza
  #  visto che e vietato dal testo
  begin
    n=rand(N) +1
  end while n==cur or edges.include?([cur,n].sort) or (i==M-1 and n==X)
 
  edges.add([cur,n].sort)
  cur=n
end

puts "%d %d %d %d" %[N,M,X,cur]
#stampo gli archi in ordine casuale:
edges.to_a.sort_by{rand}.each{|edge|
  puts "%d %d" % edge.sort_by{rand}
}
