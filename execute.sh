#!/bin/bash
EXE_NAME="tp_final_paa"
readonly EXE_NAME
BIN_DIR="./bin"
INPUTS_DIR="./inputs"
readonly INPUTS_DIR
OUTPUTS_DIR="./outputs"
readonly OUTPUTS_DIR
echo "Executando o Trabalho Final de PAA - Top K mais influentes"
$BIN_DIR/$EXE_NAME -i $INPUTS_DIR/CA-HepTh.txt -o $OUTPUTS_DIR/output.txt
