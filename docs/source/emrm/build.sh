#!/bin/bash

MODE="-halt-on-error"
#MODE="-interaction=nonstopmode"

DATE=`date -I`
A_STUB="emrm_${DATE}_a4"
US_STUB="emrm_${DATE}_us_letter"

function latex_build () {
    cat refman.tex >> $1.tex

    pdflatex $MODE $1.tex || exit 1
#    bibtex $1.aux
    pdflatex $MODE $1.tex
    pdflatex $MODE $1.tex
    pdflatex $MODE $1.tex
}

sudo apt-get install texlive texlive-latex-extra

echo "Building Reference Manual..."
# git clone https://github.com/embroidermodder/libembroidery || exit 1
#
# python3 make_tables.py || exit 1
#
# mandoc -c -O width=80 -T ascii libembroidery/docs/embroider.1 > docs/embroider.txt || exit 1

printf "\\documentclass[a4paper]{report}\n\n" > ${A_STUB}.tex || exit 1
printf "\\documentclass[letterpaper]{report}\n\n" > ${US_STUB}.tex || exit 1
    
latex_build ${A_STUB} || exit 1
latex_build ${US_STUB} || exit 1

tar cf emrm.tar ${A_STUB}.pdf ${US_STUB}.pdf

echo "Reference Manual successfully built in A4 and US Letter paper."
