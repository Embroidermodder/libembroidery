#!/usr/bin/env python3

import csv

thread_tables = [
    ["arc_polyester", "Arc Polyester Threads", "arcpoly"],
    ["arc_rayon", "Arc Rayon Threads", "arcrayon"],
    ["coats_and_clark_rayon", "Coats and Clark Rayon Threads", "coatsrayon"],
    ["dxf", "DXF Colors", "dxf"],
    ["exquisite_polyester", "Exquisite Polyester Threads", "exquisite"],
    ["fufu_polyester", "Fufu Polyester Threads", "fufupoly"],
    ["fufu_rayon", "Fufu Rayon Threads", "fufurayon"],
    ["hemingworth_polyester", "Hemingworth Polyester Threads", "hemingworth"],
    ["hus", "HUS Colors", "hus"],
    ["isacord_polyester", "Isacord Polyester Threads", "isacord"],
    ["isafil_rayon", "Isafil Rayon Threads", "isafil"],
    ["jef", "JEF Colors", "jef"],
    ["madeira_polyester", "Madeira Polyester Threads", "madeirapoly"],
    ["madeira_rayon", "Madeira Rayon Threads", "madeirarayon"],
    ["marathon_polyester", "Marathon Polyester Threads", "marathonpoly"],
    ["marathon_rayon", "Marathon Rayon Threads", "marathonrayon"],
    ["pantone", "Pantone Colors", "pantone"],
    ["pcm", "Brother PCM Colors", "pcm"],
    ["pec", "Brother PEC Colors", "pec"],
    ["robison_anton_polyester", "Robinson Anton Polyester Threads", "robinsonpoly"],
    ["robison_anton_rayon", "Robinson Anton Rayon Threads", "robisonrayon"],
    ["shv", "SHV Threads", "shv"],
    ["sigma_polyester", "Sigma Polyester Threads", "sigmapoly"],
    ["sulky_rayon", "Sulky Rayon Threads", "sulkyrayon"],
    ["svg", "SVG Colors", "svg"],
    ["thread_art_polyester", "Thread Art Polyester", "threadartpoly"],
    ["thread_art_rayon", "Thread Art Rayon", "threadartrayon"],
    ["threadelight_polyester", "ThreaDelight Polyester", "threadelight"],
    ["z102_isacord_polyester", "Z102 Isacord Polyester", "z102"]
]

for table in thread_tables:
    fname = "data/"+table[0]+"_colors.csv"
    outfname = "tables/"+table[0]+"_colors.tex"
    file = open(fname, "r", newline='')
    out_file = open(outfname, "w")
    data = csv.reader(file)
    out_file.write(r"""
\begin{longtable}{p{0.3\linewidth} p{0.3\linewidth} p{0.4\linewidth}}
\caption = {%s}
\label{tblr:%s}\\
\textbf{Name} & \textbf{RGB hex code} & \textbf{Catalog Code} \\
""" % (table[1], table[2]))
    first_line = 1
    for row in data:
        if first_line:
            first_line = 0
            continue
        out_file.write(" & ".join(row) + "\\\\\n")
    out_file.write(r"""
\end{longtable}
""")
    file.close()
    out_file.close()
