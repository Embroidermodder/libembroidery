# Formats

## Overview

## Read/Write Support Levels

The table of read/write format support levels uses the status levels described here:

| Status Label | Description |
|---|---|
| `rw-none` | Either the format produces no output, reporting an error. Or it produces a Tajima dst file as an alternative. |
| `rw-poor` | A file somewhat similar to our examples is produced. We don't know how well it runs on machines in practice as we don't have any user reports or personal tests. |
| `rw-basic` | Simple files in this format run well on machines that use this format. |
| `rw-standard` | Files with non-standard features work on machines and we have good documentation on the format. |
| `rw-reliable` | All known features don't cause crashes. Almost all work as expected. |
| `rw-complete` | All known features of the format work on machines that use this format. Translations from and to this format preserve all features present in both.

These can be split into `r-basic w-none`, for example, if they don't match.

So all formats can, in principle, have good read and good write support, because it's defined in relation to files that we have described the formats for.

### Test Support Levels

| Status Label | Description |
|----|----|
| `test-none` | No tests have been written to test the specifics of the format. |
| `test-basic` | Stitch Lists and/or colors have read/write tests. |
| `test-thorough` | All features of that format has at least one test. |
| `test-fuzz` | Can test the format for uses of features that we haven't thought of by feeding in nonsense that is designed to push possibly dangerous weaknesses to reveal themselves. |
| `test-complete` | Both thorough and fuzz testing is covered. |

So all formats can, in principle, have complete testing support, because it's defined in relation to files that we have described the formats for.

### Documentation Support Levels

| Status Label | Description |
|---|---|
| `doc-none` | We haven't researched this beyond finding example files. |
| `doc-basic` | We have a rough sketch of the size and contents of the header if there is one. We know the basic stitch encoding (if there is one), but not necessarily all stitch features. |
| `doc-standard` | We know some good sources and/or have tested all the features that appear to exist. They mostly work the way we have described. |
| `doc-good` | All features that were described somewhere have been covered here or we have thoroughly tested our ideas against other softwares and hardwares and they work as expected. |
| `doc-complete` | There is a known official description and our description covers all the same features. |

Not all formats can have complete documentation because it's based on what 
information is publically available. So the total score is reported in the table
below based on what level we think is available.

### Overall Support

Since the overall support level is the combination of these
4 factors, but rather than summing up their values it's an 
issue of the minimum support of the 4.

| Status Label | Description |
|----|----|
| `read-only` | If write support is none and read support is not none. |
| `write-only` | If read support is none and write support is not none. |
| `unstable` | If both read and write support are not none but testing or documentation is none. |
| `basic` | If all ratings are better than none. |
| `reliable` | If all ratings are better than basic. |
| `complete` | If all ratings could not reasonably be better (for example any improvements rely on information that we may never have access to). This is the only status that can be revoked, since if the format changes or new documentation is released it is no longer complete. |
| `experimental` | For all other scenarios. |

### Table of Format Support Levels

Overview of documentation support by format.

