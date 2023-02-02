loadNet("final_untrained.net")

loadPattern("final.pat")

setInitFunc("Randomize_Weights",1.000000,-1.000000)

setLearnFunc("Rprop",0.200000,0.100000,0)

setUpdateFunc("Topological_Order")

setPruningFunc("MagPruning","Rprop",15.000000,3.500000,FALSE,500.000000,90.000000,1e6,1.000000)

setShuffle(TRUE)

initNet()

while SSE > 1.500000 and CYCLES < 1000 do
   print(CYCLES, " ", SSE)
   trainNet()

endwhile

saveNet("final_trained.net")

print("Cycles trained: ",CYCLES)

print("Training stopped at SSE error: ",SSE)

