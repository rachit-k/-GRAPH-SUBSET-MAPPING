./compile.sh
date
./run1.sh T_S_2
./minisat T_S_2.satinput T_S_2.satoutput
./run2.sh T_S_2
date
python check.py T_S_2.graphs T_S_2.mapping
# rm T_M_2.satinput
# date
# ./run1.sh T_M_4
# ./minisat T_M_4.satinput T_M_4.satoutput
# ./run2.sh T_M_4
# date
# python check.py T_M_4.graphs T_M_4.mapping
# rm T_M_4.satinput
# date
# ./run1.sh T_L_1
# ./minisat T_L_1.satinput T_L_1.satoutput
# ./run2.sh T_L_1
# date
# python check.py T_L_1.graphs T_L_1.mapping
# rm T_L_1.satinput
# date
# ./run1.sh Unsat
# ./minisat Unsat.satinput Unsat.satoutput
# ./run2.sh Unsat
# date
# rm Unsat.satinput