| Format | Ratings | Score |
|----|----|----|
| Toyota Embroidery Format (.100) | rw-basic doc-none test-none | unstable |
| Toyota Embroidery Format (.10o) | rw-basic doc-none test-none | unstable |
| Bernina Embroidery Format (.art) | rw-none doc-none test-none | experimental |
| Bitmap Cache Embroidery Format (.bmc) | r-basic w-none doc-none test-none | unstable |
| Bits and Volts Embroidery Format (.bro) | rw-none doc-none test-none | experimental |
| Melco Embroidery Format (.cnd) | rw-none doc-none test-none | experimental |
| Embroidery Thread Color Format (.col) | rw-basic doc-none test-none | `experimental` |
| Singer Embroidery Format (.csd) | rw-none doc-none test-none | experimental |
| Comma Separated Values (.csv) | rw-none doc-none test-none | experimental |
| Barudan Embroidery Format (.dat) | rw-none doc-none test-none | experimental | Melco Embroidery Format (.dem) | rw-none doc-none test-none | experimental |
| Barudan Embroidery Format (.dsb) | rw-none doc-none test-none | experimental |
| Tajima Embroidery Format (.dst) | rw-none doc-none test-none | experimental |
| ZSK USA Embroidery Format (.dsz) | rw-none doc-none test-none | experimental |
| Drawing Exchange Format (.dxf) | rw-none doc-none test-none | experimental |
| Embird Embroidery Format (.edr) | rw-none doc-none test-none | experimental |
| Elna Embroidery Format (.emd) | rw-none doc-none test-none | experimental |
| Melco Embroidery Format (.exp) | rw-none doc-none test-none | experimental |
| Eltac Embroidery Format (.exy) | rw-none doc-none test-none | experimental |
| Sierra Expanded Embroidery Format (.eys) | rw-none doc-none test-none | experimental |
| Fortron Embroidery Format (.fxy) | rw-none doc-none test-none | experimental |
| Smoothie G-Code Embroidery Format (.gc) | rw-none doc-none test-none | experimental |
| Great Notions Embroidery Format (.gnc) | rw-none doc-none test-none | experimental |
| Gold Thread Embroidery Format (.gt) | rw-none doc-none test-none | experimental |
| Husqvarna Viking Embroidery Format (.hus) | rw-none doc-none test-none | experimental |
| Inbro Embroidery Format (.inb) | rw-none doc-none test-none | experimental |
| Embroidery Color Format (.inf) | rw-none doc-none test-none | experimental |
| Janome Embroidery Format (.jef) | rw-none doc-none test-none | experimental |
| Pfaff Embroidery Format (.ksm) | rw-none doc-none test-none | experimental |
| Pfaff Embroidery Format (.max) | rw-none doc-none test-none | experimental |
| Mitsubishi Embroidery Format (.mit) | rw-none doc-none test-none | experimental |
| Ameco Embroidery Format (.new) | rw-none doc-none test-none | experimental |
| Melco Embroidery Format (.ofm) | rw-none doc-none test-none | experimental |
| Pfaff Embroidery Format (.pcd) | rw-none doc-none test-none | experimental |
| Pfaff Embroidery Format (.pcm) | rw-none doc-none test-none | experimental |
| Pfaff Embroidery Format (.pcq) | rw-none doc-none test-none | experimental |
| Pfaff Embroidery Format (.pcs) | rw-none doc-none test-none | experimental |
| Brother Embroidery Format (.pec) | rw-none doc-none test-none | experimental |
| Brother Embroidery Format (.pel) | rw-none doc-none test-none | experimental |
| Brother Embroidery Format (.pem) | rw-none doc-none test-none | experimental |
| Brother Embroidery Format (.pes) | rw-none doc-none test-none | experimental |
| Brother Embroidery Format (.phb) | rw-none doc-none test-none | experimental |
| Brother Embroidery Format (.phc) | rw-none doc-none test-none | experimental |
| AutoCAD Embroidery Format (.plt) | rw-none doc-none test-none | experimental |
| RGB Embroidery Format (.rgb) | rw-none doc-none test-none | experimental |
| Janome Embroidery Format (.sew) | rw-none doc-none test-none | experimental |
| Husqvarna Viking Embroidery Format (.shv) | rw-none doc-none test-none | experimental |
| Sunstar Embroidery Format (.sst) | rw-none doc-none test-none | experimental |
| Data Stitch Embroidery Format (.stx) | rw-none doc-none test-none | experimental |
| Scalable Vector Graphics (.svg) | rw-none doc-none test-none | experimental |
| Pfaff Embroidery Format (.t01) | rw-none doc-none test-none | experimental |
| Pfaff Embroidery Format (.t09) | rw-none doc-none test-none | experimental |
| Happy Embroidery Format (.tap) | rw-none doc-none test-none | experimental |
| ThredWorks Embroidery Format (.thr) | rw-none doc-none test-none | experimental |
| Text File (.txt) | rw-none doc-none test-none | experimental |
| Barudan Embroidery Format (.u00) | rw-none doc-none test-none | experimental |
| Barudan Embroidery Format (.u01) | rw-none doc-none test-none | experimental |
| Pfaff Embroidery Format (.vip) | rw-none doc-none test-none | experimental |
| Pfaff Embroidery Format (.vp3) | rw-none doc-none test-none | experimental |
| Singer Embroidery Format (.xxx) | rw-none doc-none test-none | experimental |
| ZSK USA Embroidery Format (.zsk) | rw-none doc-none test-none | experimental 

