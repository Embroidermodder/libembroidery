#!/bin/bash

latex_build () {
   pdflatex $1.tex || exit 1
   makeindex $1 || exit 1
   bibtex $1.aux || exit 1
   pdflatex $1.tex || exit 1
   pdflatex $1.tex || exit 1
   pdflatex $1.tex || exit 1
}

sudo apt-get update &> deps.log
sudo apt-get upgrade &>> deps.log
sudo apt-get install texlive texlive-latex-extra &>> deps.log

# mandoc -c -O width=80 -T ascii docs/embroider.1 > docs/embroider.txt || exit 1

python3 bin/thead_tables.py

cd docs

echo "Building Reference Manual..."

printf "\\documentclass[a4paper]{report}\n\n" > ${A_STUB}.tex || exit 1
printf "\\documentclass[letterpaper]{report}\n\n" > ${US_STUB}.tex || exit 1

latex_build ${A_STUB} || exit 1
latex_build ${US_STUB} || exit 1

tar cf emrm.tar ${A_STUB}.pdf ${US_STUB}.pdf

echo "Reference Manual successfully built in A4 and US Letter paper."

cd ..
