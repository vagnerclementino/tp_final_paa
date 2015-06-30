#!/bin/bash
EXE_NAME="tp_final_paa"
readonly EXE_NAME
BIN_DIR="./bin"
INPUTS_DIR="./inputs"
readonly INPUTS_DIR
OUTPUTS_DIR="./outputs"
readonly OUTPUTS_DIR
RUN_TIMES="10"
readonly RUN_TIMES
K_VALUE="25"
i="1"
for((n=0;n<$RUN_TIMES;n++));
do
    
    echo "Execução "$i "/" $RUN_TIMES;
    OUTPUT_FILE=$OUTPUTS_DIR/"k="$K_VALUE"/output_k="$K_VALUE"_e="$i".txt";
    $BIN_DIR/$EXE_NAME -i $INPUTS_DIR/CA-HepTh.txt -o $OUTPUT_FILE -k $K_VALUE;
    i=$(($i+1));
done;