## Toyota Embroidery Format (.100)
\index 100
\index Toyota

The Toyota 100 format is a stitch-only format that uses an external color file.

The stitch encoding is in 4 byte chunks.

### Toyota Embroidery Format (.10o)
\index 10o
\index Toyota

The Toyota 10o format is a stitch-only format that uses an external color file.

The stitch encoding is in 3 byte chunks.

## Bernina Embroidery Format (.art)
\index art
\index Bernina

We don't know much about this format. \todo Find a source.

## Bitmap Cache Embroidery Format (.bmc)
\index bmc
\index Bitmap Cache

We don't know much about this format. \todo Find a source.

## Bits and Volts Embroidery Format (.bro)
\index bro
\index Bits and Volts

The Bits and Volts bro format is a stitch-only format that uses an external color file.

The header is 256 bytes. There's a series of unknown variables in the header.

The stitch list uses a variable length encoding which is 2 bytes for any stitch

## Melco Embroidery Format (.cnd)
\index cnd
\index Melco

The Melco cnd format is a stitch-only format.

We don't know much about this format.

\todo Find a source.

## Embroidery Thread Color Format (.col)
\index col

An external color file format for formats that do not record their own colors. 

It is a human-readable format that has a header that is a single line containing only the number of threads in decimal followed by the windows line break  `\textbackslash{}r\textbackslash{}n}.

Then the rest of the file is a comma seperated value list of all threads with 4 values per line: the index of the thread then the red, green and blue channels of the color in that order.

### Example

If we had a pattern called "example" with four colors: black, red, magenta and cyan in that order then the file is (with the white space written out):

    example.col

    4\r\n
    0,0,0,0\r\n
    1,255,0,0\r\n
    2,0,255,0\r\n
    3,0,0,255\r\n

## Singer Embroidery Format (.csd)
\index csd
\index Singer

Stitch Only Format

## Comma Separated Values (.csv)
\index csv

Comma Seperated Values files aren't a universal system, here we aim to
offer a broad support. The dialect is detected based on the opening lines,
as each manufacturer should label their CSV files there.

### Embroidermodder 2.0 CSV Dialect

Our own version has the identifier comment line:

| Control Symbol | Type | Description |
|---|---|
| `#` | `COMMENT` | |
| `>` | `VARIABLE` | To store records of a pattern's width, height etc. This means that data stored in the header of say a .dst file is preserved. |
| `$` | `THREAD` | |
| `*` | `STITCH` | |
| `*` | `JUMP` | |
| `*` | `COLOR` | To change a color: used for trim as well |
| `*` | `END` | To end a pattern. |
| `*` | `UNKNOWN` | For any feature that we can't identify.

### EmBird CSV Dialect
\index Embird

## Barudan Embroidery Format (.dat)
\index dat
\index Barudan

Stitch Only Format

## Melco Embroidery Format (.dem)
\index dem
\index Melco

Stitch Only Format

## Barudan Embroidery Format (.dsb)
\index dsb
\index Barudan

* Stitch Only Format.
* [X] Basic Read Support
* [o] Basic Write Support
* [o] Well Tested Read
* [o] Well Tested Write

## Tajima Embroidery Format (.dst)
\index dst
\index Tajima

* Stitch Only Format.
* [X] Basic Read Support
* [X] Basic Write Support
* [ ] Well Tested Read
* [ ] Well Tested Write

.DST (Tajima) embroidery file read/write routines
Format comments are thanks to [tspilman@dalcoathletic.com](tspilman@dalcoathletic.com) who's
notes appeared at [http://www.wotsit.org](http://www.wotsit.org) under Tajima Format.

Other references: \cite kde_tajima , \cite acatina .

### Header

The header contains general information about the design. It is in lines of ASCII, so if you open a DST file as a text file, it's the only part that's easy to read. The line ending symbol is  `0x0D}. The header is necessary for the file to be read by most softwares and hardwares.

The header is 125 bytes of data followed by padding spaces to make it 512 bytes in total.

The lines are as follows.

| *Label* | *Size* | *Description* | *Example* |
|----|----|----|----|
| `LA:` | 17 | The design name with no path or extension. The space reserved is 16 characters, but the name must not be longer than 8 and be padded to 16 with spaces (0x20). | `"LA:Star            "` |
| `ST:` | 8 | The stitch count. An integer in the format  `\%07d}, that is: a 7 digit number padded by leading zeros. This is the total accross all possible stitch flags. | |
| `CO:` | 4 | The number of color changes (not to be confused with thread count, an all black design we would have the record \textbf{000}). An integer in the format  `\%03d}, that is: a 3 digit number padded by leading zeros. |
| `+X:` | 6 | The extent of the pattern in the postitive x direction in millimeters. An integer in the format  `\%05d}, that is: a 5 digit number padded by leading zeros. |
| `-X:` | 6 | The extent of the pattern in the negative x direction in millimeters. An integer in the format  `\%05d}, that is: a 5 digit integer padded by leading zeros. |
| `+Y:` | 6 | The extent of the pattern in the postitive y direction in millimeters. An integer in the format  `\%05d}, that is: a 5 digit integer padded by leading zeros. |
| `-Y:` | 6 | The extent of the pattern in the negative y direction in millimeters. An integer in the format  `\%05d}, that is: a 5 digit integer padded by leading zeros. |
| `AX:` | 7 | The difference of the end from the start in the x direction in 0.1mm, the first char should be the sign, followed by an integer in the format `%05d`, that is: a 5 digit integer padded by leading zeros. |
| `AY:` | 7 | The difference of the end from the start in the y direction in 0.1mm, the first char should be the sign, followed by an integer in the format `%05d`, that is: a 5 digit integer padded by leading zeros. |
| `MX:` | 7 | The x co-ordinate of the last point in the previous file should the design span multiple files. Like AX, it is the sign, followed by a 5 digit integer. If we have a one file design set it to zero. |
| `MY:` | 7 | The y co-ordinate of the last point in the previous file should the design span multiple files. Like AY, it is the sign, followed by a 5 digit integer. If we have a one file design set it to zero. |
| `PD:` | 10 | Information about multivolume designs.

### Stitch Data

Uses 3 byte per stitch encoding with the format as follows:

| *Bit* | *7* | *6* | *5* | *4* | *3* | *2* | *1* | *0* |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|
| Byte 0 | y+1 | y-1 | y+9 | y-9 | x-9 | x+9 | x-1 | x+1 |
| Byte 1 | y+3 | y-3 | y+27 | y-27 | x-27 | x+27 | x-3 | x+3 |
| Byte 2 | jump | color change | y+81 | y-81 | x-81 | x+81 | set | set |

T01 and Tap appear to use Tajima Ternary.
 
Where the stitch type is determined as:

* Normal Stitch `0b00000011 0x03`
* Jump Stitch `0b10000011 0x83`
* Stop/Change Color `0b11000011 0xC3`
* End Design `0b11110011 0xF3`

Inclusive or'ed with the last byte.

Note that the max stitch length is the largest sum of $1+3+9+27+81=121$ where the unit length is 0.1mm so 12.1mm. The coordinate system is right handed.

## ZSK USA Embroidery Format (.dsz)
\index dsz
\index ZSK USA

The ZSK USA dsz format is stitch-only.

## Drawing Exchange Format (.dxf)
\index dxf
\index AutoCAD
\index AutoDesk

Graphics format for drawing files designed and used by AudoDesk for their AutoCAD program. \cite{dxf_reference

## Embird Embroidery Format (.edr)
\index edr
\index Embird

Stitch Only Format

## Elna Embroidery Format (.emd)
\index emd
\index Elna

Stitch Only Format.

## Melco Embroidery Format (.exp)
\index exp
\index Melco

Stitch Only Format.

## Eltac Embroidery Format (.exy)
\index exy
\index Eltac

Stitch Only Format.

## Sierra Expanded Embroidery Format (.eys)
\index eys
\index Sierra Expanded

Stitch Only Format.

Smoothie G-Code Embroidery Format (.fxy)?

## Fortron Embroidery Format (.fxy)
\index fxy
\index Fortron

Stitch Only Format.

## Great Notions Embroidery Format (.gnc)
\index gnc
\index Great Notions

Stitch Only Format.

## Gold Thread Embroidery Format (.gt)
\index gt
\index Gold Thread

Stitch Only Format.

## Husqvarna Viking Embroidery Format (.hus)
\index hus
\index Husqvarna Viking

Stitch Only Format.

## Inbro Embroidery Format (.inb)
\index inb
\index Inbro

Stitch Only Format.

## Embroidery Color Format (.inf)
\index inf

Stitch Only Format.

## Janome Embroidery Format (.jef)
\index jef
\index Janome

Stitch Only Format.

## Pfaff professional Design format (.ksm)
\index ksm
\index Pfaff

Stitch Only Format.

## Pfaff Embroidery Format (.max)
\index max
\index Pfaff

Stitch Only Format.

## Mitsubishi Embroidery Format (.mit)
\index mit
\index Mitsubishi

Stitch Only Format.

## Ameco Embroidery Format (.new)
\index new
\index Ameco

Stitch Only Format.

## Melco Embroidery Format (.ofm)
\index ofm
\index Melco

Stitch Only Format.

## Pfaff PCD File Format (.pcd)
\index pcd
\index Pfaff

Stitch Only Format.

The format uses a signed 3 byte-length number type.

See the description here ([5](5)) for the overview of the format.

For an example of the format see ([11](11)).

## Pfaff Embroidery Format (.pcm)
\index pcm
\index Pfaff

The Pfaff pcm format is stitch-only.

## Pfaff Embroidery Format (.pcq)
\index pcq
\index Pfaff

The Pfaff pcq format is stitch-only.

## Pfaff Embroidery Format (.pcs)
\index pcs
\index Pfaff

The Pfaff pcs format is stitch-only.

## Brother Embroidery Format (.pec)
\index pec
\index Brother

The Brother pec format is stitch-only.

## Brother Embroidery Format (.pel)
\index pel
\index Brother

The Brother pel format is stitch-only.

## Brother Embroidery Format (.pem)
\index pem
\index Brother

The Brother pem format is stitch-only.

## Brother Embroidery Format (.pes)
\index pes
\index Brother

The Brother pes format is stitch-only.

## Brother Embroidery Format (.phb)
\index phb
\index Brother

The Brother phb format is stitch-only.

## Brother Embroidery Format (.phc)
\index phc
\index Brother

The Brother phc format is stitch-only.

## AutoCAD Embroidery Format (.plt)
\index plt
\index AutoCAD

The AutoCAD plt format is stitch-only.

## RGB Color File (.rgb)
\index rgb

The RGB format is a color-only format to act as an external color file for other formats.

## Janome Embroidery Format (.sew)
\index sew
\index Janome

The Janome sew format is stitch-only.

## Husqvarna Viking Embroidery Format (.shv)
\index shv
\index Husqvarna Viking

The Husqvarna Viking shv format is stitch-only.

## Sunstar Embroidery Format (.sst)
\index sst
\index Sunstar

The Sunstar sst format is stitch-only.

## Data Stitch Embroidery Format (.stx)
\index stx

The Data Stitch stx format is stitch-only.

## Scalable Vector Graphics (.svg)
\index svg

The scalable vector graphics (SVG) format is a graphics format
maintained by ...

## Pfaff Embroidery Format (.t01)
\index t01
\index Pfaff

The Pfaff t01 format is stitch-only.

### Pfaff Embroidery Format (.t09)
\index t09
\index Pfaff

The Pfaff t09 format is stitch-only.

## Happy Embroidery Format (.tap)
\index tap
\index Happy

The Happy tap format is stitch-only.

## ThredWorks Embroidery Format (.thr)
\index thr
\index ThreadWorks

The ThreadWorks thr format is stitch-only.

## Text File (.txt)
\index txt

The txt format is stitch-only and isn't associated with a specific company.

## Barudan Embroidery Format (.u00)
\index u00
\index Barudan

The Barudan u00 format is stitch-only.

## Barudan Embroidery Format (.u01)
\index u01
\index Barudan

The Barudan u01 format is stitch-only.

## Pfaff Embroidery Format (.vip)
\index vip
\index Pfaff

The Pfaff vip format is stitch-only.

## Pfaff Embroidery Format (.vp3)
\index vp3
\index Pfaff

The Pfaff vp3 format is stitch-only.

## Singer Embroidery Format (.xxx)
\index xxx
\index Singer

The Singer xxx format is stitch-only.

## ZSK USA Embroidery Format (.zsk)
\index zsk
\index ZSK USA

The ZSK USA zsk format is stitch-only.

## Unplaced


## Format Support

| *FORMAT* | *READ* | *WRITE* | *NOTES* |
|----------|--------|---------|---------|
| \index 10o `10o` | YES |  | read (need to fix external color loading) (maybe find out what ctrl | code flags of 0x10, 0x08, 0x04, and 0x02 mean) |
| \index 100 `100` |  |  | none (4 byte codes) 61 00 10 09 (type, type2, x, y ?) x | y (signed char) |
| \index art `art` |  |  | none |
| \index bro `bro` | YES |  | read (complete)(maybe figure out detail of header) |
| \index cnd `cnd` |  |  | none |
| \index col `col` |  |  | (color file no design) read(final) write(final) |
| \index csd `csd` | YES   |  | read (complete) |
| \index dat `dat` |  |  | read () |
| \index dem `dem` |  |  | none (looks like just encrypted cnd) |
| \index dsb `dsb` | YES   |  | read (unknown how well) (stitch data looks same as 10o) |
| \index dst `dst` | YES   |  | read (complete) / write(unknown) |
| \index dsz `dsz` | YES   |  | read (unknown) |
| \index dxf `dxf` |  |  | read (Port to C. needs refactored) |
| \index edr `edr` |  |  | read (C version is broken) / write (complete) |
| \index emd `emd` |  |  | read (unknown) |
| \index exp `exp` | YES   |  | read (unknown) / write(unknown) |
| \index exy `exy` | YES   |  | read (need to fix external color loading) |
| \index fxy `fxy` | YES   |  | read (need to fix external color loading) |
| \index gnc `gnc` |  |  | none |
| \index gt `gt` |  |  | read (need to fix external color loading) |
| \index hus `hus` | YES   |  | read (unknown) / write (C version is broken) |
| \index inb `inb` | YES   |  | read (buggy?) |
| \index jef `jef` | YES   |  | write (need to fix the offsets when it is moving to another spot) |
| \index ksm `ksm` | YES   |  | read (unknown) / write (unknown) |
| \index pcd `pcd` |  |  |  |
| \index pcm `pcm` |  |  | |
| \index pcq `pcq` |  |  | read (Port to C) |
| \index pcs `pcs` | BUGGY |  | read (buggy / colors are not correct / after reading, writing any other format is messed up) |
| \index pec `pec` |  |  | read / write (without embedded images, sometimes overlooks some stitches leaving a gap) |
| \index pel `pel` |  |  | none |
| \index pem `pem` |  |  | none |
| \index pes `pes` | YES   |  | |
| \index phb `phb` |  |  | |
| \index phc `phc` |  |  | |
| `rgb` |  |  | |
| `sew` | YES   |  | |
| `shv` |  |  | read (C version is broken) |
| `sst` |  |  | none |
| `svg` |  | YES   | |
| `tap` | YES   |  | read (unknown) |
| `u01` |  |  | |
| `vip` | YES   |  | |
| `vp3` | YES   |  | |
| `xxx` | YES   |  | |
| `zsk` |  |  | read (complete)

Support for Singer FHE, CHE (Compucon) formats?

\todo Josh, Review this file and move any info still valid or needing work into TODO comments in the actual
    libembroidery code. Many items in this list are out of date and do not reflect the current status of
    libembroidery. When finished, delete this file.
 

- Test that all formats read data in correct scale (format details should match other programs)
- Add which formats to work with to preferences.
- Check for memory leaks
- Update all formats without color to check for edr or rgb files
- Fix issues with DST (VERY important that DST work well)

## libembroidery C formats

| FORMAT | READ  | WRITE | NOTES |
|--------|-------|-------|-------|
| 10o    | YES   |       | read (need to fix external color loading) (maybe find out what ctrl code flags of 0x10, 0x08, 0x04, and 0x02 mean) |
| 100    |       |       | none (4 byte codes) 61 00 10 09 (type, type2, x, y ?) x & y (signed char) |
| art    |       |       | none |
| bro    | YES   |       | read (complete)(maybe figure out detail of header) |
| cnd    |       |       | none |
| col    |       |       | (color file no design) read(final) write(final) |
| csd    | YES   |       | read (complete) |
| dat    |       |       | read () |
| dem    |       |       | none (looks like just encrypted cnd) |
| dsb    | YES   |       | read (unknown how well) (stitch data looks same as 10o) |
| dst    | YES   |       | read (complete) / write(unknown) |
| dsz    | YES   |       | read (unknown) |
| dxf    |       |       | read (Port to C. needs refactored) |
| edr    |       |       | read (C version is broken) / write (complete) |
| emd    |       |       | read (unknown) |
| exp    | YES   |       | read (unknown) / write(unknown) |
| exy    | YES   |       | read (need to fix external color loading) |
| fxy    | YES   |       | read (need to fix external color loading) |
| gnc    |       |       | none |
| gt     |       |       | read (need to fix external color loading) |
| hus    | YES   |       | read (unknown) / write (C version is broken) |
| inb    | YES   |       | read (buggy?) |
| jef    | YES   |       | write (need to fix the offsets when it is moving to another spot) |
| ksm    | YES   |       | read (unknown) / write (unknown) |
| pcd    |       |       |  |
| pcm    |       |       |  |
| pcq    |       |       | read (Port to C) |
| pcs    | BUGGY |       | read (buggy / colors are not correct / after reading, writing any other format is messed up) |
| pec    |       |       | read / write (without embedded images, sometimes overlooks some stitches leaving a gap) |
| pel    |       |       | none |
| pem    |       |       | none |
| pes    | YES   |       |  |
| phb    |       |       |  |
| phc    |       |       |  |
| rgb    |       |       |  |
| sew    | YES   |       |  |
| shv    |       |       | read (C version is broken) |
| sst    |       |       | none |
| svg    |       | YES   |  |
| tap    | YES   |       | read (unknown) |
| u01    |       |       |  |
| vip    | YES   |       |  |
| vp3    | YES   |       |  |
| xxx    | YES   |       |  |
| zsk    |       |       | read (complete) |

Support for Singer FHE, CHE (Compucon) formats?
