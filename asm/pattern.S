/*!
 * \file pattern.S
 * \brief Managing the EmbPattern.
 *
 */

	.text
	.globl	formatTable
	.globl	svg_color_codes
	.globl	version_string
	.globl	NUMBINS
	.globl	epsilon
	.globl	black_thread
	.globl	emb_verbose

	.globl	embConstantPi

	.globl	difatEntriesInHeader
	.globl	sizeOfFatEntry
	.globl	sizeOfDifatEntry
	.globl	sizeOfChainingEntryAtEndOfDifatSector
	.globl	sizeOfDirectoryEntry

	.data

/*!
 * \brief Format Table.
 */
	.align	32
	.type	formatTable, @object
	.size	formatTable, 25620
formatTable:
	.string	".10o"
	zfill	195
	.string	"Toyota Embroidery Format"
	.zero	175
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".100"
	.zero	195
	.string	"Toyota Embroidery Format"
	.zero	175
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".art"
	.zero	195
	.string	"Bernina Embroidery Format"
	.zero	174
	.byte	32
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".bmc"
	.zero	195
	.string	"Bitmap Cache Embroidery Format"
	.zero	169
	.byte	32
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".bro"
	.zero	195
	.string	"Bits & Volts Embroidery Format"
	.zero	169
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".cnd"
	.zero	195
	.string	"Melco Embroidery Format"
	.zero	176
	.byte	32
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".col"
	.zero	195
	.string	"Embroidery Thread Color Format"
	.zero	169
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	1
	.long	0
	.long	0
	.string	".csd"
	.zero	195
	.string	"Singer Embroidery Format"
	.zero	175
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".csv"
	.zero	195
	.string	"Comma Separated Values Format"
	.zero	170
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".dat"
	.zero	195
	.string	"Barudan Embroidery Format"
	.zero	174
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".dem"
	.zero	195
	.string	"Melco Embroidery Format"
	.zero	176
	.byte	32
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".dsb"
	.zero	195
	.string	"Barudan Embroidery Format"
	.zero	174
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".dst"
	.zero	195
	.string	"Tajima Embroidery Format"
	.zero	175
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".dsz"
	.zero	195
	.string	"ZSK USA Embroidery Format"
	.zero	174
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".dxf"
	.zero	195
	.string	"Drawing Exchange Format"
	.zero	176
	.byte	32
	.byte	32
	.zero	2
	.long	2
	.long	0
	.long	0
	.long	0
	.string	".edr"
	.zero	195
	.string	"Embird Embroidery Format"
	.zero	175
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	1
	.long	0
	.long	0
	.string	".emd"
	.zero	195
	.string	"Elna Embroidery Format"
	.zero	177
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".exp"
	.zero	195
	.string	"Melco Embroidery Format"
	.zero	176
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".exy"
	.zero	195
	.string	"Eltac Embroidery Format"
	.zero	176
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".eys"
	.zero	195
	.string	"Sierra Expanded Embroidery Format"
	.zero	166
	.byte	32
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".fxy"
	.zero	195
	.string	"Fortron Embroidery Format"
	.zero	174
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".gc"
	.zero	196
	.string	"Smoothie G-Code Format"
	.zero	177
	.byte	32
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".gnc"
	.zero	195
	.string	"Great Notions Embroidery Format"
	.zero	168
	.byte	32
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".gt"
	.zero	196
	.string	"Gold Thread Embroidery Format"
	.zero	170
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".hus"
	.zero	195
	.string	"Husqvarna Viking Embroidery Format"
	.zero	165
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".inb"
	.zero	195
	.string	"Inbro Embroidery Format"
	.zero	176
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".inf"
	.zero	195
	.string	"Embroidery Color Format"
	.zero	176
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	1
	.long	0
	.long	0
	.string	".jef"
	.zero	195
	.string	"Janome Embroidery Format"
	.zero	175
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".ksm"
	.zero	195
	.string	"Pfaff Embroidery Format"
	.zero	176
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".max"
	.zero	195
	.string	"Pfaff Embroidery Format"
	.zero	176
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".mit"
	.zero	195
	.string	"Mitsubishi Embroidery Format"
	.zero	171
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".new"
	.zero	195
	.string	"Ameco Embroidery Format"
	.zero	176
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".ofm"
	.zero	195
	.string	"Melco Embroidery Format"
	.zero	176
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".pcd"
	.zero	195
	.string	"Pfaff Embroidery Format"
	.zero	176
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".pcm"
	.zero	195
	.string	"Pfaff Embroidery Format"
	.zero	176
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".pcq"
	.zero	195
	.string	"Pfaff Embroidery Format"
	.zero	176
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".pcs"
	.zero	195
	.string	"Pfaff Embroidery Format"
	.zero	176
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".pec"
	.zero	195
	.string	"Brother Embroidery Format"
	.zero	174
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".pel"
	.zero	195
	.string	"Brother Embroidery Format"
	.zero	174
	.byte	32
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".pem"
	.zero	195
	.string	"Brother Embroidery Format"
	.zero	174
	.byte	32
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".pes"
	.zero	195
	.string	"Brother Embroidery Format"
	.zero	174
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".phb"
	.zero	195
	.string	"Brother Embroidery Format"
	.zero	174
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".phc"
	.zero	195
	.string	"Brother Embroidery Format"
	.zero	174
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".plt"
	.zero	195
	.string	"AutoCAD Plot Drawing Format"
	.zero	172
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".rgb"
	.zero	195
	.string	"RGB Embroidery Format"
	.zero	178
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	1
	.long	0
	.long	0
	.string	".sew"
	.zero	195
	.string	"Janome Embroidery Format"
	.zero	175
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".shv"
	.zero	195
	.string	"Husqvarna Viking Embroidery Format"
	.zero	165
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".sst"
	.zero	195
	.string	"Sunstar Embroidery Format"
	.zero	174
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".stx"
	.zero	195
	.string	"Data Stitch Embroidery Format"
	.zero	170
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".svg"
	.zero	195
	.string	"Scalable Vector Graphics"
	.zero	175
	.byte	85
	.byte	85
	.zero	2
	.long	2
	.long	0
	.long	0
	.long	0
	.string	".t01"
	.zero	195
	.string	"Pfaff Embroidery Format"
	.zero	176
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".t09"
	.zero	195
	.string	"Pfaff Embroidery Format"
	.zero	176
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".tap"
	.zero	195
	.string	"Happy Embroidery Format"
	.zero	176
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	1
	.long	0
	.string	".thr"
	.zero	195
	.string	"ThredWorks Embroidery Format"
	.zero	171
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	1
	.long	0
	.long	0
	.string	".txt"
	.zero	195
	.string	"Text File"
	.zero	190
	.byte	32
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".u00"
	.zero	195
	.string	"Barudan Embroidery Format"
	.zero	174
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".u01"
	.zero	195
	.string	"Barudan Embroidery Format"
	.zero	174
	.byte	32
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".vip"
	.zero	195
	.string	"Pfaff Embroidery Format"
	.zero	176
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".vp3"
	.zero	195
	.string	"Pfaff Embroidery Format"
	.zero	176
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".xxx"
	.zero	195
	.string	"Singer Embroidery Format"
	.zero	175
	.byte	85
	.byte	85
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0
	.string	".zsk"
	.zero	195
	.string	"ZSK USA Embroidery Format"
	.zero	174
	.byte	85
	.byte	32
	.zero	2
	.long	1
	.long	0
	.long	0
	.long	0

/*!
 * \brief Version String.
 */
	.section	.rodata
.LC0:
	.string	"embroider v0.1"
	.section	.data.rel.local,"aw"
	.align 8
	.type	version_string, @object
	.size	version_string, 8
version_string:
	.quad	.LC0
	.section	.rodata
	.align 4
	.type	NUMBINS, @object
	.size	NUMBINS, 4
NUMBINS:
	.long	10
	.data
	.align 8
	.type	epsilon, @object
	.size	epsilon, 8
epsilon:
	.long	-400107883
	.long	1041313291
	.align 32
	.type	black_thread, @object
	.size	black_thread, 403
black_thread:
	.byte	0
	.byte	0
	.byte	0
	.string	"Black"
	.zero	194
	.string	"Black"
	.zero	194

	.bss

	.align 4
	.type	emb_verbose, @object
	.size	emb_verbose, 4
emb_verbose:
	.zero	4

	.section	.rodata

	.align 4
	.type	embConstantPi, @object
	.size	embConstantPi, 4
embConstantPi:
	.long	1078530011

	.align 4
	.type	difatEntriesInHeader, @object
	.size	difatEntriesInHeader, 4
difatEntriesInHeader:
	.long	109

	.align 4
	.type	sizeOfFatEntry, @object
	.size	sizeOfFatEntry, 4
sizeOfFatEntry:
	.long	4

	.align 4
	.type	sizeOfDifatEntry, @object
	.size	sizeOfDifatEntry, 4
sizeOfDifatEntry:
	.long	4

	.align	4
	.type	sizeOfChainingEntryAtEndOfDifatSector, @object
	.size	sizeOfChainingEntryAtEndOfDifatSector, 4
sizeOfChainingEntryAtEndOfDifatSector:
	.long	4

	.align	4
	.type	sizeOfDirectoryEntry, @object
	.size	sizeOfDirectoryEntry, 4
sizeOfDirectoryEntry:
	.long	128

	.data

/*!
 * \brief Format Table.
 */
	.align	32
	.type	svg_color_codes, @object
	.size	svg_color_codes, 41600
svg_color_codes:
	.string	"aliceblue"
	.zero	190
	.long	-984833
	.long	0
	.string	"antiquewhite"
	.zero	187
	.long	-332841
	.long	1
	.string	"aqua"
	.zero	195
	.long	-16711681
	.long	2
	.string	"aquamarine"
	.zero	189
	.long	-8388652
	.long	3
	.string	"azure"
	.zero	194
	.long	-983041
	.long	4
	.string	"beige"
	.zero	194
	.long	-657956
	.long	5
	.string	"bisque"
	.zero	193
	.long	-6972
	.long	6
	.string	"black"
	.zero	194
	.long	-16777216
	.long	7
	.string	"blanchedalmond"
	.zero	185
	.long	-5171
	.long	8
	.string	"blue"
	.zero	195
	.long	-16776961
	.long	9
	.string	"blueviolet"
	.zero	189
	.long	-7722014
	.long	10
	.string	"brown"
	.zero	194
	.long	-5952982
	.long	11
	.string	"burlywood"
	.zero	190
	.long	-2181093
	.long	12
	.string	"cadetblue"
	.zero	190
	.long	-10510688
	.long	13
	.string	"chartreuse"
	.zero	189
	.long	-8388864
	.long	14
	.string	"chocolate"
	.zero	190
	.long	-3003106
	.long	15
	.string	"coral"
	.zero	194
	.long	-33010
	.long	16
	.string	"cornflowerblue"
	.zero	185
	.long	-14917651
	.long	17
	.string	"cornsilk"
	.zero	191
	.long	-1828
	.long	18
	.string	"crimson"
	.zero	192
	.long	-2355652
	.long	19
	.string	"cyan"
	.zero	195
	.long	-16711681
	.long	20
	.string	"darkblue"
	.zero	191
	.long	-16777077
	.long	21
	.string	"darkcyan"
	.zero	191
	.long	-16741493
	.long	22
	.string	"darkgoldenrod"
	.zero	186
	.long	-4711925
	.long	23
	.string	"darkgray"
	.zero	191
	.long	-5658199
	.long	24
	.string	"darkgreen"
	.zero	190
	.long	-16770048
	.long	25
	.string	"darkgrey"
	.zero	191
	.long	-5658199
	.long	26
	.string	"darkkhaki"
	.zero	190
	.long	-4343957
	.long	27
	.string	"darkmagenta"
	.zero	188
	.long	-7667573
	.long	28
	.string	"darkolivegreen"
	.zero	185
	.long	-15897809
	.long	29
	.string	"darkorange"
	.zero	189
	.long	-29696
	.long	30
	.string	"darkorchid"
	.zero	189
	.long	-12644660
	.long	31
	.string	"darkred"
	.zero	192
	.long	-7667712
	.long	32
	.string	"darksalmon"
	.zero	189
	.long	-1491846
	.long	33
	.string	"darkseagreen"
	.zero	187
	.long	-7357297
	.long	34
	.string	"darkslateblue"
	.zero	186
	.long	-14795381
	.long	35
	.string	"darkslategray"
	.zero	186
	.long	-13676721
	.long	36
	.string	"darkslategrey"
	.zero	186
	.long	-13676721
	.long	37
	.string	"darkturquoise"
	.zero	186
	.long	-16724271
	.long	38
	.string	"darkviolet"
	.zero	189
	.long	-10616621
	.long	39
	.string	"deeppink"
	.zero	191
	.long	-61859
	.long	40
	.string	"deepskyblue"
	.zero	188
	.long	-16728065
	.long	41
	.string	"dimgray"
	.zero	192
	.long	-13816531
	.long	42
	.string	"dimgrey"
	.zero	192
	.long	-13816531
	.long	43
	.string	"dodgerblue"
	.zero	189
	.long	-14787841
	.long	44
	.string	"firebrick"
	.zero	190
	.long	-5109238
	.long	45
	.string	"floralwhite"
	.zero	188
	.long	-1296
	.long	46
	.string	"forestgreen"
	.zero	188
	.long	-16086262
	.long	47
	.string	"fuchsia"
	.zero	192
	.long	-65281
	.long	48
	.string	"gainsboro"
	.zero	190
	.long	-2302756
	.long	49
	.string	"ghostwhite"
	.zero	189
	.long	-460545
	.long	50
	.string	"gold"
	.zero	195
	.long	-10496
	.long	51
	.string	"goldenrod"
	.zero	190
	.long	-2448114
	.long	52
	.string	"gray"
	.zero	195
	.long	-15856114
	.long	53
	.string	"grey"
	.zero	195
	.long	-15856114
	.long	54
	.string	"green"
	.zero	194
	.long	-16773632
	.long	55
	.string	"greenyellow"
	.zero	188
	.long	-5374161
	.long	56
	.string	"honeydew"
	.zero	191
	.long	-983056
	.long	57
	.string	"hotpink"
	.zero	192
	.long	-53836
	.long	58
	.string	"indianred"
	.zero	190
	.long	-3318692
	.long	59
	.string	"indigo"
	.zero	193
	.long	-11862006
	.long	60
	.string	"ivory"
	.zero	194
	.long	-16
	.long	61
	.string	"khaki"
	.zero	194
	.long	-989556
	.long	62
	.string	"lavender"
	.zero	191
	.long	-1644806
	.long	63
	.string	"lavenderblush"
	.zero	186
	.long	-3851
	.long	64
	.string	"lawngreen"
	.zero	190
	.long	-8586240
	.long	65
	.string	"lemonchiffon"
	.zero	187
	.long	-1331
	.long	66
	.string	"lightblue"
	.zero	190
	.long	-5383962
	.long	67
	.string	"lightcoral"
	.zero	189
	.long	-1044978
	.long	68
	.string	"lightcyan"
	.zero	190
	.long	-2031617
	.long	69
	.string	"lightgoldenrodyellow"
	.zero	179
	.long	-329006
	.long	70
	.string	"lightgray"
	.zero	190
	.long	-2894893
	.long	71
	.string	"lightgreen"
	.zero	189
	.long	-10817958
	.long	72
	.string	"lightgrey"
	.zero	190
	.long	-2894893
	.long	73
	.string	"lightpink"
	.zero	190
	.long	-18751
	.long	74
	.string	"lightsalmon"
	.zero	188
	.long	-24454
	.long	75
	.string	"lightseagreen"
	.zero	186
	.long	-15813974
	.long	76
	.string	"lightskyblue"
	.zero	187
	.long	-14954758
	.long	77
	.string	"lightslategray"
	.zero	185
	.long	-11716033
	.long	78
	.string	"lightslategrey"
	.zero	185
	.long	-11716033
	.long	79
	.string	"lightsteelblue"
	.zero	185
	.long	-5192482
	.long	80
	.string	"lightyellow"
	.zero	188
	.long	-32
	.long	81
	.string	"lime"
	.zero	195
	.long	-16711936
	.long	82
	.string	"limegreen"
	.zero	190
	.long	-15807218
	.long	83
	.string	"linen"
	.zero	194
	.long	-331546
	.long	84
	.string	"magenta"
	.zero	192
	.long	-65281
	.long	85
	.string	"maroon"
	.zero	193
	.long	-15859712
	.long	86
	.string	"mediumaquamarine"
	.zero	183
	.long	-13972054
	.long	87
	.string	"mediumblue"
	.zero	189
	.long	-16777011
	.long	88
	.string	"mediumorchid"
	.zero	187
	.long	-4583981
	.long	89
	.string	"mediumpurple"
	.zero	187
	.long	-10670373
	.long	90
	.string	"mediumseagreen"
	.zero	185
	.long	-12799185
	.long	91
	.string	"mediumslateblue"
	.zero	184
	.long	-8704786
	.long	92
	.string	"mediumspringgreen"
	.zero	182
	.long	-16713062
	.long	93
	.string	"mediumturquoise"
	.zero	184
	.long	-14757428
	.long	94
	.string	"mediumvioletred"
	.zero	184
	.long	-3731699
	.long	95
	.string	"midnightblue"
	.zero	187
	.long	-15921874
	.long	96
	.string	"mintcream"
	.zero	190
	.long	-655366
	.long	97
	.string	"mistyrose"
	.zero	190
	.long	-6943
	.long	98
	.string	"moccasin"
	.zero	191
	.long	-6987
	.long	99
	.string	"navajowhite"
	.zero	188
	.long	-8531
	.long	100
	.string	"navy"
	.zero	195
	.long	-16777202
	.long	101
	.string	"oldlace"
	.zero	192
	.long	-133658
	.long	102
	.string	"olive"
	.zero	194
	.long	-15856128
	.long	103
	.string	"olivedrab"
	.zero	190
	.long	-9728501
	.long	104
	.string	"orange"
	.zero	193
	.long	-23296
	.long	105
	.string	"orangered"
	.zero	190
	.long	-54016
	.long	106
	.string	"orchid"
	.zero	193
	.long	-2478378
	.long	107
	.string	"palegoldenrod"
	.zero	186
	.long	-1120086
	.long	109
	.string	"palegreen"
	.zero	190
	.long	-12649666
	.long	110
	.string	"paleturquoise"
	.zero	186
	.long	-5247250
	.long	111
	.string	"palevioletred"
	.zero	186
	.long	-2412963
	.long	112
	.string	"papayawhip"
	.zero	189
	.long	-4139
	.long	113
	.string	"peachpuff"
	.zero	190
	.long	-9543
	.long	114
	.string	"peru"
	.zero	195
	.long	-3338945
	.long	115
	.string	"pink"
	.zero	195
	.long	-16181
	.long	116
	.string	"plum"
	.zero	195
	.long	-2252579
	.long	117
	.string	"powderblue"
	.zero	189
	.long	-5185306
	.long	118
	.string	"purple"
	.zero	193
	.long	-15859698
	.long	119
	.string	"red"
	.zero	196
	.long	-65536
	.long	120
	.string	"rosybrown"
	.zero	190
	.long	-4419697
	.long	121
	.string	"royalblue"
	.zero	190
	.long	-14864927
	.long	122
	.string	"saddlebrown"
	.zero	188
	.long	-7656179
	.long	123
	.string	"salmon"
	.zero	193
	.long	-389602
	.long	124
	.string	"sandybrown"
	.zero	189
	.long	-744388
	.long	125
	.string	"seagreen"
	.zero	191
	.long	-13726949
	.long	126
	.string	"seashell"
	.zero	191
	.long	-2578
	.long	127
	.string	"sienna"
	.zero	193
	.long	-6288851
	.long	128
	.string	"silver"
	.zero	193
	.long	-4144960
	.long	129
	.string	"skyblue"
	.zero	192
	.long	-14954773
	.long	130
	.string	"slateblue"
	.zero	190
	.long	-9807155
	.long	131
	.string	"slategray"
	.zero	190
	.long	-13758886
	.long	132
	.string	"slategrey"
	.zero	190
	.long	-13758886
	.long	133
	.string	"snow"
	.zero	195
	.long	-1286
	.long	134
	.string	"springgreen"
	.zero	188
	.long	-16711809
	.long	135
	.string	"steelblue"
	.zero	190
	.long	-13759820
	.long	136
	.string	"tan"
	.zero	196
	.long	-2968436
	.long	137
	.string	"teal"
	.zero	195
	.long	-16773618
	.long	138
	.string	"thistle"
	.zero	192
	.long	-2572328
	.long	139
	.string	"tomato"
	.zero	193
	.long	-49361
	.long	140
	.string	"turquoise"
	.zero	190
	.long	-14884656
	.long	141
	.string	"violet"
	.zero	193
	.long	-1176850
	.long	142
	.string	"wheat"
	.zero	194
	.long	-663885
	.long	143
	.string	"white"
	.zero	194
	.long	-1
	.long	144
	.string	"whitesmoke"
	.zero	189
	.long	-657931
	.long	145
	.string	"yellow"
	.zero	193
	.long	-256
	.long	146
	.string	"yellowgreen"
	.zero	188
	.long	-6632178
	.long	147
	.string	"END"
	.zero	196
	.long	0
	.long	-1
	.zero	10816
	.globl	brand_codes
	.section	.data.rel.local
	.align 32
	.type	brand_codes, @object
	.size	brand_codes, 21600
brand_codes:
	.quad	svg_color_codes
	.long	100
	.string	"DXF"
	.zero	196
	.zero	4
	.quad	svg_color_codes
	.long	100
	.string	"HUS"
	.zero	196
	.zero	4
	.quad	svg_color_codes
	.long	100
	.string	"JEF"
	.zero	196
	.zero	4
	.quad	svg_color_codes
	.long	100
	.string	"SHV"
	.zero	196
	.zero	4
	.quad	svg_color_codes
	.long	100
	.string	"PCM"
	.zero	196
	.zero	4
	.quad	svg_color_codes
	.long	100
	.string	"PEC"
	.zero	196
	.zero	4
	.quad	svg_color_codes
	.long	200
	.string	"Scalable Vector Graphics"
	.zero	175
	.zero	4
	.zero	20088
	.text
	.globl	string_whitespace
	.type	string_whitespace, @function
string_whitespace:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L9:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	je	.L10
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$9, %al
	je	.L11
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$13, %al
	je	.L12
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	je	.L13
	movl	-4(%rbp), %eax
	jmp	.L8
.L10:
	nop
	jmp	.L4
.L11:
	nop
	jmp	.L4
.L12:
	nop
	jmp	.L4
.L13:
	nop
.L4:
	addl	$1, -4(%rbp)
.L2:
	cmpl	$199, -4(%rbp)
	jle	.L9
	movl	-4(%rbp), %eax
.L8:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	string_whitespace, .-string_whitespace
	.globl	string_len
	.type	string_len, @function
string_len:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L15
.L18:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L16
	movl	-4(%rbp), %eax
	jmp	.L17
.L16:
	addl	$1, -4(%rbp)
.L15:
	cmpl	$199, -4(%rbp)
	jle	.L18
	movl	$-1, %eax
.L17:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	string_len, .-string_len
	.globl	string_rchar
	.type	string_rchar, @function
string_rchar:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movb	%al, -28(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	string_len
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	.L20
.L23:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, -28(%rbp)
	jne	.L21
	movl	-4(%rbp), %eax
	jmp	.L22
.L21:
	subl	$1, -4(%rbp)
.L20:
	cmpl	$0, -4(%rbp)
	jns	.L23
	movl	$0, %eax
.L22:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	string_rchar, .-string_rchar
	.globl	embColor_fromHexStr
	.type	embColor_fromHexStr, @function
embColor_fromHexStr:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -9(%rbp)
	movq	-24(%rbp), %rax
	movzbl	1(%rax), %eax
	movb	%al, -8(%rbp)
	movb	$0, -7(%rbp)
	movq	-24(%rbp), %rax
	movzbl	2(%rax), %eax
	movb	%al, -12(%rbp)
	movq	-24(%rbp), %rax
	movzbl	3(%rax), %eax
	movb	%al, -11(%rbp)
	movb	$0, -10(%rbp)
	movq	-24(%rbp), %rax
	movzbl	4(%rax), %eax
	movb	%al, -15(%rbp)
	movq	-24(%rbp), %rax
	movzbl	5(%rax), %eax
	movb	%al, -14(%rbp)
	movb	$0, -13(%rbp)
	leaq	-9(%rbp), %rax
	movl	$16, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movb	%al, -6(%rbp)
	leaq	-12(%rbp), %rax
	movl	$16, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movb	%al, -5(%rbp)
	leaq	-15(%rbp), %rax
	movl	$16, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movb	%al, -4(%rbp)
	movzwl	-6(%rbp), %eax
	movw	%ax, -3(%rbp)
	movzbl	-4(%rbp), %eax
	movb	%al, -1(%rbp)
	movl	$0, %eax
	movzwl	-3(%rbp), %edx
	movzwl	%dx, %edx
	movw	$0, %ax
	orq	%rdx, %rax
	movzbl	-1(%rbp), %edx
	movzbl	%dl, %edx
	salq	$16, %rdx
	andq	$-16711681, %rax
	orq	%rdx, %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	embColor_fromHexStr, .-embColor_fromHexStr
	.globl	embColor_make
	.type	embColor_make, @function
embColor_make:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%esi, %ecx
	movl	%edx, %eax
	movl	%edi, %edx
	movb	%dl, -20(%rbp)
	movl	%ecx, %edx
	movb	%dl, -24(%rbp)
	movb	%al, -28(%rbp)
	movzbl	-20(%rbp), %eax
	movb	%al, -6(%rbp)
	movzbl	-24(%rbp), %eax
	movb	%al, -4(%rbp)
	movzbl	-28(%rbp), %eax
	movb	%al, -5(%rbp)
	movzwl	-6(%rbp), %eax
	movw	%ax, -3(%rbp)
	movzbl	-4(%rbp), %eax
	movb	%al, -1(%rbp)
	movl	$0, %eax
	movzwl	-3(%rbp), %edx
	movzwl	%dx, %edx
	movw	$0, %ax
	orq	%rdx, %rax
	movzbl	-1(%rbp), %edx
	movzbl	%dl, %edx
	salq	$16, %rdx
	andq	$-16711681, %rax
	orq	%rdx, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	embColor_make, .-embColor_make
	.globl	emb_swap
	.type	emb_swap, @function
emb_swap:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movb	%al, -1(%rbp)
	movl	-32(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rcx
	movq	-24(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	movl	-32(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-1(%rbp), %eax
	movb	%al, (%rdx)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	emb_swap, .-emb_swap
	.globl	fix_endian
	.type	fix_endian, @function
fix_endian:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	cmpl	$0, -16(%rbp)
	je	.L32
	cmpl	$2, -12(%rbp)
	jne	.L31
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_swap
.L31:
	cmpl	$4, -12(%rbp)
	jne	.L32
	movq	-8(%rbp), %rax
	movl	$3, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_swap
	movq	-8(%rbp), %rax
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	emb_swap
.L32:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	fix_endian, .-fix_endian
	.section	.rodata
	.align 8
.LC1:
	.string	"ERROR: Failed to read a int16_t."
	.text
	.globl	emb_read_i16
	.type	emb_read_i16, @function
emb_read_i16:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-2(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	je	.L34
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L36
.L34:
	leaq	-2(%rbp), %rax
	movl	$0, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fix_endian
	leaq	-2(%rbp), %rax
	movzwl	(%rax), %eax
.L36:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	emb_read_i16, .-emb_read_i16
	.section	.rodata
	.align 8
.LC2:
	.string	"ERROR: Failed to read a uint16_t."
	.text
	.globl	emb_read_u16
	.type	emb_read_u16, @function
emb_read_u16:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-2(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	je	.L38
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L40
.L38:
	leaq	-2(%rbp), %rax
	movl	$0, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fix_endian
	leaq	-2(%rbp), %rax
	movzwl	(%rax), %eax
.L40:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	emb_read_u16, .-emb_read_u16
	.section	.rodata
	.align 8
.LC3:
	.string	"ERROR: Failed to read a int32_t."
	.text
	.globl	emb_read_i32
	.type	emb_read_i32, @function
emb_read_i32:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-4(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$4, %rax
	je	.L42
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L44
.L42:
	leaq	-4(%rbp), %rax
	movl	$0, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fix_endian
	leaq	-4(%rbp), %rax
	movl	(%rax), %eax
.L44:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	emb_read_i32, .-emb_read_i32
	.section	.rodata
	.align 8
.LC4:
	.string	"ERROR: Failed to read a uint32_t."
	.text
	.globl	emb_read_u32
	.type	emb_read_u32, @function
emb_read_u32:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-4(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$4, %rax
	je	.L46
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L48
.L46:
	leaq	-4(%rbp), %rax
	movl	$0, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fix_endian
	leaq	-4(%rbp), %rax
	movl	(%rax), %eax
.L48:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	emb_read_u32, .-emb_read_u32
	.globl	emb_read_i16be
	.type	emb_read_i16be, @function
emb_read_i16be:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-2(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	je	.L50
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L52
.L50:
	leaq	-2(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fix_endian
	leaq	-2(%rbp), %rax
	movzwl	(%rax), %eax
.L52:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	emb_read_i16be, .-emb_read_i16be
	.globl	emb_read_u16be
	.type	emb_read_u16be, @function
emb_read_u16be:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-2(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$2, %rax
	je	.L54
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L56
.L54:
	leaq	-2(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fix_endian
	leaq	-2(%rbp), %rax
	movzwl	(%rax), %eax
.L56:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	emb_read_u16be, .-emb_read_u16be
	.globl	emb_read_i32be
	.type	emb_read_i32be, @function
emb_read_i32be:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-4(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$4, %rax
	je	.L58
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L60
.L58:
	leaq	-4(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fix_endian
	leaq	-4(%rbp), %rax
	movl	(%rax), %eax
.L60:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	emb_read_i32be, .-emb_read_i32be
	.globl	emb_read_u32be
	.type	emb_read_u32be, @function
emb_read_u32be:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-4(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$4, %rax
	je	.L62
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L64
.L62:
	leaq	-4(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fix_endian
	leaq	-4(%rbp), %rax
	movl	(%rax), %eax
.L64:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	emb_read_u32be, .-emb_read_u32be
	.globl	decode_t01_record
	.type	decode_t01_record, @function
decode_t01_record:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	decode_tajima_ternary
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	cmpb	$-13, %al
	jne	.L66
	movq	-32(%rbp), %rax
	movl	$16, (%rax)
	movl	$1, %eax
	jmp	.L67
.L66:
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$195, %eax
	cmpl	$195, %eax
	je	.L68
	cmpl	$195, %eax
	jg	.L69
	cmpl	$3, %eax
	je	.L70
	cmpl	$131, %eax
	je	.L71
	jmp	.L69
.L70:
	movq	-32(%rbp), %rax
	movl	$0, (%rax)
	jmp	.L72
.L71:
	movq	-32(%rbp), %rax
	movl	$2, (%rax)
	jmp	.L72
.L68:
	movq	-32(%rbp), %rax
	movl	$4, (%rax)
	jmp	.L72
.L69:
	movq	-32(%rbp), %rax
	movl	$0, (%rax)
	nop
.L72:
	movl	$1, %eax
.L67:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	decode_t01_record, .-decode_t01_record
	.globl	encode_t01_record
	.type	encode_t01_record, @function
encode_t01_record:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movl	%ecx, -20(%rbp)
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %ecx
	movq	-8(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	encode_tajima_ternary
	testl	%eax, %eax
	je	.L78
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$2, %rax
	orl	$3, %edx
	movb	%dl, (%rax)
	movl	-20(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L76
	movq	-8(%rbp), %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movb	$-13, (%rax)
.L76:
	movl	-20(%rbp), %eax
	andl	$3, %eax
	testl	%eax, %eax
	je	.L77
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$2, %rax
	orl	$-125, %edx
	movb	%dl, (%rax)
.L77:
	movl	-20(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L73
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$2, %rax
	orl	$-61, %edx
	movb	%dl, (%rax)
	jmp	.L73
.L78:
	nop
.L73:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	encode_t01_record, .-encode_t01_record
	.section	.rodata
	.align 8
.LC5:
	.string	"ERROR: format-t01.c encode_record(), "
	.align 8
.LC6:
	.string	"x is not in valid range [-121,121] , x = %d\n"
	.align 8
.LC7:
	.string	"y is not in valid range [-121,121] , y = %d\n"
	.align 8
.LC8:
	.string	"ERROR: format-dst.c encode_record(), "
.LC9:
	.string	"x should be zero yet x = %d\n"
.LC10:
	.string	"y should be zero yet y = %d\n"
	.text
	.globl	encode_tajima_ternary
	.type	encode_tajima_ternary, @function
encode_tajima_ternary:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movq	-8(%rbp), %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movb	$0, (%rax)
	cmpl	$121, -12(%rbp)
	jg	.L80
	cmpl	$-121, -12(%rbp)
	jge	.L81
.L80:
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L82
.L81:
	cmpl	$121, -16(%rbp)
	jg	.L83
	cmpl	$-121, -16(%rbp)
	jge	.L84
.L83:
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L82
.L84:
	cmpl	$40, -12(%rbp)
	jle	.L85
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$2, %rax
	orl	$4, %edx
	movb	%dl, (%rax)
	subl	$81, -12(%rbp)
.L85:
	cmpl	$-40, -12(%rbp)
	jge	.L86
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$2, %rax
	orl	$8, %edx
	movb	%dl, (%rax)
	addl	$81, -12(%rbp)
.L86:
	cmpl	$13, -12(%rbp)
	jle	.L87
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$1, %rax
	orl	$4, %edx
	movb	%dl, (%rax)
	subl	$27, -12(%rbp)
.L87:
	cmpl	$-13, -12(%rbp)
	jge	.L88
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$1, %rax
	orl	$8, %edx
	movb	%dl, (%rax)
	addl	$27, -12(%rbp)
.L88:
	cmpl	$4, -12(%rbp)
	jle	.L89
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	orl	$4, %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	subl	$9, -12(%rbp)
.L89:
	cmpl	$-4, -12(%rbp)
	jge	.L90
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	orl	$8, %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	addl	$9, -12(%rbp)
.L90:
	cmpl	$1, -12(%rbp)
	jle	.L91
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$1, %rax
	orl	$1, %edx
	movb	%dl, (%rax)
	subl	$3, -12(%rbp)
.L91:
	cmpl	$-1, -12(%rbp)
	jge	.L92
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$1, %rax
	orl	$2, %edx
	movb	%dl, (%rax)
	addl	$3, -12(%rbp)
.L92:
	cmpl	$0, -12(%rbp)
	jle	.L93
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	orl	$1, %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	subl	$1, -12(%rbp)
.L93:
	cmpl	$0, -12(%rbp)
	jns	.L94
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	orl	$2, %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	addl	$1, -12(%rbp)
.L94:
	cmpl	$0, -12(%rbp)
	je	.L95
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L82
.L95:
	cmpl	$40, -16(%rbp)
	jle	.L96
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$2, %rax
	orl	$32, %edx
	movb	%dl, (%rax)
	subl	$81, -16(%rbp)
.L96:
	cmpl	$-40, -16(%rbp)
	jge	.L97
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$2, %rax
	orl	$16, %edx
	movb	%dl, (%rax)
	addl	$81, -16(%rbp)
.L97:
	cmpl	$13, -16(%rbp)
	jle	.L98
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$1, %rax
	orl	$32, %edx
	movb	%dl, (%rax)
	subl	$27, -16(%rbp)
.L98:
	cmpl	$-13, -16(%rbp)
	jge	.L99
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$1, %rax
	orl	$16, %edx
	movb	%dl, (%rax)
	addl	$27, -16(%rbp)
.L99:
	cmpl	$4, -16(%rbp)
	jle	.L100
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	orl	$32, %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	subl	$9, -16(%rbp)
.L100:
	cmpl	$-4, -16(%rbp)
	jge	.L101
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	orl	$16, %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	addl	$9, -16(%rbp)
.L101:
	cmpl	$1, -16(%rbp)
	jle	.L102
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$1, %rax
	orl	$-128, %edx
	movb	%dl, (%rax)
	subl	$3, -16(%rbp)
.L102:
	cmpl	$-1, -16(%rbp)
	jge	.L103
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	addq	$1, %rax
	orl	$64, %edx
	movb	%dl, (%rax)
	addl	$3, -16(%rbp)
.L103:
	cmpl	$0, -16(%rbp)
	jle	.L104
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	orl	$-128, %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	subl	$1, -16(%rbp)
.L104:
	cmpl	$0, -16(%rbp)
	jns	.L105
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	orl	$64, %eax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	addl	$1, -16(%rbp)
.L105:
	cmpl	$0, -16(%rbp)
	je	.L106
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L82
.L106:
	movl	$1, %eax
.L82:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	encode_tajima_ternary, .-encode_tajima_ternary
	.globl	decode_tajima_ternary
	.type	decode_tajima_ternary, @function
decode_tajima_ternary:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-16(%rbp), %rax
	movl	$0, (%rax)
	movq	-24(%rbp), %rax
	movl	$0, (%rax)
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L108
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
.L108:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L109
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
.L109:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L110
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	9(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
.L110:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L111
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-9(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
.L111:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jns	.L112
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L112:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L113
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L113:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L114
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	9(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L114:
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L115
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	-9(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L115:
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L116
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	3(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
.L116:
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L117
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-3(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
.L117:
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L118
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	27(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
.L118:
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L119
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-27(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
.L119:
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jns	.L120
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	3(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L120:
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L121
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	-3(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L121:
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L122
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	27(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L122:
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L123
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	-27(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L123:
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L124
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	81(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
.L124:
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L125
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	leal	-81(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
.L125:
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L126
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	81(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L126:
	movq	-8(%rbp), %rax
	addq	$2, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L128
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	-81(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L128:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	decode_tajima_ternary, .-decode_tajima_ternary
	.section	.rodata
	.align 8
.LC11:
	.string	"ERROR: format-pcs.c pcsEncode(), file argument is null"
	.text
	.globl	pfaffEncode
	.type	pfaffEncode, @function
pfaffEncode:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	movb	$0, -1(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L130
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L129
.L130:
	movl	-28(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	write_24bit
	movl	-32(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	write_24bit
	movl	-36(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L132
	movzbl	-1(%rbp), %eax
	orl	$1, %eax
	movb	%al, -1(%rbp)
.L132:
	movl	-36(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L133
	movzbl	-1(%rbp), %eax
	orl	$4, %eax
	movb	%al, -1(%rbp)
.L133:
	movq	-24(%rbp), %rdx
	leaq	-1(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
.L129:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE25:
	.size	pfaffEncode, .-pfaffEncode
	.globl	pfaffDecode
	.type	pfaffDecode, @function
pfaffDecode:
.LFB26:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%esi, %ecx
	movl	%edx, %eax
	movl	%edi, %edx
	movb	%dl, -20(%rbp)
	movl	%ecx, %edx
	movb	%dl, -24(%rbp)
	movb	%al, -28(%rbp)
	movzbl	-20(%rbp), %eax
	movzbl	-24(%rbp), %edx
	sall	$8, %edx
	addl	%eax, %edx
	movzbl	-28(%rbp), %eax
	sall	$16, %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	cmpl	$8388607, -4(%rbp)
	jle	.L135
	movl	-4(%rbp), %eax
	notl	%eax
	andl	$8388607, %eax
	movl	$1, %edx
	subl	%eax, %edx
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%edx, %xmm0
	jmp	.L136
.L135:
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-4(%rbp), %xmm0
.L136:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	pfaffDecode, .-pfaffDecode
	.globl	mitEncodeStitch
	.type	mitEncodeStitch, @function
mitEncodeStitch:
.LFB27:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -4(%rbp)
	pxor	%xmm0, %xmm0
	comiss	-4(%rbp), %xmm0
	jbe	.L142
	movss	-4(%rbp), %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	orl	$-128, %eax
	jmp	.L140
.L142:
	cvttss2sil	-4(%rbp), %eax
.L140:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	mitEncodeStitch, .-mitEncodeStitch
	.globl	mitDecodeStitch
	.type	mitDecodeStitch, @function
mitDecodeStitch:
.LFB28:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	testb	%al, %al
	jns	.L144
	movzbl	-4(%rbp), %eax
	andl	$31, %eax
	negl	%eax
	jmp	.L145
.L144:
	movzbl	-4(%rbp), %eax
.L145:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	mitDecodeStitch, .-mitDecodeStitch
	.globl	decodeNewStitch
	.type	decodeNewStitch, @function
decodeNewStitch:
.LFB29:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movzbl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE29:
	.size	decodeNewStitch, .-decodeNewStitch
	.globl	fpad
	.type	fpad, @function
fpad:
.LFB30:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movl	%edx, -32(%rbp)
	movb	%al, -28(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L149
.L150:
	movq	-24(%rbp), %rdx
	leaq	-28(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	addl	$1, -4(%rbp)
.L149:
	movl	-4(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jl	.L150
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE30:
	.size	fpad, .-fpad
	.globl	emb_write_i16
	.type	emb_write_i16, @function
emb_write_i16:
.LFB31:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movw	%ax, -28(%rbp)
	leaq	-28(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fix_endian
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE31:
	.size	emb_write_i16, .-emb_write_i16
	.globl	emb_write_u16
	.type	emb_write_u16, @function
emb_write_u16:
.LFB32:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movw	%ax, -28(%rbp)
	leaq	-28(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fix_endian
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE32:
	.size	emb_write_u16, .-emb_write_u16
	.globl	emb_write_i16be
	.type	emb_write_i16be, @function
emb_write_i16be:
.LFB33:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movw	%ax, -28(%rbp)
	leaq	-28(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fix_endian
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE33:
	.size	emb_write_i16be, .-emb_write_i16be
	.globl	emb_write_u16be
	.type	emb_write_u16be, @function
emb_write_u16be:
.LFB34:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movw	%ax, -28(%rbp)
	leaq	-28(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	fix_endian
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$2, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE34:
	.size	emb_write_u16be, .-emb_write_u16be
	.globl	emb_write_i32
	.type	emb_write_i32, @function
emb_write_i32:
.LFB35:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	leaq	-28(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fix_endian
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE35:
	.size	emb_write_i32, .-emb_write_i32
	.globl	emb_write_u32
	.type	emb_write_u32, @function
emb_write_u32:
.LFB36:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	leaq	-28(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fix_endian
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE36:
	.size	emb_write_u32, .-emb_write_u32
	.globl	emb_write_i32be
	.type	emb_write_i32be, @function
emb_write_i32be:
.LFB37:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	leaq	-28(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fix_endian
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE37:
	.size	emb_write_i32be, .-emb_write_i32be
	.globl	emb_write_u32be
	.type	emb_write_u32be, @function
emb_write_u32be:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	leaq	-28(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fix_endian
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE38:
	.size	emb_write_u32be, .-emb_write_u32be
	.globl	emb_array_create
	.type	emb_array_create, @function
emb_array_create:
.LFB39:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	$40, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	-20(%rbp), %edx
	movl	%edx, 32(%rax)
	movq	-8(%rbp), %rax
	movl	$128, 28(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 24(%rax)
	cmpl	$15, -20(%rbp)
	je	.L160
	cmpl	$19, -20(%rbp)
	je	.L161
	jmp	.L165
.L160:
	movl	$2048, %edi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	jmp	.L163
.L161:
	movl	$51584, %edi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	jmp	.L163
.L165:
	movl	$5120, %edi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
.L163:
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE39:
	.size	emb_array_create, .-emb_array_create
	.globl	emb_array_resize
	.type	emb_array_resize, @function
emb_array_resize:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %edx
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	subl	$3, %eax
	cmpl	%eax, %edx
	jge	.L167
	movl	$1, %eax
	jmp	.L168
.L167:
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	leal	128(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 28(%rax)
	movq	-8(%rbp), %rax
	movl	32(%rax), %eax
	cmpl	$15, %eax
	je	.L169
	cmpl	$19, %eax
	je	.L170
	jmp	.L176
.L169:
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	-8(%rbp), %rdx
	movq	%rax, 8(%rdx)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	jne	.L177
	movl	$0, %eax
	jmp	.L168
.L170:
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	cltq
	imulq	$403, %rax, %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	-8(%rbp), %rdx
	movq	%rax, 16(%rdx)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	jne	.L178
	movl	$0, %eax
	jmp	.L168
.L176:
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	-8(%rbp), %rdx
	movq	%rax, (%rdx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L179
	movl	$0, %eax
	jmp	.L168
.L177:
	nop
	jmp	.L173
.L178:
	nop
	jmp	.L173
.L179:
	nop
.L173:
	movl	$1, %eax
.L168:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE40:
	.size	emb_array_resize, .-emb_array_resize
	.globl	emb_array_copy
	.type	emb_array_copy, @function
emb_array_copy:
.LFB41:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %edi
	call	emb_array_create
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movl	28(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 28(%rax)
	movq	-16(%rbp), %rax
	movl	24(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	movq	-8(%rbp), %rax
	movl	32(%rax), %eax
	cmpl	$15, %eax
	je	.L181
	cmpl	$19, %eax
	je	.L182
	jmp	.L185
.L181:
	movq	-16(%rbp), %rax
	movl	24(%rax), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	jmp	.L184
.L182:
	movq	-16(%rbp), %rax
	movl	24(%rax), %eax
	cltq
	imulq	$403, %rax, %rdx
	movq	-16(%rbp), %rax
	movq	16(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	jmp	.L184
.L185:
	movq	-16(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	nop
.L184:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE41:
	.size	emb_array_copy, .-emb_array_copy
	.globl	emb_array_add_circle
	.type	emb_array_add_circle, @function
emb_array_add_circle:
.LFB42:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%xmm0, %rax
	movaps	%xmm1, %xmm0
	movq	%rax, -24(%rbp)
	movss	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L187
	movl	$0, %eax
	jmp	.L188
.L187:
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movl	-16(%rbp), %edx
	movl	%edx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movl	$2, 28(%rax)
	movl	$1, %eax
.L188:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE42:
	.size	emb_array_add_circle, .-emb_array_add_circle
	.globl	emb_array_add_ellipse
	.type	emb_array_add_ellipse, @function
emb_array_add_ellipse:
.LFB43:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L190
	movl	$0, %eax
	jmp	.L191
.L190:
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rax, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movl	32(%rbp), %eax
	movl	%eax, 16(%rcx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movl	$5, 28(%rax)
	movl	$1, %eax
.L191:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE43:
	.size	emb_array_add_ellipse, .-emb_array_add_ellipse
	.globl	emb_array_add_flag
	.type	emb_array_add_flag, @function
emb_array_add_flag:
.LFB44:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L193
	movl	$0, %eax
	jmp	.L194
.L193:
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-12(%rbp), %eax
	movl	%eax, 24(%rdx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movl	$6, 28(%rax)
	movl	$1, %eax
.L194:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE44:
	.size	emb_array_add_flag, .-emb_array_add_flag
	.globl	emb_array_addLine
	.type	emb_array_addLine, @function
emb_array_addLine:
.LFB45:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L196
	movl	$0, %eax
	jmp	.L197
.L196:
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rax, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movl	$7, 28(%rax)
	movl	$1, %eax
.L197:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE45:
	.size	emb_array_addLine, .-emb_array_addLine
	.globl	emb_array_addPath
	.type	emb_array_addPath, @function
emb_array_addPath:
.LFB46:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L199
	movl	$0, %eax
	jmp	.L200
.L199:
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rax, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movl	$9, 28(%rax)
	movl	$1, %eax
.L200:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE46:
	.size	emb_array_addPath, .-emb_array_addPath
	.globl	emb_array_addPoint
	.type	emb_array_addPoint, @function
emb_array_addPoint:
.LFB47:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%xmm0, %rdx
	movq	%rsi, %rax
	movq	%rdx, -24(%rbp)
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L202
	movl	$0, %eax
	jmp	.L203
.L202:
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rax, %rcx
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movl	$10, 28(%rax)
	movl	$1, %eax
.L203:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE47:
	.size	emb_array_addPoint, .-emb_array_addPoint
	.globl	emb_array_addPolyline
	.type	emb_array_addPolyline, @function
emb_array_addPolyline:
.LFB48:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L205
	movl	$0, %eax
	jmp	.L206
.L205:
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rax, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movl	$12, 28(%rax)
	movl	$1, %eax
.L206:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE48:
	.size	emb_array_addPolyline, .-emb_array_addPolyline
	.globl	emb_array_addPolygon
	.type	emb_array_addPolygon, @function
emb_array_addPolygon:
.LFB49:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L208
	movl	$0, %eax
	jmp	.L209
.L208:
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rax, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movl	$11, 28(%rax)
	movl	$1, %eax
.L209:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE49:
	.size	emb_array_addPolygon, .-emb_array_addPolygon
	.globl	emb_array_addRect
	.type	emb_array_addRect, @function
emb_array_addRect:
.LFB50:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L211
	movl	$0, %eax
	jmp	.L212
.L211:
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rax, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movl	$13, 28(%rax)
	movl	$1, %eax
.L212:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE50:
	.size	emb_array_addRect, .-emb_array_addRect
	.globl	emb_array_addStitch
	.type	emb_array_addStitch, @function
emb_array_addStitch:
.LFB51:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rdx, %rcx
	movq	%rsi, %rax
	movq	%rdi, %rdx
	movq	%rcx, %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L214
	movl	$0, %eax
	jmp	.L215
.L214:
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	cltq
	salq	$4, %rax
	subq	$16, %rax
	leaq	(%rdx,%rax), %rcx
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movl	$1, %eax
.L215:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE51:
	.size	emb_array_addStitch, .-emb_array_addStitch
	.globl	emb_array_add_geometry
	.type	emb_array_add_geometry, @function
emb_array_add_geometry:
.LFB52:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L217
	movl	$0, %eax
	jmp	.L218
.L217:
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movq	16(%rbp), %rcx
	movq	24(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	32(%rbp), %rcx
	movq	40(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	48(%rbp), %rdx
	movq	%rdx, 32(%rax)
	movl	$1, %eax
.L218:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE52:
	.size	emb_array_add_geometry, .-emb_array_add_geometry
	.globl	emb_array_addVector
	.type	emb_array_addVector, @function
emb_array_addVector:
.LFB53:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L220
	movl	$0, %eax
	jmp	.L221
.L220:
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	leaq	(%rcx,%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rax, (%rdx)
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movl	$18, 28(%rax)
	movl	$1, %eax
.L221:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE53:
	.size	emb_array_addVector, .-emb_array_addVector
	.globl	emb_array_free
	.type	emb_array_free, @function
emb_array_free:
.LFB54:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	cmpq	$0, -72(%rbp)
	je	.L237
	movq	-72(%rbp), %rax
	movl	32(%rax), %eax
	cmpl	$15, %eax
	je	.L225
	cmpl	$19, %eax
	je	.L226
	jmp	.L236
.L225:
	movq	-72(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	safe_free
	jmp	.L228
.L226:
	movq	-72(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, %rdi
	call	safe_free
	jmp	.L228
.L236:
	movl	$0, -20(%rbp)
	jmp	.L229
.L235:
	movq	-72(%rbp), %rax
	movq	(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -64(%rbp)
	movq	%rbx, -56(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -48(%rbp)
	movq	%rbx, -40(%rbp)
	movq	32(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movl	28(%rax), %eax
	cmpl	$12, %eax
	je	.L230
	cmpl	$12, %eax
	jg	.L238
	cmpl	$9, %eax
	je	.L232
	cmpl	$11, %eax
	je	.L233
	jmp	.L238
.L232:
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_free
	jmp	.L234
.L233:
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_free
	jmp	.L234
.L230:
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	emb_array_free
	jmp	.L234
.L238:
	nop
.L234:
	addl	$1, -20(%rbp)
.L229:
	movq	-72(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L235
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	safe_free
	nop
.L228:
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free
	jmp	.L222
.L237:
	nop
.L222:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE54:
	.size	emb_array_free, .-emb_array_free
	.section	.rodata
.LC14:
	.string	"%sX = %f\n"
.LC15:
	.string	"%sY = %f\n"
	.text
	.globl	emb_vector_print
	.type	emb_vector_print, @function
emb_vector_print:
.LFB55:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%xmm0, -8(%rbp)
	movq	%rdi, -16(%rbp)
	movss	-8(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rsi
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movss	-4(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movq	%xmm2, %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rsi
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE55:
	.size	emb_vector_print, .-emb_vector_print
	.section	.rodata
.LC16:
	.string	"start"
.LC17:
	.string	"middle"
.LC18:
	.string	"end"
	.text
	.globl	emb_arc_print
	.type	emb_arc_print, @function
emb_arc_print:
.LFB56:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	16(%rbp), %rdx
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	movq	%rdx, %xmm0
	call	emb_vector_print
	movq	24(%rbp), %rdx
	leaq	.LC17(%rip), %rax
	movq	%rax, %rdi
	movq	%rdx, %xmm0
	call	emb_vector_print
	movq	32(%rbp), %rdx
	leaq	.LC18(%rip), %rax
	movq	%rax, %rdi
	movq	%rdx, %xmm0
	call	emb_vector_print
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE56:
	.size	emb_arc_print, .-emb_arc_print
	.globl	check_header_present
	.type	check_header_present, @function
check_header_present:
.LFB57:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	-24(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -4(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jge	.L242
	movl	$0, %eax
	jmp	.L243
.L242:
	movl	-4(%rbp), %eax
.L243:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE57:
	.size	check_header_present, .-check_header_present
	.globl	sectorSize
	.type	sectorSize, @function
sectorSize:
.LFB58:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzwl	26(%rax), %eax
	cmpw	$3, %ax
	jne	.L245
	movl	$512, %eax
	jmp	.L246
.L245:
	movl	$4096, %eax
.L246:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE58:
	.size	sectorSize, .-sectorSize
	.globl	haveExtraDIFATSectors
	.type	haveExtraDIFATSectors, @function
haveExtraDIFATSectors:
.LFB59:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	80(%rax), %rax
	movq	%rax, %rdi
	call	entriesInDifatSector
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE59:
	.size	haveExtraDIFATSectors, .-haveExtraDIFATSectors
	.globl	seekToSector
	.type	seekToSector, @function
seekToSector:
.LFB60:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	sectorSize
	imull	-52(%rbp), %eax
	movl	%eax, %ebx
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	sectorSize
	addl	%ebx, %eax
	movl	%eax, -20(%rbp)
	movl	-20(%rbp), %ecx
	movq	-48(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE60:
	.size	seekToSector, .-seekToSector
	.globl	parseDIFATSectors
	.type	parseDIFATSectors, @function
parseDIFATSectors:
.LFB61:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	44(%rax), %eax
	movl	$109, %edx
	subl	%edx, %eax
	movl	%eax, -8(%rbp)
	movq	-32(%rbp), %rax
	movl	68(%rax), %eax
	movl	%eax, -4(%rbp)
	jmp	.L252
.L254:
	movl	-4(%rbp), %edx
	movq	-24(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	seekToSector
	movq	-32(%rbp), %rax
	movq	80(%rax), %rcx
	leaq	-8(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	readFullSector
	movl	%eax, -4(%rbp)
.L252:
	cmpl	$-2, -4(%rbp)
	je	.L255
	movl	-8(%rbp), %eax
	testl	%eax, %eax
	jne	.L254
.L255:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE61:
	.size	parseDIFATSectors, .-parseDIFATSectors
	.section	.rodata
.LC19:
	.string	"\320\317\021\340\241\261\032\341"
.LC20:
	.string	"bad header signature"
.LC21:
	.string	"Failed to parse header"
	.text
	.globl	bcfFile_read
	.type	bcfFile_read, @function
bcfFile_read:
.LFB62:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$120, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rbx
	leaq	-128(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	bcfFileHeader_read
	movq	-128(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rax, (%rbx)
	movq	%rdx, 8(%rbx)
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, 16(%rbx)
	movq	%rdx, 24(%rbx)
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rax, 32(%rbx)
	movq	%rdx, 40(%rbx)
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	-68(%rbp), %rax
	movq	-60(%rbp), %rdx
	movq	%rax, 60(%rbx)
	movq	%rdx, 68(%rbx)
	movq	-48(%rbp), %rax
	movl	$8, %edx
	leaq	.LC19(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcmp@PLT
	testl	%eax, %eax
	je	.L257
	leaq	.LC20(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC21(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L258
.L257:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	sectorSize
	movl	%eax, %edx
	movq	-48(%rbp), %rax
	movl	44(%rax), %ecx
	movq	-40(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	bcf_difat_create
	movq	-48(%rbp), %rdx
	movq	%rax, 80(%rdx)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	haveExtraDIFATSectors
	testl	%eax, %eax
	je	.L259
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parseDIFATSectors
.L259:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	sectorSize
	movl	%eax, %edi
	call	bcfFileFat_create
	movq	-48(%rbp), %rdx
	movq	%rax, 88(%rdx)
	movl	$0, -20(%rbp)
	jmp	.L260
.L261:
	movq	-48(%rbp), %rax
	movq	80(%rax), %rax
	movl	-20(%rbp), %edx
	movl	4(%rax,%rdx,4), %eax
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %edx
	movq	-40(%rbp), %rcx
	movq	-48(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	seekToSector
	movq	-48(%rbp), %rax
	movq	88(%rax), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	loadFatFromSector
	addl	$1, -20(%rbp)
.L260:
	movq	-48(%rbp), %rax
	movl	44(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jb	.L261
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	sectorSize
	movl	$128, %ebx
	movl	$0, %edx
	divl	%ebx
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	CompoundFileDirectory
	movq	-48(%rbp), %rdx
	movq	%rax, 96(%rdx)
	movq	-48(%rbp), %rax
	movl	48(%rax), %eax
	movl	%eax, -24(%rbp)
	jmp	.L262
.L263:
	movl	-24(%rbp), %edx
	movq	-40(%rbp), %rcx
	movq	-48(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	seekToSector
	movq	-48(%rbp), %rax
	movq	96(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	readNextSector
	movq	-48(%rbp), %rax
	movq	88(%rax), %rax
	movl	-24(%rbp), %edx
	movl	4(%rax,%rdx,4), %eax
	movl	%eax, -24(%rbp)
.L262:
	cmpl	$-2, -24(%rbp)
	jne	.L263
	movl	$1, %eax
.L258:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE62:
	.size	bcfFile_read, .-bcfFile_read
	.section	.rodata
	.align 8
.LC22:
	.string	"ERROR: GetFile failed to read byte."
	.text
	.globl	GetFile
	.type	GetFile, @function
GetFile:
.LFB63:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%rdx, -88(%rbp)
	call	tmpfile@PLT
	movq	%rax, -40(%rbp)
	movq	-72(%rbp), %rax
	movq	96(%rax), %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	jmp	.L265
.L268:
	movq	-32(%rbp), %rdx
	movq	-88(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L278
	movq	-32(%rbp), %rax
	movq	136(%rax), %rax
	movq	%rax, -32(%rbp)
.L265:
	cmpq	$0, -32(%rbp)
	jne	.L268
	jmp	.L267
.L278:
	nop
.L267:
	movq	-32(%rbp), %rax
	movq	120(%rax), %rax
	movl	%eax, -44(%rbp)
	movq	-72(%rbp), %rax
	movq	80(%rax), %rax
	movl	440(%rax), %eax
	movl	%eax, -48(%rbp)
	movl	$0, -12(%rbp)
	movq	-32(%rbp), %rax
	movl	116(%rax), %eax
	movl	%eax, -4(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-44(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2ssl	-48(%rbp), %xmm1
	divss	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	call	ceil@PLT
	cvttsd2sil	%xmm0, %eax
	movl	%eax, -52(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L269
.L277:
	movl	-4(%rbp), %edx
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	seekToSector
	movl	-44(%rbp), %eax
	subl	-12(%rbp), %eax
	movl	%eax, -8(%rbp)
	movl	-48(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	.L270
	movl	-48(%rbp), %eax
	movl	%eax, -8(%rbp)
.L270:
	movl	$0, -20(%rbp)
	jmp	.L271
.L276:
	movq	-80(%rbp), %rdx
	leaq	-53(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L272
	leaq	.LC22(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-40(%rbp), %rax
	jmp	.L275
.L272:
	movq	-40(%rbp), %rdx
	leaq	-53(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	cmpq	$1, %rax
	je	.L274
	leaq	.LC22(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-40(%rbp), %rax
	jmp	.L275
.L274:
	addl	$1, -20(%rbp)
.L271:
	movl	-20(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L276
	movl	-8(%rbp), %eax
	addl	%eax, -12(%rbp)
	movq	-72(%rbp), %rax
	movq	88(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	4(%rax,%rdx,4), %eax
	movl	%eax, -4(%rbp)
	addl	$1, -16(%rbp)
.L269:
	movl	-16(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L277
	movq	-40(%rbp), %rax
.L275:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE63:
	.size	GetFile, .-GetFile
	.globl	bcf_file_free
	.type	bcf_file_free, @function
bcf_file_free:
.LFB64:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	80(%rax), %rax
	movq	%rax, %rdi
	call	safe_free
	movq	-8(%rbp), %rax
	movq	88(%rax), %rax
	movq	%rax, %rdi
	call	safe_free
	movq	-8(%rbp), %rax
	addq	$96, %rax
	movq	%rax, %rdi
	call	bcf_directory_free
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE64:
	.size	bcf_file_free, .-bcf_file_free
	.section	.rodata
	.align 8
.LC23:
	.string	"ERROR: compound-file-difat.c bcf_difat_create(), cannot allocate memory for difat"
	.align 8
.LC24:
	.string	"ERROR: compound-file-difat.c bcf_difat_create(), Unexpected sector value %x at DIFAT[%d]\n"
	.text
	.globl	bcf_difat_create
	.type	bcf_difat_create, @function
bcf_difat_create:
.LFB65:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	%edx, -48(%rbp)
	movq	$0, -16(%rbp)
	movl	$444, %edi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L281
	leaq	.LC23(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L282
.L281:
	movq	-16(%rbp), %rax
	movl	-48(%rbp), %edx
	movl	%edx, 440(%rax)
	movl	$109, %eax
	cmpl	-44(%rbp), %eax
	jnb	.L283
	movl	$109, -44(%rbp)
.L283:
	movl	$0, -4(%rbp)
	jmp	.L284
.L285:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -20(%rbp)
	movq	-16(%rbp), %rax
	movl	-4(%rbp), %edx
	movl	-20(%rbp), %ecx
	movl	%ecx, 4(%rax,%rdx,4)
	addl	$1, -4(%rbp)
.L284:
	movl	-4(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jb	.L285
	movq	-16(%rbp), %rax
	movl	-44(%rbp), %edx
	movl	%edx, (%rax)
	movl	-44(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	.L286
.L288:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -20(%rbp)
	cmpl	$-1, -20(%rbp)
	je	.L287
	movl	-4(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC24(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L287:
	addl	$1, -4(%rbp)
.L286:
	movl	$109, %eax
	cmpl	%eax, -4(%rbp)
	jb	.L288
	movq	-16(%rbp), %rax
.L282:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE65:
	.size	bcf_difat_create, .-bcf_difat_create
	.globl	entriesInDifatSector
	.type	entriesInDifatSector, @function
entriesInDifatSector:
.LFB66:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	440(%rax), %eax
	movl	$4, %edx
	subl	%edx, %eax
	movl	$4, %ecx
	movl	$0, %edx
	divl	%ecx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE66:
	.size	entriesInDifatSector, .-entriesInDifatSector
	.section	.rodata
	.align 8
.LC25:
	.string	"ERROR: compound-file-difat.c readFullSector(), "
	.align 8
.LC26:
	.string	"Unexpected sector value %x at DIFAT[%d]]\n"
	.text
	.globl	readFullSector
	.type	readFullSector, @function
readFullSector:
.LFB67:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movl	$0, -24(%rbp)
	movq	-56(%rbp), %rax
	movl	(%rax), %ebx
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	entriesInDifatSector
	cmpl	%ebx, %eax
	jnb	.L292
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	entriesInDifatSector
	movl	%eax, -24(%rbp)
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	subl	-24(%rbp), %eax
	movl	%eax, %edx
	movq	-56(%rbp), %rax
	movl	%edx, (%rax)
	jmp	.L293
.L292:
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -24(%rbp)
	movq	-56(%rbp), %rax
	movl	$0, (%rax)
.L293:
	movl	$0, -20(%rbp)
	jmp	.L294
.L295:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -32(%rbp)
	movq	-48(%rbp), %rax
	movl	(%rax), %edx
	movq	-48(%rbp), %rax
	movl	%edx, %ecx
	movl	-32(%rbp), %edx
	movl	%edx, 4(%rax,%rcx,4)
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-48(%rbp), %rax
	movl	%edx, (%rax)
	addl	$1, -20(%rbp)
.L294:
	movl	-20(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jb	.L295
	movl	-24(%rbp), %eax
	movl	%eax, -20(%rbp)
	jmp	.L296
.L298:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -32(%rbp)
	cmpl	$-1, -32(%rbp)
	je	.L297
	leaq	.LC25(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-20(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC26(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L297:
	addl	$1, -20(%rbp)
.L296:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	entriesInDifatSector
	cmpl	%eax, -20(%rbp)
	jb	.L298
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE67:
	.size	readFullSector, .-readFullSector
	.globl	parseDirectoryEntryName
	.type	parseDirectoryEntryName, @function
parseDirectoryEntryName:
.LFB68:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L301
.L303:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i16
	movw	%ax, -6(%rbp)
	cmpw	$0, -6(%rbp)
	je	.L302
	movzwl	-6(%rbp), %eax
	movl	%eax, %ecx
	movq	-32(%rbp), %rdx
	movl	-4(%rbp), %eax
	cltq
	movb	%cl, (%rdx,%rax)
.L302:
	addl	$1, -4(%rbp)
.L301:
	cmpl	$31, -4(%rbp)
	jle	.L303
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE68:
	.size	parseDirectoryEntryName, .-parseDirectoryEntryName
	.section	.rodata
	.align 8
.LC27:
	.string	"ERROR: compound-file-directory.c CompoundFileDirectory(), cannot allocate memory for dir"
	.text
	.globl	CompoundFileDirectory
	.type	CompoundFileDirectory, @function
CompoundFileDirectory:
.LFB69:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	$16, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L305
	leaq	.LC27(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L306
.L305:
	movq	-8(%rbp), %rax
	movl	-20(%rbp), %edx
	movl	%edx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	movq	-8(%rbp), %rax
.L306:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE69:
	.size	CompoundFileDirectory, .-CompoundFileDirectory
	.section	.rodata
.LC28:
	.string	"%u %u\n"
	.text
	.globl	parseTime
	.type	parseTime, @function
parseTime:
.LFB70:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -4(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC28(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, -24(%rbp)
	movl	$2, -20(%rbp)
	movl	$3, -16(%rbp)
	movl	$4, -28(%rbp)
	movl	$5, -12(%rbp)
	movl	$6, -32(%rbp)
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-16(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	-40(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE70:
	.size	parseTime, .-parseTime
	.section	.rodata
	.align 8
.LC29:
	.string	"ERROR: compound-file-directory.c CompoundFileDirectoryEntry(), cannot allocate memory for dir"
	.align 8
.LC30:
	.string	"ERROR: compound-file-directory.c CompoundFileDirectoryEntry()"
.LC31:
	.string	", unexpected object type: %d\n"
	.align 8
.LC32:
	.string	"ERROR: Failed to read guidSize bytes for CLSID"
	.text
	.globl	CompoundFileDirectoryEntry
	.type	CompoundFileDirectoryEntry, @function
CompoundFileDirectoryEntry:
.LFB71:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$16, -8(%rbp)
	movl	$144, %edi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L310
	leaq	.LC29(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L311
.L310:
	movq	-16(%rbp), %rax
	movl	$32, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parseDirectoryEntryName
	movq	-16(%rbp), %rax
	movq	$0, 136(%rax)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16
	movq	-16(%rbp), %rdx
	movw	%ax, 32(%rdx)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, %edx
	movq	-16(%rbp), %rax
	movb	%dl, 34(%rax)
	movq	-16(%rbp), %rax
	movzbl	34(%rax), %eax
	cmpb	$1, %al
	je	.L312
	movq	-16(%rbp), %rax
	movzbl	34(%rax), %eax
	cmpb	$2, %al
	je	.L312
	movq	-16(%rbp), %rax
	movzbl	34(%rax), %eax
	cmpb	$5, %al
	je	.L312
	leaq	.LC30(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movzbl	34(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC31(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L311
.L312:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, %edx
	movq	-16(%rbp), %rax
	movb	%dl, 35(%rax)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, %edx
	movq	-16(%rbp), %rax
	movl	%edx, 36(%rax)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, %edx
	movq	-16(%rbp), %rax
	movl	%edx, 40(%rax)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, %edx
	movq	-16(%rbp), %rax
	movl	%edx, 44(%rax)
	movl	-8(%rbp), %eax
	cltq
	movq	-16(%rbp), %rdx
	leaq	48(%rdx), %rdi
	movq	-24(%rbp), %rdx
	movq	%rdx, %rcx
	movq	%rax, %rdx
	movl	$1, %esi
	call	fread@PLT
	movq	%rax, %rdx
	movl	-8(%rbp), %eax
	cltq
	cmpq	%rax, %rdx
	jnb	.L313
	leaq	.LC32(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	jmp	.L311
.L313:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, %edx
	movq	-16(%rbp), %rax
	movl	%edx, 64(%rax)
	movl	$0, -4(%rbp)
	jmp	.L314
.L315:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, %ecx
	movq	-16(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	addq	$16, %rdx
	movl	%ecx, 4(%rax,%rdx,4)
	addl	$1, -4(%rbp)
.L314:
	cmpl	$5, -4(%rbp)
	jle	.L315
	movl	$0, -4(%rbp)
	jmp	.L316
.L317:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, %ecx
	movq	-16(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	addq	$20, %rdx
	movl	%ecx, 12(%rax,%rdx,4)
	addl	$1, -4(%rbp)
.L316:
	cmpl	$5, -4(%rbp)
	jle	.L317
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, %edx
	movq	-16(%rbp), %rax
	movl	%edx, 116(%rax)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 120(%rax)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, %edx
	movq	-16(%rbp), %rax
	movl	%edx, 128(%rax)
	movq	-16(%rbp), %rax
.L311:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE71:
	.size	CompoundFileDirectoryEntry, .-CompoundFileDirectoryEntry
	.globl	readNextSector
	.type	readNextSector, @function
readNextSector:
.LFB72:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L319
.L325:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	CompoundFileDirectoryEntry
	movq	%rax, -24(%rbp)
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L322
	movq	-48(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	jmp	.L321
.L324:
	movq	-16(%rbp), %rax
	movq	136(%rax), %rax
	testq	%rax, %rax
	jne	.L323
	movq	-16(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 136(%rax)
	jmp	.L321
.L323:
	movq	-16(%rbp), %rax
	movq	136(%rax), %rax
	movq	%rax, -16(%rbp)
.L322:
	cmpq	$0, -16(%rbp)
	jne	.L324
.L321:
	addl	$1, -4(%rbp)
.L319:
	movq	-48(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jb	.L325
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE72:
	.size	readNextSector, .-readNextSector
	.globl	bcf_directory_free
	.type	bcf_directory_free, @function
bcf_directory_free:
.LFB73:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L331
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L329
.L330:
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	136(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free
.L329:
	cmpq	$0, -8(%rbp)
	jne	.L330
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	safe_free
	jmp	.L326
.L331:
	nop
.L326:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE73:
	.size	bcf_directory_free, .-bcf_directory_free
	.section	.rodata
	.align 8
.LC33:
	.string	"ERROR: compound-file-fat.c bcfFileFat_create(), "
	.align 8
.LC34:
	.string	"cannot allocate memory for fat"
	.text
	.globl	bcfFileFat_create
	.type	bcfFileFat_create, @function
bcfFileFat_create:
.LFB74:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	$1028, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L333
	leaq	.LC33(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC34(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L334
.L333:
	movl	$4, %ecx
	movl	-20(%rbp), %eax
	movl	$0, %edx
	divl	%ecx
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, 1024(%rax)
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
	movq	-8(%rbp), %rax
.L334:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE74:
	.size	bcfFileFat_create, .-bcfFileFat_create
	.globl	loadFatFromSector
	.type	loadFatFromSector, @function
loadFatFromSector:
.LFB75:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -8(%rbp)
	movq	-24(%rbp), %rax
	movl	1024(%rax), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	.L336
.L337:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, %ecx
	movq	-24(%rbp), %rax
	movl	-4(%rbp), %edx
	movl	%ecx, 4(%rax,%rdx,4)
	addl	$1, -4(%rbp)
.L336:
	movl	-4(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jb	.L337
	movl	-12(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE75:
	.size	loadFatFromSector, .-loadFatFromSector
	.section	.rodata
	.align 8
.LC35:
	.string	"ERROR: failed to read signature bytes from bcf file."
	.align 8
.LC36:
	.string	"ERROR: failed to read CLSID bytes from bcf file."
	.text
	.globl	bcfFileHeader_read
	.type	bcfFileHeader_read, @function
bcfFileHeader_read:
.LFB76:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$104, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	-112(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$7, %rax
	ja	.L339
	leaq	.LC35(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-104(%rbp), %rax
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-36(%rbp), %rcx
	movq	-28(%rbp), %rbx
	movq	%rcx, 60(%rax)
	movq	%rbx, 68(%rax)
	jmp	.L342
.L339:
	movq	-112(%rbp), %rax
	leaq	-96(%rbp), %rdx
	leaq	8(%rdx), %rdi
	movq	%rax, %rcx
	movl	$16, %edx
	movl	$1, %esi
	call	fread@PLT
	cmpq	$15, %rax
	ja	.L341
	leaq	.LC36(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-104(%rbp), %rax
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-36(%rbp), %rcx
	movq	-28(%rbp), %rbx
	movq	%rcx, 60(%rax)
	movq	%rbx, 68(%rax)
	jmp	.L342
.L341:
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16
	movw	%ax, -72(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16
	movw	%ax, -70(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16
	movw	%ax, -68(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16
	movw	%ax, -66(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16
	movw	%ax, -64(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_u16
	movw	%ax, -62(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -60(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -56(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -52(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -48(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -44(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -40(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -36(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -32(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -28(%rbp)
	movq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	emb_read_i32
	movl	%eax, -24(%rbp)
	movq	-104(%rbp), %rax
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, 32(%rax)
	movq	%rbx, 40(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 48(%rax)
	movq	%rbx, 56(%rax)
	movq	-36(%rbp), %rcx
	movq	-28(%rbp), %rbx
	movq	%rcx, 60(%rax)
	movq	%rbx, 68(%rax)
.L342:
	movq	-104(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE76:
	.size	bcfFileHeader_read, .-bcfFileHeader_read
	.section	.rodata
	.align 8
.LC38:
	.string	"ERROR: emb_generate_satin_outline(), cannot allocate memory for outline->side1"
	.align 8
.LC39:
	.string	"ERROR: emb_generate_satin_outline(), cannot allocate memory for outline->side2"
	.align 8
.LC40:
	.string	"ERROR: emb_generate_satin_outline(), result argument is null"
	.align 8
.LC41:
	.string	"ERROR: emb_generate_satin_outline(), cannot allocate memory for result->side1"
	.align 8
.LC42:
	.string	"ERROR: emb_generate_satin_outline(), cannot allocate memory for result->side2"
.LC43:
	.string	"No intersection point."
	.text
	.globl	emb_generate_satin_outline
	.type	emb_generate_satin_outline, @function
emb_generate_satin_outline:
.LFB77:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movq	%rdi, -184(%rbp)
	movss	%xmm0, -188(%rbp)
	movq	%rsi, -200(%rbp)
	movss	-188(%rbp), %xmm0
	movss	.LC37(%rip), %xmm1
	divss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movq	-184(%rbp), %rax
	movl	24(%rax), %eax
	subl	$1, %eax
	addl	%eax, %eax
	movl	%eax, -12(%rbp)
	movl	$18, %edi
	call	emb_array_create
	movq	%rax, -104(%rbp)
	movq	-104(%rbp), %rax
	testq	%rax, %rax
	jne	.L344
	leaq	.LC38(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L356
.L344:
	movl	$18, %edi
	call	emb_array_create
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	testq	%rax, %rax
	jne	.L346
	leaq	.LC39(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L356
.L346:
	movl	$1, -4(%rbp)
	jmp	.L347
.L348:
	movq	-184(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -160(%rbp)
	movq	-184(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -152(%rbp)
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-160(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-144(%rbp), %rax
	movq	%rax, 16(%rcx)
	movl	$1, %edi
	call	emb_line_normalVector@PLT
	addq	$32, %rsp
	movq	%xmm0, %rax
	movq	%rax, -128(%rbp)
	movss	-8(%rbp), %xmm0
	movq	-128(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale@PLT
	movq	%xmm0, %rax
	movq	%rax, -136(%rbp)
	movq	-184(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movq	(%rax), %rdx
	movq	-136(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -136(%rbp)
	movq	-104(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movq	-184(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rdx
	movq	-136(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -136(%rbp)
	movq	-104(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movss	-8(%rbp), %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-128(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale@PLT
	movq	%xmm0, %rax
	movq	%rax, -136(%rbp)
	movq	-184(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movq	(%rax), %rdx
	movq	-136(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -136(%rbp)
	movq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movq	-184(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rdx
	movq	-136(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -136(%rbp)
	movq	-96(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	addl	$1, -4(%rbp)
.L347:
	movq	-184(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L348
	cmpq	$0, -200(%rbp)
	jne	.L349
	leaq	.LC40(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L356
.L349:
	movl	$18, %edi
	call	emb_array_create
	movq	-200(%rbp), %rdx
	movq	%rax, 8(%rdx)
	movq	-200(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	jne	.L350
	leaq	.LC41(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L356
.L350:
	movl	$18, %edi
	call	emb_array_create
	movq	-200(%rbp), %rdx
	movq	%rax, 16(%rdx)
	movq	-200(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	jne	.L351
	leaq	.LC42(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L356
.L351:
	movq	-104(%rbp), %rax
	movq	(%rax), %rdx
	movq	-200(%rbp), %rax
	movq	8(%rax), %rax
	movq	(%rdx), %rdx
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movq	-96(%rbp), %rax
	movq	(%rax), %rdx
	movq	-200(%rbp), %rax
	movq	16(%rax), %rax
	movq	(%rdx), %rdx
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movl	$3, -4(%rbp)
	jmp	.L352
.L355:
	movl	$0, -164(%rbp)
	movq	-104(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$120, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-104(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$80, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	-104(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	movq	-104(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -72(%rbp)
	leaq	-164(%rbp), %rsi
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rcx)
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	%rsi, %rdi
	call	emb_line_intersectionPoint@PLT
	addq	$48, %rsp
	movq	%xmm0, %rax
	movq	%rax, -120(%rbp)
	movl	-164(%rbp), %eax
	testl	%eax, %eax
	je	.L353
	leaq	.LC43(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L353:
	movq	-200(%rbp), %rax
	movq	8(%rax), %rax
	movq	-120(%rbp), %rdx
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movq	-96(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$120, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	-96(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$80, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -40(%rbp)
	movq	-96(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$40, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	movq	-96(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -72(%rbp)
	leaq	-164(%rbp), %rsi
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rcx)
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	%rsi, %rdi
	call	emb_line_intersectionPoint@PLT
	addq	$48, %rsp
	movq	%xmm0, %rax
	movq	%rax, -120(%rbp)
	movl	-164(%rbp), %eax
	testl	%eax, %eax
	je	.L354
	leaq	.LC43(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L354:
	movq	-200(%rbp), %rax
	movq	16(%rax), %rax
	movq	-120(%rbp), %rdx
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	addl	$2, -4(%rbp)
.L352:
	movl	-4(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jl	.L355
	movq	-104(%rbp), %rax
	movq	(%rax), %rcx
	movq	-184(%rbp), %rax
	movl	24(%rax), %eax
	addl	%eax, %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$120, %rax
	leaq	(%rcx,%rax), %rdx
	movq	-200(%rbp), %rax
	movq	8(%rax), %rax
	movq	(%rdx), %rdx
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movq	-96(%rbp), %rax
	movq	(%rax), %rcx
	movq	-184(%rbp), %rax
	movl	24(%rax), %eax
	addl	%eax, %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	subq	$120, %rax
	leaq	(%rcx,%rax), %rdx
	movq	-200(%rbp), %rax
	movq	16(%rax), %rax
	movq	(%rdx), %rdx
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movq	-184(%rbp), %rax
	movl	24(%rax), %edx
	movq	-200(%rbp), %rax
	movl	%edx, (%rax)
	movl	$1, %eax
.L356:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE77:
	.size	emb_generate_satin_outline, .-emb_generate_satin_outline
	.section	.rodata
	.align 8
.LC44:
	.string	"ERROR: emb_satin_outline_render(), result argument is null"
	.text
	.globl	emb_satin_outline_render
	.type	emb_satin_outline_render, @function
emb_satin_outline_render:
.LFB78:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movq	%rdi, -136(%rbp)
	movss	%xmm0, -140(%rbp)
	movq	$0, -16(%rbp)
	cmpq	$0, -136(%rbp)
	jne	.L358
	leaq	.LC44(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L366
.L358:
	movq	-136(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jle	.L360
	movl	$0, -8(%rbp)
	jmp	.L361
.L365:
	movq	-136(%rbp), %rax
	movq	8(%rax), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -24(%rbp)
	movq	-136(%rbp), %rax
	movq	8(%rax), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	cltq
	leaq	1(%rax), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -32(%rbp)
	movq	-136(%rbp), %rax
	movq	16(%rax), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -40(%rbp)
	movq	-136(%rbp), %rax
	movq	16(%rax), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	cltq
	leaq	1(%rax), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -48(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract@PLT
	movq	%xmm0, %rax
	movq	%rax, -80(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract@PLT
	movq	%xmm0, %rax
	movq	%rax, -88(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_average@PLT
	movq	%xmm0, %rax
	movq	%rax, -104(%rbp)
	movq	-48(%rbp), %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_average@PLT
	movq	%xmm0, %rax
	movq	%rax, -112(%rbp)
	movq	-112(%rbp), %rdx
	movq	-104(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract@PLT
	movq	%xmm0, %rax
	movq	%rax, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_length@PLT
	movd	%xmm0, %eax
	movl	%eax, -52(%rbp)
	movss	-52(%rbp), %xmm0
	mulss	-140(%rbp), %xmm0
	movss	.LC45(%rip), %xmm1
	divss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %eax
	movl	%eax, -56(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-56(%rbp), %xmm1
	movsd	.LC46(%rip), %xmm0
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-80(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale@PLT
	movq	%xmm0, %rax
	movq	%rax, -120(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-56(%rbp), %xmm1
	movsd	.LC46(%rip), %xmm0
	divsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-88(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale@PLT
	movq	%xmm0, %rax
	movq	%rax, -128(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -72(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L362
.L364:
	cmpq	$0, -16(%rbp)
	jne	.L363
	movl	$18, %edi
	call	emb_array_create
	movq	%rax, -16(%rbp)
.L363:
	movq	-64(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movq	-72(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movq	-120(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -64(%rbp)
	movq	-128(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -72(%rbp)
	addl	$1, -4(%rbp)
.L362:
	movl	-4(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jl	.L364
	addl	$1, -8(%rbp)
.L361:
	movq	-136(%rbp), %rax
	movl	(%rax), %eax
	subl	$1, %eax
	cmpl	%eax, -8(%rbp)
	jl	.L365
	movq	-64(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	movq	-72(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
.L360:
	movq	-16(%rbp), %rax
.L366:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE78:
	.size	emb_satin_outline_render, .-emb_satin_outline_render
	.globl	write_24bit
	.type	write_24bit, @function
write_24bit:
.LFB79:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movb	$0, -4(%rbp)
	movl	-28(%rbp), %eax
	movb	%al, -3(%rbp)
	movl	-28(%rbp), %eax
	sarl	$8, %eax
	movb	%al, -2(%rbp)
	movl	-28(%rbp), %eax
	sarl	$16, %eax
	movb	%al, -1(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-4(%rbp), %rax
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE79:
	.size	write_24bit, .-write_24bit
	.globl	embColor_distance
	.type	embColor_distance, @function
embColor_distance:
.LFB80:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movzbl	-24(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-32(%rbp), %eax
	movzbl	%al, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movzbl	-24(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-32(%rbp), %eax
	movzbl	%al, %eax
	subl	%eax, %edx
	movl	%ecx, %eax
	imull	%edx, %eax
	movl	%eax, -4(%rbp)
	movzbl	-23(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-31(%rbp), %eax
	movzbl	%al, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movzbl	-23(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-31(%rbp), %eax
	movzbl	%al, %eax
	subl	%eax, %edx
	movl	%ecx, %eax
	imull	%edx, %eax
	addl	%eax, -4(%rbp)
	movzbl	-22(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-30(%rbp), %eax
	movzbl	%al, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movzbl	-22(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-30(%rbp), %eax
	movzbl	%al, %eax
	subl	%eax, %edx
	movl	%ecx, %eax
	imull	%edx, %eax
	addl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE80:
	.size	embColor_distance, .-embColor_distance
	.section	.rodata
	.align 8
.LC47:
	.string	"ERROR: Failed to read embColor bytes."
	.text
	.globl	embColor_read
	.type	embColor_read, @function
embColor_read:
.LFB81:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rcx
	leaq	-4(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movl	-36(%rbp), %edx
	movl	%edx, %edx
	cmpq	%rdx, %rax
	jnb	.L371
	leaq	.LC47(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L370
.L371:
	movzbl	-4(%rbp), %edx
	movq	-32(%rbp), %rax
	movb	%dl, (%rax)
	movzbl	-3(%rbp), %edx
	movq	-32(%rbp), %rax
	movb	%dl, 1(%rax)
	movzbl	-2(%rbp), %edx
	movq	-32(%rbp), %rax
	movb	%dl, 2(%rax)
.L370:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE81:
	.size	embColor_read, .-embColor_read
	.globl	embColor_write
	.type	embColor_write, @function
embColor_write:
.LFB82:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movzbl	-32(%rbp), %eax
	movb	%al, -4(%rbp)
	movzbl	-31(%rbp), %eax
	movb	%al, -3(%rbp)
	movzbl	-30(%rbp), %eax
	movb	%al, -2(%rbp)
	movb	$0, -1(%rbp)
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rcx
	leaq	-4(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE82:
	.size	embColor_write, .-embColor_write
	.globl	emb_find_nearest_color
	.type	emb_find_nearest_color, @function
emb_find_nearest_color:
.LFB83:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$40, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	$196608, -4(%rbp)
	movl	$-1, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L375
.L377:
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movzbl	1(%rax), %ecx
	salq	$8, %rcx
	orq	%rcx, %rdx
	movzbl	2(%rax), %eax
	salq	$16, %rax
	orq	%rdx, %rax
	movq	%rax, %rsi
	movzbl	-24(%rbp), %eax
	movzbl	-23(%rbp), %edx
	salq	$8, %rdx
	orq	%rax, %rdx
	movzbl	-22(%rbp), %eax
	salq	$16, %rax
	orq	%rdx, %rax
	movq	%rax, %rdi
	call	embColor_distance
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jg	.L376
	movl	-16(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -8(%rbp)
.L376:
	addl	$1, -12(%rbp)
.L375:
	movl	-12(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L377
	movl	-8(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE83:
	.size	emb_find_nearest_color, .-emb_find_nearest_color
	.globl	emb_find_nearest_thread
	.type	emb_find_nearest_thread, @function
emb_find_nearest_thread:
.LFB84:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$40, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	$196608, -4(%rbp)
	movl	$-1, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L380
.L382:
	movl	-12(%rbp), %eax
	cltq
	imulq	$403, %rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movzbl	1(%rax), %ecx
	salq	$8, %rcx
	orq	%rcx, %rdx
	movzbl	2(%rax), %eax
	salq	$16, %rax
	orq	%rdx, %rax
	movq	%rax, %rsi
	movzbl	-24(%rbp), %eax
	movzbl	-23(%rbp), %edx
	salq	$8, %rdx
	orq	%rax, %rdx
	movzbl	-22(%rbp), %eax
	salq	$16, %rax
	orq	%rdx, %rax
	movq	%rax, %rdi
	call	embColor_distance
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jg	.L381
	movl	-16(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -8(%rbp)
.L381:
	addl	$1, -12(%rbp)
.L380:
	movl	-12(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L382
	movl	-8(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE84:
	.size	emb_find_nearest_thread, .-emb_find_nearest_thread
	.globl	emb_get_random_thread
	.type	emb_get_random_thread, @function
emb_get_random_thread:
.LFB85:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$432, %rsp
	movq	%rdi, -424(%rbp)
	call	rand@PLT
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$24, %eax
	addl	%eax, %edx
	movzbl	%dl, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movb	%al, -416(%rbp)
	call	rand@PLT
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$24, %eax
	addl	%eax, %edx
	movzbl	%dl, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movb	%al, -415(%rbp)
	call	rand@PLT
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$24, %eax
	addl	%eax, %edx
	movzbl	%dl, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movb	%al, -414(%rbp)
	leaq	-416(%rbp), %rax
	addq	$3, %rax
	movl	$1684955506, (%rax)
	movl	$7171940, 3(%rax)
	movb	$0, -213(%rbp)
	movq	-424(%rbp), %rax
	movq	%rax, %rdx
	leaq	-416(%rbp), %rax
	movl	$403, %ecx
	movq	(%rax), %rsi
	movq	%rsi, (%rdx)
	movl	%ecx, %esi
	addq	%rdx, %rsi
	leaq	8(%rsi), %rdi
	movl	%ecx, %esi
	addq	%rax, %rsi
	addq	$8, %rsi
	movq	-16(%rsi), %rsi
	movq	%rsi, -16(%rdi)
	leaq	8(%rdx), %rdi
	andq	$-8, %rdi
	subq	%rdi, %rdx
	subq	%rdx, %rax
	addl	%edx, %ecx
	andl	$-8, %ecx
	shrl	$3, %ecx
	movl	%ecx, %edx
	movl	%edx, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	movq	-424(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE85:
	.size	emb_get_random_thread, .-emb_get_random_thread
	.globl	binaryReadString
	.type	binaryReadString, @function
binaryReadString:
.LFB86:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L387
.L390:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, %ecx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L391
	addl	$1, -4(%rbp)
.L387:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L390
	jmp	.L392
.L391:
	nop
.L392:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE86:
	.size	binaryReadString, .-binaryReadString
	.globl	binaryReadUnicodeString
	.type	binaryReadUnicodeString, @function
binaryReadUnicodeString:
.LFB87:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L394
.L396:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -5(%rbp)
	cmpb	$0, -5(%rbp)
	je	.L395
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-5(%rbp), %eax
	movb	%al, (%rdx)
.L395:
	addl	$1, -4(%rbp)
.L394:
	movl	-36(%rbp), %eax
	addl	%eax, %eax
	cmpl	%eax, -4(%rbp)
	jl	.L396
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE87:
	.size	binaryReadUnicodeString, .-binaryReadUnicodeString
	.globl	stringInArray
	.type	stringInArray, @function
stringInArray:
.LFB88:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L398
.L401:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rcx
	movq	-24(%rbp), %rax
	movl	$200, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncmp@PLT
	testl	%eax, %eax
	jne	.L399
	movl	$1, %eax
	jmp	.L400
.L399:
	addl	$1, -4(%rbp)
.L398:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	string_len
	testl	%eax, %eax
	jne	.L401
	movl	$0, %eax
.L400:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE88:
	.size	stringInArray, .-stringInArray
	.globl	emb_readline
	.type	emb_readline, @function
emb_readline:
.LFB89:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L403
.L410:
	movq	-24(%rbp), %rdx
	leaq	-5(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	testq	%rax, %rax
	je	.L412
	movzbl	-5(%rbp), %eax
	cmpb	$13, %al
	jne	.L406
	movq	-24(%rbp), %rdx
	leaq	-5(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	jne	.L413
	movzbl	-5(%rbp), %eax
	cmpb	$10, %al
	je	.L414
	movq	-24(%rbp), %rax
	movl	$1, %edx
	movq	$-1, %rsi
	movq	%rax, %rdi
	call	fseek@PLT
	jmp	.L414
.L406:
	movzbl	-5(%rbp), %eax
	cmpb	$10, %al
	je	.L415
	movzbl	-5(%rbp), %edx
	movq	-32(%rbp), %rax
	movb	%dl, (%rax)
	addq	$1, -32(%rbp)
	addl	$1, -4(%rbp)
.L403:
	movl	-36(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -4(%rbp)
	jl	.L410
	jmp	.L405
.L412:
	nop
	jmp	.L405
.L413:
	nop
	jmp	.L405
.L414:
	nop
	jmp	.L405
.L415:
	nop
.L405:
	movq	-32(%rbp), %rax
	movb	$0, (%rax)
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE89:
	.size	emb_readline, .-emb_readline
	.globl	get_trim_bounds
	.type	get_trim_bounds, @function
get_trim_bounds:
.LFB90:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -32(%rbp)
	movq	%rsi, -40(%rbp)
	movq	%rdx, -48(%rbp)
	movq	$0, -16(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	string_whitespace
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-40(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
.L417:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	string_whitespace
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	addq	%rax, %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-48(%rbp), %rax
	movq	(%rax), %rbx
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	string_whitespace
	cltq
	addq	%rbx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L417
	nop
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE90:
	.size	get_trim_bounds, .-get_trim_bounds
	.globl	copy_trim
	.type	copy_trim, @function
copy_trim:
.LFB91:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -8(%rbp)
	leaq	-32(%rbp), %rdx
	leaq	-24(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	get_trim_bounds
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, -16(%rbp)
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE91:
	.size	copy_trim, .-copy_trim
	.section	.rodata
.LC48:
	.string	"%.10f"
	.text
	.globl	emb_optOut
	.type	emb_optOut, @function
emb_optOut:
.LFB92:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movss	%xmm0, -20(%rbp)
	movq	%rdi, -32(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-20(%rbp), %xmm1
	movq	%xmm1, %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC48(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$1, %eax
	call	sprintf@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	string_len
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	nop
.L421:
	subq	$1, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$48, %al
	je	.L421
	movq	-8(%rbp), %rax
	addq	$1, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$46, %al
	jne	.L422
	movq	-8(%rbp), %rax
	movb	$0, (%rax)
.L422:
	movq	-32(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE92:
	.size	emb_optOut, .-emb_optOut
	.section	.rodata
.LC49:
	.string	"%d"
	.text
	.globl	embTime_initNow
	.type	embTime_initNow, @function
embTime_initNow:
.LFB93:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC49(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE93:
	.size	embTime_initNow, .-embTime_initNow
	.globl	embTime_time
	.type	embTime_time, @function
embTime_time:
.LFB94:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	movl	$1, -4(%rbp)
	movq	-24(%rbp), %rcx
	movq	-32(%rbp), %rsi
	movq	(%rsi), %rax
	movq	8(%rsi), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	16(%rsi), %rax
	movq	%rax, 16(%rcx)
	movq	-24(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE94:
	.size	embTime_time, .-embTime_time
	.section	.rodata
.LC50:
	.string	"List of Formats"
.LC51:
	.string	"---------------"
.LC52:
	.string	""
.LC53:
	.string	"    KEY"
	.align 8
.LC54:
	.string	"    'S' = Yes, and is considered stable."
	.align 8
.LC55:
	.string	"    'U' = Yes, but may be unstable."
.LC56:
	.string	"    ' ' = No."
	.align 8
.LC57:
	.string	"  Format   Read    Write   Description"
	.align 8
.LC58:
	.string	"|________|_______|_______|____________________________________________________|"
	.align 8
.LC59:
	.string	"|        |       |       |                                                    |"
	.align 8
.LC60:
	.string	"|  %-4s  |   %c   |   %c   |  %-49s |\n"
	.align 8
.LC61:
	.string	"| Total: |  %3d  |  %3d  |                                                    |\n"
	.text
	.globl	formats
	.type	formats, @function
formats:
.LFB95:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	leaq	.LC50(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC51(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC52(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC53(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC54(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC55(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC56(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC52(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC57(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC58(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC59(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, -12(%rbp)
	jmp	.L428
.L431:
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	400+formatTable(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	cmpb	$32, %al
	je	.L429
	addl	$1, -4(%rbp)
.L429:
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	401+formatTable(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	cmpb	$32, %al
	je	.L430
	addl	$1, -8(%rbp)
.L430:
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	192(%rax), %rdx
	leaq	formatTable(%rip), %rax
	addq	%rdx, %rax
	leaq	8(%rax), %rdi
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	401+formatTable(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movsbl	%al, %edx
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	400+formatTable(%rip), %rcx
	movzbl	(%rax,%rcx), %eax
	movsbl	%al, %eax
	movl	-12(%rbp), %ecx
	movslq	%ecx, %rcx
	imulq	$420, %rcx, %rcx
	leaq	formatTable(%rip), %rsi
	addq	%rcx, %rsi
	movq	%rdi, %r8
	movl	%edx, %ecx
	movl	%eax, %edx
	leaq	.LC60(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -12(%rbp)
.L428:
	cmpl	$60, -12(%rbp)
	jle	.L431
	leaq	.LC58(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC59(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC61(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC58(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC52(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE95:
	.size	formats, .-formats
	.section	.rodata
.LC62:
	.string	"example.%s"
.LC63:
	.string	"Error: format unrecognised."
.LC64:
	.string	"Converting %s to %s.\n"
.LC65:
	.string	"Usage of the to flag is:"
	.align 8
.LC66:
	.string	"    embroider -t FORMAT FILE(S)"
	.align 8
.LC67:
	.string	"but it appears you entered less than 3 arguments to embroider."
	.text
	.globl	to_flag
	.type	to_flag, @function
to_flag:
.LFB96:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$240, %rsp
	movq	%rdi, -232(%rbp)
	movl	%esi, -236(%rbp)
	movl	%edx, -240(%rbp)
	movl	-240(%rbp), %eax
	addl	$2, %eax
	cmpl	%eax, -236(%rbp)
	jle	.L433
	movl	-240(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-232(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	leaq	-224(%rbp), %rax
	leaq	.LC62(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	sprintf@PLT
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	emb_identify_format@PLT
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	jns	.L434
	leaq	.LC63(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L434:
	movl	-240(%rbp), %eax
	addl	$2, %eax
	movl	%eax, -4(%rbp)
	jmp	.L435
.L436:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-232(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	string_len
	movl	%eax, -12(%rbp)
	movb	$0, -224(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-232(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	leaq	-224(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	movl	-12(%rbp), %eax
	subl	$4, %eax
	cltq
	movb	$0, -224(%rbp,%rax)
	movl	-8(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	formatTable(%rip), %rdx
	addq	%rax, %rdx
	leaq	-224(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-232(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	-224(%rbp), %rdx
	movq	%rax, %rsi
	leaq	.LC64(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-232(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	-224(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	convert
	addl	$1, -4(%rbp)
.L435:
	movl	-4(%rbp), %eax
	cmpl	-236(%rbp), %eax
	jl	.L436
	jmp	.L438
.L433:
	leaq	.LC65(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC66(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC67(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L438:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE96:
	.size	to_flag, .-to_flag
	.globl	rules
	.section	.rodata
.LC68:
	.string	"+BF-AFA-FB+"
.LC69:
	.string	"-AF+BFB+FA-"
	.section	.data.rel.local
	.align 16
	.type	rules, @object
	.size	rules, 16
rules:
	.quad	.LC68
	.quad	.LC69
	.globl	hilbert_curve_l_system
	.section	.rodata
.LC70:
	.string	"AB"
.LC71:
	.string	"F+-"
	.section	.data.rel.local
	.align 32
	.type	hilbert_curve_l_system, @object
	.size	hilbert_curve_l_system, 32
hilbert_curve_l_system:
	.byte	65
	.zero	7
	.quad	.LC70
	.quad	.LC71
	.quad	rules
	.text
	.globl	lindenmayer_system
	.type	lindenmayer_system, @function
lindenmayer_system:
.LFB97:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	cmpl	$0, -32(%rbp)
	jne	.L440
	movzbl	16(%rbp), %edx
	movq	-24(%rbp), %rax
	movb	%dl, (%rax)
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movb	$0, (%rax)
	movl	-32(%rbp), %eax
	leal	1(%rax), %r8d
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rdi
	subq	$32, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	40(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movl	%r8d, %edx
	call	lindenmayer_system
	addq	$32, %rsp
	movl	$0, %eax
	jmp	.L441
.L440:
	movq	-24(%rbp), %rax
	addq	$5000000, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movb	$0, (%rax)
	movl	$0, -4(%rbp)
	jmp	.L442
.L447:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$64, %al
	jle	.L443
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$69, %al
	jg	.L443
	movq	40(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rcx
	movq	-24(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rdx), %edx
	movsbq	%dl, %rdx
	salq	$3, %rdx
	subq	$520, %rdx
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
.L443:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$70, %al
	jne	.L444
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movw	$70, (%rax)
.L444:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$43, %al
	jne	.L445
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movw	$43, (%rax)
.L445:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$45, %al
	jne	.L446
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movw	$45, (%rax)
.L446:
	addl	$1, -4(%rbp)
.L442:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	string_len
	cmpl	%eax, -4(%rbp)
	jl	.L447
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	string_len
	addl	$1, %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	movl	-32(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jge	.L448
	movl	-32(%rbp), %eax
	leal	1(%rax), %r8d
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rdi
	subq	$32, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	40(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movl	%r8d, %edx
	call	lindenmayer_system
	addq	$32, %rsp
.L448:
	movl	$0, %eax
.L441:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE97:
	.size	lindenmayer_system, .-lindenmayer_system
	.type	join_short_stitches, @function
join_short_stitches:
.LFB98:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movl	%ecx, -56(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L450
.L459:
	movl	$0, -4(%rbp)
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	subl	$2, %eax
	movl	%eax, -8(%rbp)
	jmp	.L451
.L456:
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-52(%rbp)
	movl	%edx, %ecx
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-52(%rbp)
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-52(%rbp)
	movl	%edx, %ecx
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-52(%rbp)
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, -16(%rbp)
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-52(%rbp)
	movl	%eax, %ecx
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-52(%rbp)
	cmpl	%eax, %ecx
	jne	.L452
	movl	-8(%rbp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-52(%rbp)
	movl	%eax, %ecx
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-52(%rbp)
	cmpl	%eax, %ecx
	jne	.L452
	movl	$1, %eax
	jmp	.L453
.L452:
	movl	$0, %eax
.L453:
	movl	%eax, -20(%rbp)
	movl	-12(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jge	.L454
	movl	-16(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jge	.L454
	cmpl	$0, -20(%rbp)
	je	.L454
	addl	$1, -4(%rbp)
	jmp	.L455
.L454:
	subl	$1, -8(%rbp)
.L451:
	cmpl	$0, -8(%rbp)
	jns	.L456
.L455:
	cmpl	$0, -4(%rbp)
	je	.L450
	addl	$1, -8(%rbp)
	jmp	.L457
.L458:
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-40(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -8(%rbp)
.L457:
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L458
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-48(%rbp), %rax
	movl	%edx, (%rax)
.L450:
	cmpl	$0, -4(%rbp)
	jg	.L459
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE98:
	.size	join_short_stitches, .-join_short_stitches
	.type	threshold_method, @function
threshold_method:
.LFB99:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movl	%ecx, -56(%rbp)
	movl	%r8d, -60(%rbp)
	movq	-40(%rbp), %rax
	movl	28(%rax), %eax
	movl	%eax, -12(%rbp)
	movq	-40(%rbp), %rax
	movl	24(%rax), %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %eax
	cltd
	idivl	-56(%rbp)
	movl	%eax, %ecx
	movl	-16(%rbp), %eax
	cltd
	idivl	-52(%rbp)
	imull	%ecx, %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	movq	-48(%rbp), %rax
	movl	$0, (%rax)
	movl	$0, -4(%rbp)
	jmp	.L461
.L465:
	movl	$0, -8(%rbp)
	jmp	.L462
.L464:
	movl	-56(%rbp), %eax
	imull	-4(%rbp), %eax
	imull	-16(%rbp), %eax
	movl	%eax, %edx
	movl	-52(%rbp), %eax
	imull	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -28(%rbp)
	movq	-40(%rbp), %rax
	movq	16(%rax), %rcx
	movl	-28(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	cltq
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, -31(%rbp)
	movq	-40(%rbp), %rax
	movq	16(%rax), %rcx
	movl	-28(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	cltq
	addq	$1, %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, -30(%rbp)
	movq	-40(%rbp), %rax
	movq	16(%rax), %rcx
	movl	-28(%rbp), %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	cltq
	addq	$2, %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movb	%al, -29(%rbp)
	movzbl	-31(%rbp), %eax
	movzbl	%al, %edx
	movzbl	-30(%rbp), %eax
	movzbl	%al, %eax
	addl	%eax, %edx
	movzbl	-29(%rbp), %eax
	movzbl	%al, %eax
	addl	%edx, %eax
	cmpl	%eax, -60(%rbp)
	jle	.L463
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-28(%rbp), %eax
	movl	%eax, (%rdx)
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-48(%rbp), %rax
	movl	%edx, (%rax)
.L463:
	addl	$1, -8(%rbp)
.L462:
	movl	-16(%rbp), %eax
	cltd
	idivl	-52(%rbp)
	cmpl	%eax, -8(%rbp)
	jl	.L464
	addl	$1, -4(%rbp)
.L461:
	movl	-12(%rbp), %eax
	cltd
	idivl	-56(%rbp)
	cmpl	%eax, -4(%rbp)
	jl	.L465
	movq	-24(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE99:
	.size	threshold_method, .-threshold_method
	.section	.rodata
.LC72:
	.string	"points[0] = %d\n"
.LC73:
	.string	"n_points = %d\n"
.LC74:
	.string	"width = %d\n"
.LC75:
	.string	"bias = %f\n"
.LC78:
	.string	"%2.1f%%\n"
	.text
	.type	greedy_algorithm, @function
greedy_algorithm:
.LFB100:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movl	%edx, -64(%rbp)
	movss	%xmm0, -68(%rbp)
	movq	-56(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC72(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-60(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC73(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-64(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC74(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	pxor	%xmm3, %xmm3
	cvtss2sd	-68(%rbp), %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	leaq	.LC75(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, -4(%rbp)
	jmp	.L468
.L476:
	movss	.LC76(%rip), %xmm0
	movss	%xmm0, -12(%rbp)
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-64(%rbp)
	movl	%edx, -20(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-64(%rbp)
	movl	%eax, -24(%rbp)
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -8(%rbp)
	jmp	.L469
.L474:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-64(%rbp)
	movl	-20(%rbp), %eax
	subl	%edx, %eax
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %eax
	imull	%eax, %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	comiss	-12(%rbp), %xmm0
	ja	.L478
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-64(%rbp)
	movl	%eax, %edx
	movl	-24(%rbp), %eax
	subl	%edx, %eax
	movl	%eax, -36(%rbp)
	movl	-32(%rbp), %eax
	imull	%eax, %eax
	pxor	%xmm1, %xmm1
	cvtsi2ssl	%eax, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-36(%rbp), %xmm0
	movaps	%xmm0, %xmm2
	mulss	-68(%rbp), %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-36(%rbp), %xmm0
	mulss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -40(%rbp)
	movss	-12(%rbp), %xmm0
	comiss	-40(%rbp), %xmm0
	jbe	.L472
	movl	-8(%rbp), %eax
	movl	%eax, -16(%rbp)
	movss	-40(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	jmp	.L472
.L478:
	nop
.L472:
	addl	$1, -8(%rbp)
.L469:
	movl	-8(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L474
	movl	-4(%rbp), %edx
	movslq	%edx, %rax
	imulq	$1374389535, %rax, %rax
	shrq	$32, %rax
	sarl	$5, %eax
	movl	%edx, %ecx
	sarl	$31, %ecx
	subl	%ecx, %eax
	imull	$100, %eax, %ecx
	movl	%edx, %eax
	subl	%ecx, %eax
	testl	%eax, %eax
	jne	.L475
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-4(%rbp), %xmm1
	movsd	.LC77(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-60(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leaq	.LC78(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
.L475:
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -28(%rbp)
	movl	-4(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	-16(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-56(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	-4(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	-56(%rbp), %rax
	addq	%rax, %rdx
	movl	-28(%rbp), %eax
	movl	%eax, (%rdx)
	addl	$1, -4(%rbp)
.L468:
	movl	-60(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -4(%rbp)
	jl	.L476
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE100:
	.size	greedy_algorithm, .-greedy_algorithm
	.type	save_points_to_pattern, @function
save_points_to_pattern:
.LFB101:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movss	%xmm0, -40(%rbp)
	movl	%ecx, -44(%rbp)
	movl	%r8d, -48(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L480
.L481:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-44(%rbp)
	movl	%edx, -8(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-44(%rbp)
	movl	%eax, %edx
	movl	-48(%rbp), %eax
	subl	%edx, %eax
	movl	%eax, -12(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-12(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	mulss	-40(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-8(%rbp), %xmm0
	mulss	-40(%rbp), %xmm0
	movd	%xmm0, %ecx
	movq	-24(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	addl	$1, -4(%rbp)
.L480:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L481
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE101:
	.size	save_points_to_pattern, .-save_points_to_pattern
	.globl	emb_pattern_horizontal_fill
	.type	emb_pattern_horizontal_fill, @function
emb_pattern_horizontal_fill:
.LFB102:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -52(%rbp)
	movss	.LC79(%rip), %xmm0
	movss	%xmm0, -4(%rbp)
	movl	$3, -8(%rbp)
	movl	$3, -12(%rbp)
	movss	.LC80(%rip), %xmm0
	movss	%xmm0, -16(%rbp)
	movl	-52(%rbp), %edi
	movl	-12(%rbp), %ecx
	movl	-8(%rbp), %edx
	leaq	-28(%rbp), %rsi
	movq	-48(%rbp), %rax
	movl	%edi, %r8d
	movq	%rax, %rdi
	call	threshold_method
	movq	%rax, -24(%rbp)
	movq	-48(%rbp), %rax
	movl	24(%rax), %edx
	movl	-28(%rbp), %ecx
	movl	-16(%rbp), %esi
	movq	-24(%rbp), %rax
	movd	%esi, %xmm0
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	greedy_algorithm
	movq	-48(%rbp), %rax
	movl	24(%rax), %edx
	leaq	-28(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$40, %ecx
	movq	%rax, %rdi
	call	join_short_stitches
	movq	-48(%rbp), %rax
	movl	28(%rax), %r8d
	movq	-48(%rbp), %rax
	movl	24(%rax), %ecx
	movl	-28(%rbp), %edx
	movl	-4(%rbp), %edi
	movq	-24(%rbp), %rsi
	movq	-40(%rbp), %rax
	movd	%edi, %xmm0
	movq	%rax, %rdi
	call	save_points_to_pattern
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_end
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE102:
	.size	emb_pattern_horizontal_fill, .-emb_pattern_horizontal_fill
	.section	.rodata
.LC82:
	.string	"%f %f\n"
	.text
	.globl	emb_pattern_crossstitch
	.type	emb_pattern_crossstitch, @function
emb_pattern_crossstitch:
.LFB103:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movl	%edx, -68(%rbp)
	movss	.LC79(%rip), %xmm0
	movss	%xmm0, -8(%rbp)
	movl	$5, -12(%rbp)
	movl	$5, -16(%rbp)
	movss	.LC81(%rip), %xmm0
	movss	%xmm0, -20(%rbp)
	movl	$1000, -24(%rbp)
	movl	-68(%rbp), %edi
	movl	-16(%rbp), %ecx
	movl	-12(%rbp), %edx
	leaq	-44(%rbp), %rsi
	movq	-64(%rbp), %rax
	movl	%edi, %r8d
	movq	%rax, %rdi
	call	threshold_method
	movq	%rax, -32(%rbp)
	movl	-44(%rbp), %ecx
	movl	-20(%rbp), %esi
	movl	-24(%rbp), %edx
	movq	-32(%rbp), %rax
	movd	%esi, %xmm0
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	greedy_algorithm
	movl	$0, -4(%rbp)
	jmp	.L484
.L485:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-24(%rbp)
	movl	%edx, %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, -36(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltd
	idivl	-24(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	%xmm0, -40(%rbp)
	pxor	%xmm0, %xmm0
	cvtss2sd	-40(%rbp), %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	-36(%rbp), %xmm2
	movq	%xmm2, %rax
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC82(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
	movss	-8(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	mulss	-40(%rbp), %xmm1
	movss	-8(%rbp), %xmm0
	mulss	-36(%rbp), %xmm0
	movd	%xmm0, %ecx
	movq	-56(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-16(%rbp), %xmm0
	addss	-40(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	mulss	-8(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-12(%rbp), %xmm0
	addss	-36(%rbp), %xmm0
	mulss	-8(%rbp), %xmm0
	movd	%xmm0, %ecx
	movq	-56(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-16(%rbp), %xmm0
	addss	-40(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	mulss	-8(%rbp), %xmm1
	movss	-8(%rbp), %xmm0
	mulss	-36(%rbp), %xmm0
	movd	%xmm0, %ecx
	movq	-56(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	movss	-8(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	mulss	-40(%rbp), %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-12(%rbp), %xmm0
	addss	-36(%rbp), %xmm0
	mulss	-8(%rbp), %xmm0
	movd	%xmm0, %ecx
	movq	-56(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	addl	$1, -4(%rbp)
.L484:
	movl	-44(%rbp), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L485
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_end
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE103:
	.size	emb_pattern_crossstitch, .-emb_pattern_crossstitch
	.globl	hilbert_curve
	.type	hilbert_curve, @function
hilbert_curve:
.LFB104:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movss	.LC81(%rip), %xmm0
	movss	%xmm0, -12(%rbp)
	movl	$10000000, %edi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	movl	-60(%rbp), %esi
	movq	-24(%rbp), %rdi
	subq	$32, %rsp
	movq	%rsp, %rcx
	movq	hilbert_curve_l_system(%rip), %rax
	movq	8+hilbert_curve_l_system(%rip), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	16+hilbert_curve_l_system(%rip), %rax
	movq	24+hilbert_curve_l_system(%rip), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movl	$0, %edx
	call	lindenmayer_system
	addq	$32, %rsp
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L487
.L496:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$43, %al
	jne	.L488
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$30, %eax
	addl	%eax, %edx
	andl	$3, %edx
	subl	%eax, %edx
	movl	%edx, -8(%rbp)
	jmp	.L489
.L488:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$45, %al
	jne	.L490
	movl	-8(%rbp), %eax
	leal	3(%rax), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$30, %eax
	addl	%eax, %edx
	andl	$3, %edx
	subl	%eax, %edx
	movl	%edx, -8(%rbp)
	jmp	.L489
.L490:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$70, %al
	jne	.L489
	movl	$0, -28(%rbp)
	cmpl	$3, -8(%rbp)
	je	.L491
	cmpl	$3, -8(%rbp)
	jg	.L492
	cmpl	$1, -8(%rbp)
	je	.L493
	cmpl	$2, -8(%rbp)
	je	.L494
.L492:
	movl	-36(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	.L495
.L493:
	movl	-32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -32(%rbp)
	jmp	.L495
.L494:
	movl	-36(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -36(%rbp)
	jmp	.L495
.L491:
	movl	-32(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -32(%rbp)
	nop
.L495:
	movl	-32(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movaps	%xmm0, %xmm1
	mulss	-12(%rbp), %xmm1
	movl	-36(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	mulss	-12(%rbp), %xmm0
	movd	%xmm0, %ecx
	movl	-28(%rbp), %esi
	movq	-56(%rbp), %rax
	movl	$0, %edx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
.L489:
	addl	$1, -4(%rbp)
.L487:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	string_len
	cmpl	%eax, -4(%rbp)
	jl	.L496
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_end
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE104:
	.size	hilbert_curve, .-hilbert_curve
	.globl	generate_dragon_curve
	.type	generate_dragon_curve, @function
generate_dragon_curve:
.LFB105:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	cmpl	$1, -28(%rbp)
	jne	.L499
	movq	-24(%rbp), %rax
	movb	$82, (%rax)
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movb	$0, (%rax)
	jmp	.L498
.L499:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	string_len
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -4(%rbp)
	jmp	.L501
.L504:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	-4(%rbp), %edx
	addl	%edx, %edx
	movslq	%edx, %rdx
	leaq	1(%rdx), %rcx
	movq	-24(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	movl	-4(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L502
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$82, (%rax)
	jmp	.L503
.L502:
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$76, (%rax)
.L503:
	subl	$1, -4(%rbp)
.L501:
	cmpl	$0, -4(%rbp)
	jns	.L504
	movl	-8(%rbp), %eax
	addl	%eax, %eax
	cltq
	leaq	1(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movl	-28(%rbp), %eax
	leal	-1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	generate_dragon_curve
.L498:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE105:
	.size	generate_dragon_curve, .-generate_dragon_curve
	.section	.rodata
	.align 8
.LC83:
	.string	"The dragon curve is only supported up to 10 iterations."
	.text
	.globl	dragon_curve
	.type	dragon_curve, @function
dragon_curve:
.LFB106:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	cmpl	$10, -20(%rbp)
	jle	.L506
	leaq	.LC83(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L507
.L506:
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movl	-20(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	generate_dragon_curve
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free
	movl	$1, %eax
.L507:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE106:
	.size	dragon_curve, .-dragon_curve
	.globl	embPolygon_reduceByDistance
	.type	embPolygon_reduceByDistance, @function
embPolygon_reduceByDistance:
.LFB107:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movss	%xmm0, -36(%rbp)
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$2, %eax
	jg	.L509
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_array_copy
	jmp	.L508
.L509:
	movl	$0, -4(%rbp)
	jmp	.L511
.L515:
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	24(%rax), %ecx
	movl	%edx, %eax
	cltd
	idivl	%ecx
	movl	%edx, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rax, %rcx
	movq	-24(%rbp), %rax
	movq	(%rax), %rsi
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rsi, %rax
	movq	(%rcx), %rdx
	movq	(%rax), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract@PLT
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_length@PLT
	movss	-36(%rbp), %xmm1
	comiss	%xmm0, %xmm1
	ja	.L516
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
	jmp	.L514
.L516:
	nop
.L514:
	addl	$1, -4(%rbp)
.L511:
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L515
.L508:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE107:
	.size	embPolygon_reduceByDistance, .-embPolygon_reduceByDistance
	.globl	embPolygon_reduceByNth
	.type	embPolygon_reduceByNth, @function
embPolygon_reduceByNth:
.LFB108:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	$2, %eax
	jg	.L518
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_array_copy
	jmp	.L517
.L518:
	movl	$0, -4(%rbp)
	jmp	.L520
.L522:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	je	.L521
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %xmm0
	movq	%rax, %rdi
	call	emb_array_addVector
.L521:
	addl	$1, -4(%rbp)
.L520:
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L522
.L517:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE108:
	.size	embPolygon_reduceByNth, .-embPolygon_reduceByNth
	.globl	emb_pattern_combine
	.type	emb_pattern_combine, @function
emb_pattern_combine:
.LFB109:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	call	emb_pattern_create
	movq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L524
.L525:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	-16(%rbp), %rdx
	movq	32(%rdx), %rcx
	movq	(%rax), %rdx
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdx
	movq	%rcx, %rdi
	call	emb_array_addStitch
	addl	$1, -4(%rbp)
.L524:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L525
	movl	$0, -4(%rbp)
	jmp	.L526
.L527:
	movq	-32(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	-16(%rbp), %rdx
	movq	32(%rdx), %rcx
	movq	(%rax), %rdx
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdx
	movq	%rcx, %rdi
	call	emb_array_addStitch
	addl	$1, -4(%rbp)
.L526:
	movq	-32(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L527
	movl	$0, -4(%rbp)
	jmp	.L528
.L529:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movq	-16(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rdx
	movl	$50, %ecx
	movq	%rdx, %rdi
	movq	%rax, %rsi
	rep movsq
	movq	%rsi, %rax
	movq	%rdi, %rdx
	movzwl	(%rax), %ecx
	movw	%cx, (%rdx)
	leaq	2(%rdx), %rdx
	leaq	2(%rax), %rax
	movzbl	(%rax), %ecx
	movb	%cl, (%rdx)
	movq	%r8, %rdi
	call	emb_pattern_addThread
	addq	$416, %rsp
	addl	$1, -4(%rbp)
.L528:
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L529
	movl	$0, -4(%rbp)
	jmp	.L530
.L531:
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movq	-16(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rdx
	movl	$50, %ecx
	movq	%rdx, %rdi
	movq	%rax, %rsi
	rep movsq
	movq	%rsi, %rax
	movq	%rdi, %rdx
	movzwl	(%rax), %ecx
	movw	%cx, (%rdx)
	leaq	2(%rdx), %rdx
	leaq	2(%rax), %rax
	movzbl	(%rax), %ecx
	movb	%cl, (%rdx)
	movq	%r8, %rdi
	call	emb_pattern_addThread
	addq	$416, %rsp
	addl	$1, -4(%rbp)
.L530:
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L531
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE109:
	.size	emb_pattern_combine, .-emb_pattern_combine
	.section	.rodata
	.align 8
.LC84:
	.string	"DEBUG stitchArc (unfinished): %f %f %d %d\n"
	.text
	.globl	emb_pattern_stitchArc
	.type	emb_pattern_stitchArc, @function
emb_pattern_stitchArc:
.LFB110:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movss	16(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movq	%xmm2, %rax
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %ecx
	movl	%ecx, %esi
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC84(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE110:
	.size	emb_pattern_stitchArc, .-emb_pattern_stitchArc
	.section	.rodata
.LC86:
	.string	"style %d\n"
	.text
	.globl	emb_pattern_stitchCircle
	.type	emb_pattern_stitchCircle, @function
emb_pattern_stitchCircle:
.LFB111:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -88(%rbp)
	movq	%xmm0, %rax
	movaps	%xmm1, %xmm0
	movl	%esi, -108(%rbp)
	movl	%edx, -112(%rbp)
	movq	%rax, -104(%rbp)
	movss	%xmm0, -96(%rbp)
	movss	.LC79(%rip), %xmm0
	movss	%xmm0, -8(%rbp)
	movss	.LC81(%rip), %xmm0
	movss	%xmm0, -20(%rbp)
	movss	.LC81(%rip), %xmm0
	movss	%xmm0, -16(%rbp)
	movss	.LC85(%rip), %xmm0
	movss	%xmm0, -28(%rbp)
	movss	.LC81(%rip), %xmm0
	movss	%xmm0, -24(%rbp)
	movq	-20(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_normalize@PLT
	movq	%xmm0, %rax
	movq	%rax, -20(%rbp)
	movq	-28(%rbp), %rax
	movq	%rax, %xmm0
	call	emb_vector_normalize@PLT
	movq	%xmm0, %rax
	movq	%rax, -28(%rbp)
	movl	-112(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC86(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movss	-96(%rbp), %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	jmp	.L535
.L536:
	movss	-96(%rbp), %xmm1
	movss	-96(%rbp), %xmm0
	mulss	%xmm0, %xmm1
	movss	-4(%rbp), %xmm0
	mulss	%xmm0, %xmm0
	subss	%xmm0, %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-4(%rbp), %xmm0
	movq	-28(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale@PLT
	movq	%xmm0, %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rdx
	movq	-104(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -64(%rbp)
	movss	-12(%rbp), %xmm0
	movq	-20(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale@PLT
	movq	%xmm0, %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_subtract@PLT
	movq	%xmm0, %rax
	movq	%rax, -64(%rbp)
	movss	-4(%rbp), %xmm0
	movq	-28(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale@PLT
	movq	%xmm0, %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rdx
	movq	-104(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -56(%rbp)
	movss	-12(%rbp), %xmm0
	movq	-20(%rbp), %rax
	movaps	%xmm0, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_scale@PLT
	movq	%xmm0, %rax
	movq	%rax, -72(%rbp)
	movq	-72(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_add@PLT
	movq	%xmm0, %rax
	movq	%rax, -56(%rbp)
	movss	-60(%rbp), %xmm0
	movl	-64(%rbp), %ecx
	movl	-108(%rbp), %edx
	movq	-88(%rbp), %rax
	movl	$0, %esi
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	movss	-52(%rbp), %xmm0
	movl	-56(%rbp), %ecx
	movl	-108(%rbp), %edx
	movq	-88(%rbp), %rax
	movl	$0, %esi
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	movss	-4(%rbp), %xmm0
	addss	-8(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
.L535:
	movss	-96(%rbp), %xmm0
	comiss	-4(%rbp), %xmm0
	ja	.L536
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE111:
	.size	emb_pattern_stitchCircle, .-emb_pattern_stitchCircle
	.section	.rodata
	.align 8
.LC87:
	.string	"DEBUG stitchEllipse: %f %f %d %d\n"
	.text
	.globl	emb_pattern_stitchEllipse
	.type	emb_pattern_stitchEllipse, @function
emb_pattern_stitchEllipse:
.LFB112:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movss	16(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movq	%xmm2, %rax
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %ecx
	movl	%ecx, %esi
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC87(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE112:
	.size	emb_pattern_stitchEllipse, .-emb_pattern_stitchEllipse
	.section	.rodata
	.align 8
.LC88:
	.string	"DEBUG stitchPath: %f %d %d %d\n"
	.text
	.globl	emb_pattern_stitchPath
	.type	emb_pattern_stitchPath, @function
emb_pattern_stitchPath:
.LFB113:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movq	16(%rbp), %rax
	movl	24(%rax), %esi
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movl	-16(%rbp), %ecx
	movl	-12(%rbp), %edx
	movq	%rax, %xmm0
	leaq	.LC88(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE113:
	.size	emb_pattern_stitchPath, .-emb_pattern_stitchPath
	.section	.rodata
	.align 8
.LC89:
	.string	"DEBUG stitchPolygon: %f %d %d %d\n"
	.text
	.globl	emb_pattern_stitchPolygon
	.type	emb_pattern_stitchPolygon, @function
emb_pattern_stitchPolygon:
.LFB114:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movq	16(%rbp), %rax
	movl	24(%rax), %esi
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movl	-16(%rbp), %ecx
	movl	-12(%rbp), %edx
	movq	%rax, %xmm0
	leaq	.LC89(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE114:
	.size	emb_pattern_stitchPolygon, .-emb_pattern_stitchPolygon
	.section	.rodata
	.align 8
.LC90:
	.string	"DEBUG stitchPolyline: %f %d %d %d\n"
	.text
	.globl	emb_pattern_stitchPolyline
	.type	emb_pattern_stitchPolyline, @function
emb_pattern_stitchPolyline:
.LFB115:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movq	16(%rbp), %rax
	movl	24(%rax), %esi
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movl	-16(%rbp), %ecx
	movl	-12(%rbp), %edx
	movq	%rax, %xmm0
	leaq	.LC90(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE115:
	.size	emb_pattern_stitchPolyline, .-emb_pattern_stitchPolyline
	.section	.rodata
	.align 8
.LC91:
	.string	"WARNING: Only style 0 has been implimented."
	.text
	.globl	emb_pattern_stitchRect
	.type	emb_pattern_stitchRect, @function
emb_pattern_stitchRect:
.LFB116:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movss	.LC79(%rip), %xmm0
	movss	%xmm0, -12(%rbp)
	cmpl	$0, -32(%rbp)
	jle	.L542
	leaq	.LC91(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L542:
	movss	24(%rbp), %xmm0
	movss	28(%rbp), %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L551
	movss	20(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
	jmp	.L545
.L546:
	movl	20(%rbp), %ecx
	movl	-28(%rbp), %edx
	movss	-4(%rbp), %xmm0
	movq	-24(%rbp), %rax
	movl	$0, %esi
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	movss	20(%rbp), %xmm1
	movss	28(%rbp), %xmm0
	addss	%xmm0, %xmm1
	movd	%xmm1, %ecx
	movl	-28(%rbp), %edx
	movss	-4(%rbp), %xmm0
	movq	-24(%rbp), %rax
	movl	$0, %esi
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	movss	-4(%rbp), %xmm0
	addss	-12(%rbp), %xmm0
	movss	%xmm0, -4(%rbp)
.L545:
	movss	20(%rbp), %xmm1
	movss	28(%rbp), %xmm0
	addss	%xmm1, %xmm0
	comiss	-4(%rbp), %xmm0
	ja	.L546
	jmp	.L552
.L551:
	movss	16(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	jmp	.L548
.L549:
	movss	16(%rbp), %xmm0
	movl	-28(%rbp), %edx
	movl	-8(%rbp), %ecx
	movq	-24(%rbp), %rax
	movl	$0, %esi
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	movss	16(%rbp), %xmm1
	movss	24(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movl	-28(%rbp), %edx
	movl	-8(%rbp), %ecx
	movq	-24(%rbp), %rax
	movl	$0, %esi
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	movss	-8(%rbp), %xmm0
	addss	-12(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
.L548:
	movss	16(%rbp), %xmm1
	movss	24(%rbp), %xmm0
	addss	%xmm1, %xmm0
	comiss	-8(%rbp), %xmm0
	ja	.L549
.L552:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE116:
	.size	emb_pattern_stitchRect, .-emb_pattern_stitchRect
	.section	.rodata
.LC92:
	.string	"DEBUG: %f %f %d %d"
	.text
	.globl	emb_pattern_stitchText
	.type	emb_pattern_stitchText, @function
emb_pattern_stitchText:
.LFB117:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movss	20(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movq	-8(%rbp), %rax
	movss	8(%rax), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movq	%xmm2, %rax
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %ecx
	movl	%ecx, %esi
	movapd	%xmm0, %xmm1
	movq	%rax, %xmm0
	leaq	.LC92(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE117:
	.size	emb_pattern_stitchText, .-emb_pattern_stitchText
	.globl	emb_pattern_convertGeometry
	.type	emb_pattern_convertGeometry, @function
emb_pattern_convertGeometry:
.LFB118:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L555
.L562:
	movq	-72(%rbp), %rax
	movq	40(%rax), %rax
	movq	(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -64(%rbp)
	movq	%rbx, -56(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -48(%rbp)
	movq	%rbx, -40(%rbp)
	movq	32(%rax), %rax
	movq	%rax, -32(%rbp)
	movl	-36(%rbp), %eax
	cmpl	$13, %eax
	je	.L556
	cmpl	$13, %eax
	jg	.L563
	cmpl	$5, %eax
	je	.L558
	cmpl	$5, %eax
	jg	.L563
	cmpl	$1, %eax
	je	.L559
	cmpl	$2, %eax
	je	.L560
	jmp	.L563
.L559:
	movq	-72(%rbp), %rdi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-48(%rbp), %rax
	movq	%rax, 16(%rcx)
	movl	$0, %edx
	movl	$0, %esi
	call	emb_pattern_stitchArc
	addq	$32, %rsp
	jmp	.L561
.L560:
	movq	-64(%rbp), %rcx
	movss	-56(%rbp), %xmm1
	movq	-72(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rcx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_stitchCircle
	jmp	.L561
.L558:
	movq	-72(%rbp), %rdi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movl	-48(%rbp), %eax
	movl	%eax, 16(%rcx)
	movl	$0, %edx
	movl	$0, %esi
	call	emb_pattern_stitchEllipse
	addq	$32, %rsp
	jmp	.L561
.L556:
	movq	-72(%rbp), %rdi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-48(%rbp), %rax
	movq	%rax, 16(%rcx)
	movl	$0, %edx
	movl	$0, %esi
	call	emb_pattern_stitchRect
	addq	$32, %rsp
	jmp	.L561
.L563:
	nop
.L561:
	addl	$1, -20(%rbp)
.L555:
	movq	-72(%rbp), %rax
	movq	40(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L562
	movq	-72(%rbp), %rax
	movq	40(%rax), %rax
	movl	$0, 24(%rax)
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE118:
	.size	emb_pattern_convertGeometry, .-emb_pattern_convertGeometry
	.globl	imageWithFrame
	.section	.rodata
	.align 32
	.type	imageWithFrame, @object
	.size	imageWithFrame, 1824
imageWithFrame:
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	"\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001\001"
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.string	""
	.text
	.globl	safe_free
	.type	safe_free, @function
safe_free:
.LFB119:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L566
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	$0, -8(%rbp)
.L566:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE119:
	.size	safe_free, .-safe_free
	.globl	char_to_lower
	.type	char_to_lower, @function
char_to_lower:
.LFB120:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$64, -4(%rbp)
	jbe	.L568
	cmpb	$90, -4(%rbp)
	ja	.L568
	addb	$32, -4(%rbp)
.L568:
	movzbl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE120:
	.size	char_to_lower, .-char_to_lower
	.section	.rodata
	.align 8
.LC93:
	.string	"ERROR: format-pec.c writeImage(), file argument is null"
	.text
	.globl	writeImage
	.type	writeImage, @function
writeImage:
.LFB121:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L571
	leaq	.LC93(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L570
.L571:
	movl	$0, -4(%rbp)
	jmp	.L573
.L590:
	movl	$0, -8(%rbp)
	jmp	.L574
.L589:
	movl	-8(%rbp), %eax
	sall	$3, %eax
	movl	%eax, -12(%rbp)
	movb	$0, -13(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	cltq
	movzbl	(%rdx,%rax), %eax
	testb	%al, %al
	setne	%al
	movl	%eax, %edx
	movzbl	-13(%rbp), %eax
	orl	%edx, %eax
	movb	%al, -13(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	addl	$1, %eax
	cltq
	movzbl	(%rdx,%rax), %eax
	testb	%al, %al
	je	.L575
	movl	$2, %edx
	jmp	.L576
.L575:
	movl	$0, %edx
.L576:
	movzbl	-13(%rbp), %eax
	orl	%edx, %eax
	movb	%al, -13(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	addl	$2, %eax
	cltq
	movzbl	(%rdx,%rax), %eax
	testb	%al, %al
	je	.L577
	movl	$4, %edx
	jmp	.L578
.L577:
	movl	$0, %edx
.L578:
	movzbl	-13(%rbp), %eax
	orl	%edx, %eax
	movb	%al, -13(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	addl	$3, %eax
	cltq
	movzbl	(%rdx,%rax), %eax
	testb	%al, %al
	je	.L579
	movl	$8, %edx
	jmp	.L580
.L579:
	movl	$0, %edx
.L580:
	movzbl	-13(%rbp), %eax
	orl	%edx, %eax
	movb	%al, -13(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	addl	$4, %eax
	cltq
	movzbl	(%rdx,%rax), %eax
	testb	%al, %al
	je	.L581
	movl	$16, %edx
	jmp	.L582
.L581:
	movl	$0, %edx
.L582:
	movzbl	-13(%rbp), %eax
	orl	%edx, %eax
	movb	%al, -13(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	addl	$5, %eax
	cltq
	movzbl	(%rdx,%rax), %eax
	testb	%al, %al
	je	.L583
	movl	$32, %edx
	jmp	.L584
.L583:
	movl	$0, %edx
.L584:
	movzbl	-13(%rbp), %eax
	orl	%edx, %eax
	movb	%al, -13(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	addl	$6, %eax
	cltq
	movzbl	(%rdx,%rax), %eax
	testb	%al, %al
	je	.L585
	movl	$64, %edx
	jmp	.L586
.L585:
	movl	$0, %edx
.L586:
	movzbl	-13(%rbp), %eax
	orl	%edx, %eax
	movb	%al, -13(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	addl	$7, %eax
	cltq
	movzbl	(%rdx,%rax), %eax
	testb	%al, %al
	je	.L587
	movl	$-128, %edx
	jmp	.L588
.L587:
	movl	$0, %edx
.L588:
	movzbl	-13(%rbp), %eax
	orl	%edx, %eax
	movb	%al, -13(%rbp)
	movq	-24(%rbp), %rdx
	leaq	-13(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	addl	$1, -8(%rbp)
.L574:
	cmpl	$5, -8(%rbp)
	jle	.L589
	addl	$1, -4(%rbp)
.L573:
	cmpl	$37, -4(%rbp)
	jle	.L590
.L570:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE121:
	.size	writeImage, .-writeImage
	.globl	image_diff
	.type	image_diff, @function
image_diff:
.LFB122:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L592
.L593:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %edx
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	subl	%eax, %edx
	movl	%edx, -12(%rbp)
	movl	-12(%rbp), %eax
	imull	%eax, %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	movss	-8(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	addl	$1, -4(%rbp)
.L592:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L593
	movss	-8(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE122:
	.size	image_diff, .-image_diff
	.section	.rodata
.LC94:
	.string	"Cannot render %p, %s\n"
	.text
	.globl	emb_pattern_render
	.type	emb_pattern_render, @function
emb_pattern_render:
.LFB123:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC94(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE123:
	.size	emb_pattern_render, .-emb_pattern_render
	.globl	emb_pattern_simulate
	.type	emb_pattern_simulate, @function
emb_pattern_simulate:
.LFB124:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_render
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE124:
	.size	emb_pattern_simulate, .-emb_pattern_simulate
	.globl	embImage_create
	.type	embImage_create, @function
embImage_create:
.LFB125:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$448, %rsp
	movq	%rdi, -440(%rbp)
	movl	%esi, -444(%rbp)
	movl	%edx, -448(%rbp)
	movl	-444(%rbp), %eax
	movl	%eax, -408(%rbp)
	movl	-448(%rbp), %eax
	movl	%eax, -404(%rbp)
	movl	-444(%rbp), %eax
	imull	-448(%rbp), %eax
	sall	$2, %eax
	cltq
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -416(%rbp)
	movq	-440(%rbp), %rax
	movq	%rax, %rdi
	leaq	-432(%rbp), %rax
	movl	$54, %edx
	movq	%rax, %rsi
	movq	%rdx, %rcx
	rep movsq
	movq	-440(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE125:
	.size	embImage_create, .-embImage_create
	.section	.rodata
.LC95:
	.string	"%d, %s\n"
	.text
	.globl	embImage_read
	.type	embImage_read, @function
embImage_read:
.LFB126:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movq	-16(%rbp), %rdx
	movl	%eax, %esi
	leaq	.LC95(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE126:
	.size	embImage_read, .-embImage_read
	.globl	embImage_write
	.type	embImage_write, @function
embImage_write:
.LFB127:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	movq	-16(%rbp), %rdx
	movl	%eax, %esi
	leaq	.LC95(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE127:
	.size	embImage_write, .-embImage_write
	.globl	embImage_free
	.type	embImage_free, @function
embImage_free:
.LFB128:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, %rdi
	call	safe_free
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE128:
	.size	embImage_free, .-embImage_free
	.section	.rodata
	.align 8
.LC96:
	.string	"ERROR: emb-pattern.c emb_pattern_create(), "
	.align 8
.LC97:
	.string	"unable to allocate memory for p"
	.text
	.globl	emb_pattern_create
	.type	emb_pattern_create, @function
emb_pattern_create:
.LFB129:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$11136, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L606
	leaq	.LC96(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC97(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	jmp	.L607
.L606:
	movq	-8(%rbp), %rax
	movl	$6, 4(%rax)
	movq	-8(%rbp), %rax
	pxor	%xmm0, %xmm0
	movss	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	pxor	%xmm0, %xmm0
	movss	%xmm0, 12(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 1168(%rax)
	movl	$15, %edi
	call	emb_array_create
	movq	-8(%rbp), %rdx
	movq	%rax, 32(%rdx)
	movl	$19, %edi
	call	emb_array_create
	movq	-8(%rbp), %rdx
	movq	%rax, 24(%rdx)
	movq	-8(%rbp), %rax
	pxor	%xmm0, %xmm0
	movss	%xmm0, 20(%rax)
	movq	-8(%rbp), %rax
	pxor	%xmm0, %xmm0
	movss	%xmm0, 16(%rax)
	movl	$7, %edi
	call	emb_array_create
	movq	-8(%rbp), %rdx
	movq	%rax, 40(%rdx)
	movq	-8(%rbp), %rax
.L607:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE129:
	.size	emb_pattern_create, .-emb_pattern_create
	.section	.rodata
	.align 8
.LC98:
	.string	"ERROR: emb-pattern.c emb_pattern_hideStitchesOverLength(), "
.LC99:
	.string	"p argument is null"
	.text
	.globl	emb_pattern_hideStitchesOverLength
	.type	emb_pattern_hideStitchesOverLength, @function
emb_pattern_hideStitchesOverLength:
.LFB130:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L609
	leaq	.LC98(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC99(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L608
.L609:
	movl	$0, -4(%rbp)
	jmp	.L611
.L615:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	4(%rax), %xmm0
	movss	-12(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	.LC100(%rip), %xmm1
	andps	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-28(%rbp), %xmm1
	comisd	%xmm1, %xmm0
	ja	.L612
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	8(%rax), %xmm0
	movss	-8(%rbp), %xmm1
	subss	%xmm1, %xmm0
	movss	.LC100(%rip), %xmm1
	andps	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdl	-28(%rbp), %xmm1
	comisd	%xmm1, %xmm0
	jbe	.L613
.L612:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movl	(%rax), %edx
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$4, %rcx
	addq	%rcx, %rax
	orl	$2, %edx
	movl	%edx, (%rax)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	leaq	(%rax,%rdx), %rcx
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rax, %rdx
	movl	(%rcx), %eax
	movl	%eax, (%rdx)
.L613:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	4(%rax), %xmm0
	movss	%xmm0, -12(%rbp)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	8(%rax), %xmm0
	movss	%xmm0, -8(%rbp)
	addl	$1, -4(%rbp)
.L611:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L615
.L608:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE130:
	.size	emb_pattern_hideStitchesOverLength, .-emb_pattern_hideStitchesOverLength
	.globl	emb_pattern_addThread
	.type	emb_pattern_addThread, @function
emb_pattern_addThread:
.LFB131:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %edx
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movl	28(%rax), %eax
	cmpl	%eax, %edx
	jl	.L617
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, %rdi
	call	emb_array_resize
	testl	%eax, %eax
	jne	.L617
	movl	$0, %eax
	jmp	.L618
.L617:
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	leaq	16(%rbp), %rdx
	movl	$403, %ecx
	movq	(%rdx), %rsi
	movq	%rsi, (%rax)
	movl	%ecx, %esi
	addq	%rax, %rsi
	leaq	8(%rsi), %rdi
	movl	%ecx, %esi
	addq	%rdx, %rsi
	addq	$8, %rsi
	movq	-16(%rsi), %rsi
	movq	%rsi, -16(%rdi)
	leaq	8(%rax), %rdi
	andq	$-8, %rdi
	subq	%rdi, %rax
	subq	%rax, %rdx
	addl	%eax, %ecx
	andl	$-8, %ecx
	movl	%ecx, %eax
	shrl	$3, %eax
	movl	%eax, %eax
	movq	%rdx, %rsi
	movq	%rax, %rcx
	rep movsq
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %edx
	addl	$1, %edx
	movl	%edx, 24(%rax)
	movl	$1, %eax
.L618:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE131:
	.size	emb_pattern_addThread, .-emb_pattern_addThread
	.section	.rodata
	.align 8
.LC101:
	.string	"ERROR: emb-pattern.c emb_pattern_fixColorCount(), "
	.text
	.globl	emb_pattern_fixColorCount
	.type	emb_pattern_fixColorCount, @function
emb_pattern_fixColorCount:
.LFB132:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$432, %rsp
	movq	%rdi, -424(%rbp)
	movl	$0, -4(%rbp)
	cmpq	$0, -424(%rbp)
	jne	.L620
	leaq	.LC101(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC99(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L619
.L620:
	movl	$0, -8(%rbp)
	jmp	.L622
.L623:
	movq	-424(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movl	12(%rax), %eax
	movl	-4(%rbp), %edx
	cmpl	%eax, %edx
	cmovge	%edx, %eax
	movl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L622:
	movq	-424(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L623
	movq	-424(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	je	.L624
	cmpl	$0, -4(%rbp)
	jne	.L625
.L624:
	movq	-424(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	black_thread(%rip), %rax
	movl	$50, %ecx
	movq	%rdx, %rdi
	movq	%rax, %rsi
	rep movsq
	movq	%rsi, %rax
	movq	%rdi, %rdx
	movzwl	(%rax), %ecx
	movw	%cx, (%rdx)
	leaq	2(%rdx), %rdx
	leaq	2(%rax), %rax
	movzbl	(%rax), %ecx
	movb	%cl, (%rdx)
	movq	%r8, %rdi
	call	emb_pattern_addThread
	addq	$416, %rsp
	jmp	.L619
.L625:
	cmpl	$0, -4(%rbp)
	jle	.L619
	jmp	.L626
.L627:
	leaq	-416(%rbp), %rax
	movq	%rax, %rdi
	call	emb_get_random_thread
	movq	-424(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-416(%rbp), %rax
	movl	$50, %ecx
	movq	%rdx, %rdi
	movq	%rax, %rsi
	rep movsq
	movq	%rsi, %rax
	movq	%rdi, %rdx
	movzwl	(%rax), %ecx
	movw	%cx, (%rdx)
	leaq	2(%rdx), %rdx
	leaq	2(%rax), %rax
	movzbl	(%rax), %ecx
	movb	%cl, (%rdx)
	movq	%r8, %rdi
	call	emb_pattern_addThread
	addq	$416, %rsp
.L626:
	movq	-424(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jge	.L627
.L619:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE132:
	.size	emb_pattern_fixColorCount, .-emb_pattern_fixColorCount
	.section	.rodata
	.align 8
.LC102:
	.string	"ERROR: emb-pattern.c emb_pattern_copystitch_listToPolylines(), "
	.text
	.globl	emb_pattern_copystitch_listToPolylines
	.type	emb_pattern_copystitch_listToPolylines, @function
emb_pattern_copystitch_listToPolylines:
.LFB133:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movq	%rdi, -120(%rbp)
	cmpq	$0, -120(%rbp)
	jne	.L629
	leaq	.LC102(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC99(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L628
.L629:
	movl	$7, -20(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L631
.L639:
	movq	$0, -16(%rbp)
	jmp	.L632
.L637:
	movq	-120(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movl	-80(%rbp), %eax
	andl	-20(%rbp), %eax
	testl	%eax, %eax
	jne	.L640
	movl	-80(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L635
	cmpq	$0, -16(%rbp)
	jne	.L636
	movl	$10, %edi
	call	emb_array_create
	movq	%rax, -16(%rbp)
	movq	-120(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-68(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -51(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -49(%rbp)
.L636:
	movss	-76(%rbp), %xmm0
	movss	%xmm0, -48(%rbp)
	movss	-72(%rbp), %xmm0
	movss	%xmm0, -44(%rbp)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rcx, %xmm0
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_array_addPoint
.L635:
	addl	$1, -4(%rbp)
.L632:
	movq	-120(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L637
	jmp	.L634
.L640:
	nop
.L634:
	cmpq	$0, -16(%rbp)
	je	.L638
	movq	-16(%rbp), %rax
	movq	%rax, -112(%rbp)
	movzwl	-51(%rbp), %eax
	movw	%ax, -92(%rbp)
	movzbl	-49(%rbp), %eax
	movb	%al, -90(%rbp)
	movl	$1, -96(%rbp)
	movq	-120(%rbp), %rax
	movq	40(%rax), %rsi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-96(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	%rsi, %rdi
	call	emb_array_addPolyline
	addq	$32, %rsp
.L638:
	addl	$1, -4(%rbp)
.L631:
	movq	-120(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L639
.L628:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE133:
	.size	emb_pattern_copystitch_listToPolylines, .-emb_pattern_copystitch_listToPolylines
	.section	.rodata
	.align 8
.LC103:
	.string	"ERROR: emb-pattern.c emb_pattern_copyPolylinesTostitch_list(), "
	.text
	.globl	emb_pattern_copyPolylinesTostitch_list
	.type	emb_pattern_copyPolylinesTostitch_list, @function
emb_pattern_copyPolylinesTostitch_list:
.LFB134:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$480, %rsp
	movq	%rdi, -472(%rbp)
	movl	$1, -4(%rbp)
	cmpq	$0, -472(%rbp)
	jne	.L642
	leaq	.LC103(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC99(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L641
.L642:
	movl	$0, -8(%rbp)
	jmp	.L644
.L650:
	movq	-472(%rbp), %rax
	movq	40(%rax), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movl	28(%rax), %eax
	cmpl	$12, %eax
	jne	.L651
	movq	-472(%rbp), %rax
	movq	40(%rax), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rax, %rcx
	movq	(%rcx), %rax
	movq	8(%rcx), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	16(%rcx), %rax
	movq	%rax, -32(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movb	$0, -261(%rbp)
	movzwl	-28(%rbp), %eax
	movw	%ax, -464(%rbp)
	movzbl	-26(%rbp), %eax
	movb	%al, -462(%rbp)
	movb	$0, -461(%rbp)
	movq	-472(%rbp), %r8
	subq	$8, %rsp
	subq	$408, %rsp
	movq	%rsp, %rax
	movq	%rax, %rdx
	leaq	-464(%rbp), %rax
	movl	$50, %ecx
	movq	%rdx, %rdi
	movq	%rax, %rsi
	rep movsq
	movq	%rsi, %rax
	movq	%rdi, %rdx
	movzwl	(%rax), %ecx
	movw	%cx, (%rdx)
	leaq	2(%rdx), %rdx
	leaq	2(%rax), %rax
	movzbl	(%rax), %ecx
	movb	%cl, (%rdx)
	movq	%r8, %rdi
	call	emb_pattern_addThread
	addq	$416, %rsp
	cmpl	$0, -4(%rbp)
	jne	.L647
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movss	4(%rax), %xmm0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %ecx
	movq	-472(%rbp), %rax
	movl	$1, %edx
	movl	$2, %esi
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	movq	-472(%rbp), %rax
	movl	$1, %edx
	movl	$4, %esi
	pxor	%xmm1, %xmm1
	movl	.LC12(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel
.L647:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movss	4(%rax), %xmm0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %ecx
	movq	-472(%rbp), %rax
	movl	$1, %edx
	movl	$1, %esi
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	movl	$1, -12(%rbp)
	jmp	.L648
.L649:
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-12(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, -56(%rbp)
	movss	-52(%rbp), %xmm0
	movl	-56(%rbp), %ecx
	movq	-472(%rbp), %rax
	movl	$1, %edx
	movl	$0, %esi
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
	addl	$1, -12(%rbp)
.L648:
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -12(%rbp)
	jl	.L649
	movl	$0, -4(%rbp)
	jmp	.L646
.L651:
	nop
.L646:
	addl	$1, -8(%rbp)
.L644:
	movq	-472(%rbp), %rax
	movq	40(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L650
	movq	-472(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC12(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel
.L641:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE134:
	.size	emb_pattern_copyPolylinesTostitch_list, .-emb_pattern_copyPolylinesTostitch_list
	.section	.rodata
	.align 8
.LC104:
	.string	"ERROR: emb-pattern.c emb_pattern_movestitch_listToPolylines(), p argument is null"
	.text
	.globl	emb_pattern_movestitch_listToPolylines
	.type	emb_pattern_movestitch_listToPolylines, @function
emb_pattern_movestitch_listToPolylines:
.LFB135:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L653
	leaq	.LC104(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L652
.L653:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_copystitch_listToPolylines
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movl	$0, 24(%rax)
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movl	$0, 24(%rax)
.L652:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE135:
	.size	emb_pattern_movestitch_listToPolylines, .-emb_pattern_movestitch_listToPolylines
	.section	.rodata
	.align 8
.LC105:
	.string	"ERROR: emb-pattern.c emb_pattern_movePolylinesTostitch_list(), p argument is null"
	.text
	.globl	emb_pattern_movePolylinesTostitch_list
	.type	emb_pattern_movePolylinesTostitch_list, @function
emb_pattern_movePolylinesTostitch_list:
.LFB136:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L656
	leaq	.LC105(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L655
.L656:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_copyPolylinesTostitch_list
.L655:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE136:
	.size	emb_pattern_movePolylinesTostitch_list, .-emb_pattern_movePolylinesTostitch_list
	.section	.rodata
	.align 8
.LC106:
	.string	"ERROR: emb-pattern.c emb_pattern_addStitchAbs(), "
	.align 8
.LC107:
	.string	"ERROR: emb-pattern.c emb_pattern_addStitchAbs(), found multiple END stitches"
	.text
	.globl	emb_pattern_addStitchAbs
	.type	emb_pattern_addStitchAbs, @function
emb_pattern_addStitchAbs:
.LFB137:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movss	%xmm0, -44(%rbp)
	movss	%xmm1, -48(%rbp)
	movl	%esi, -52(%rbp)
	movl	%edx, -56(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L659
	leaq	.LC106(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC99(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L658
.L659:
	movl	-52(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L661
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	je	.L668
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cltq
	salq	$4, %rax
	subq	$16, %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L663
	leaq	.LC107(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L658
.L663:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_fixColorCount
.L661:
	movl	-52(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L664
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	je	.L669
	cmpl	$0, -56(%rbp)
	je	.L664
	movq	-40(%rbp), %rax
	movl	1168(%rax), %eax
	leal	1(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, 1168(%rax)
.L664:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	jne	.L666
	movq	-40(%rbp), %rax
	movss	8(%rax), %xmm0
	movss	%xmm0, -28(%rbp)
	movq	-40(%rbp), %rax
	movss	12(%rax), %xmm0
	movss	%xmm0, -24(%rbp)
	movl	$1, -32(%rbp)
	movq	-40(%rbp), %rax
	movl	1168(%rax), %eax
	movl	%eax, -20(%rbp)
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_array_addStitch
.L666:
	movss	-44(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	movss	-48(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
	movl	-52(%rbp), %eax
	movl	%eax, -16(%rbp)
	movq	-40(%rbp), %rax
	movl	1168(%rax), %eax
	movl	%eax, -4(%rbp)
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_array_addStitch
	jmp	.L658
.L668:
	nop
	jmp	.L658
.L669:
	nop
.L658:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE137:
	.size	emb_pattern_addStitchAbs, .-emb_pattern_addStitchAbs
	.section	.rodata
	.align 8
.LC108:
	.string	"ERROR: emb-pattern.c emb_pattern_addStitchRel(), p argument is null"
	.text
	.globl	emb_pattern_addStitchRel
	.type	emb_pattern_addStitchRel, @function
emb_pattern_addStitchRel:
.LFB138:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movss	%xmm0, -44(%rbp)
	movss	%xmm1, -48(%rbp)
	movl	%esi, -52(%rbp)
	movl	%edx, -56(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L671
	leaq	.LC108(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L670
.L671:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	jle	.L673
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cltq
	salq	$4, %rax
	subq	$16, %rax
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movss	-28(%rbp), %xmm0
	movss	-44(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	movss	-24(%rbp), %xmm0
	movss	-48(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	jmp	.L674
.L673:
	movq	-40(%rbp), %rax
	movss	8(%rax), %xmm0
	movss	-44(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	movq	-40(%rbp), %rax
	movss	12(%rax), %xmm0
	movss	-48(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
.L674:
	movl	-56(%rbp), %edx
	movl	-52(%rbp), %esi
	movss	-8(%rbp), %xmm0
	movl	-4(%rbp), %ecx
	movq	-40(%rbp), %rax
	movaps	%xmm0, %xmm1
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchAbs
.L670:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE138:
	.size	emb_pattern_addStitchRel, .-emb_pattern_addStitchRel
	.section	.rodata
	.align 8
.LC109:
	.string	"ERROR: emb-pattern.c emb_pattern_changeColor(), p argument is null"
	.text
	.globl	emb_pattern_changeColor
	.type	emb_pattern_changeColor, @function
emb_pattern_changeColor:
.LFB139:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L676
	leaq	.LC109(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L675
.L676:
	movq	-8(%rbp), %rax
	movl	-12(%rbp), %edx
	movl	%edx, 1168(%rax)
.L675:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE139:
	.size	emb_pattern_changeColor, .-emb_pattern_changeColor
	.section	.rodata
	.align 8
.LC110:
	.string	"ERROR: emb-pattern.c emb_pattern_scale(), p argument is null"
	.text
	.globl	emb_pattern_scale
	.type	emb_pattern_scale, @function
emb_pattern_scale:
.LFB140:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movss	%xmm0, -28(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L679
	leaq	.LC110(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L678
.L679:
	movl	$0, -4(%rbp)
	jmp	.L681
.L682:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	4(%rax), %xmm0
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	mulss	-28(%rbp), %xmm0
	movss	%xmm0, 4(%rax)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	8(%rax), %xmm0
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	mulss	-28(%rbp), %xmm0
	movss	%xmm0, 8(%rax)
	addl	$1, -4(%rbp)
.L681:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L682
.L678:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE140:
	.size	emb_pattern_scale, .-emb_pattern_scale
	.section	.rodata
	.align 8
.LC111:
	.string	"ERROR: emb-pattern.c emb_pattern_bounds(), "
	.text
	.globl	emb_pattern_bounds
	.type	emb_pattern_bounds, @function
emb_pattern_bounds:
.LFB141:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$280, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -280(%rbp)
	movq	%rsi, -288(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -80(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -76(%rbp)
	movss	.LC81(%rip), %xmm0
	movss	%xmm0, -72(%rbp)
	movss	.LC81(%rip), %xmm0
	movss	%xmm0, -68(%rbp)
	cmpq	$0, -288(%rbp)
	jne	.L684
	leaq	.LC111(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC99(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-280(%rbp), %rcx
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rcx)
	jmp	.L804
.L684:
	movq	-288(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	jne	.L686
	movq	-288(%rbp), %rax
	movq	40(%rax), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	jne	.L686
	movq	-280(%rbp), %rcx
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rcx)
	jmp	.L804
.L686:
	movss	.LC112(%rip), %xmm0
	movss	%xmm0, -80(%rbp)
	movss	.LC112(%rip), %xmm0
	movss	%xmm0, -76(%rbp)
	movsd	.LC113(%rip), %xmm0
	movsd	%xmm0, -32(%rbp)
	movsd	.LC113(%rip), %xmm0
	movsd	%xmm0, -40(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L687
.L701:
	movq	-288(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	movl	-96(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	jne	.L688
	movss	-80(%rbp), %xmm0
	movss	-92(%rbp), %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L837
	movss	-80(%rbp), %xmm0
	jmp	.L691
.L837:
	movss	-92(%rbp), %xmm0
.L691:
	movss	%xmm0, -80(%rbp)
	movss	-76(%rbp), %xmm0
	movss	-88(%rbp), %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L838
	movss	-76(%rbp), %xmm0
	jmp	.L694
.L838:
	movss	-88(%rbp), %xmm0
.L694:
	movss	%xmm0, -76(%rbp)
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	comisd	-32(%rbp), %xmm0
	jbe	.L839
	movsd	-32(%rbp), %xmm0
	jmp	.L697
.L839:
	movss	-92(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
.L697:
	movsd	%xmm0, -32(%rbp)
	movss	-88(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	comisd	-40(%rbp), %xmm0
	jbe	.L840
	movsd	-40(%rbp), %xmm0
	jmp	.L700
.L840:
	movss	-88(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
.L700:
	movsd	%xmm0, -40(%rbp)
.L688:
	addl	$1, -20(%rbp)
.L687:
	movq	-288(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L701
	movl	$0, -20(%rbp)
	jmp	.L702
.L803:
	movq	-288(%rbp), %rax
	movq	40(%rax), %rax
	movq	(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rcx
	movq	8(%rax), %rbx
	movq	%rcx, -272(%rbp)
	movq	%rbx, -264(%rbp)
	movq	16(%rax), %rcx
	movq	24(%rax), %rbx
	movq	%rcx, -256(%rbp)
	movq	%rbx, -248(%rbp)
	movq	32(%rax), %rax
	movq	%rax, -240(%rbp)
	movl	-244(%rbp), %eax
	cmpl	$14, %eax
	ja	.L869
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L705(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L705(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L705:
	.long	.L869-.L705
	.long	.L713-.L705
	.long	.L712-.L705
	.long	.L869-.L705
	.long	.L869-.L705
	.long	.L711-.L705
	.long	.L869-.L705
	.long	.L710-.L705
	.long	.L869-.L705
	.long	.L869-.L705
	.long	.L709-.L705
	.long	.L708-.L705
	.long	.L707-.L705
	.long	.L706-.L705
	.long	.L869-.L705
	.text
.L713:
	movq	-272(%rbp), %rax
	movq	-264(%rbp), %rdx
	movq	%rax, -128(%rbp)
	movq	%rdx, -120(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -112(%rbp)
	movss	-80(%rbp), %xmm1
	movss	-128(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L841
	movss	-80(%rbp), %xmm0
	jmp	.L716
.L841:
	movss	-128(%rbp), %xmm0
.L716:
	movss	%xmm0, -80(%rbp)
	movss	-76(%rbp), %xmm1
	movss	-124(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L842
	movss	-76(%rbp), %xmm0
	jmp	.L719
.L842:
	movss	-124(%rbp), %xmm0
.L719:
	movss	%xmm0, -76(%rbp)
	movss	-128(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L843
	movsd	-32(%rbp), %xmm0
	jmp	.L722
.L843:
	movss	-128(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
.L722:
	movsd	%xmm0, -32(%rbp)
	movss	-124(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-40(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L844
	movsd	-40(%rbp), %xmm0
	jmp	.L725
.L844:
	movss	-124(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
.L725:
	movsd	%xmm0, -40(%rbp)
	jmp	.L726
.L712:
	movq	-272(%rbp), %rax
	movq	%rax, -140(%rbp)
	movl	-264(%rbp), %eax
	movl	%eax, -132(%rbp)
	movss	-80(%rbp), %xmm1
	movss	-140(%rbp), %xmm0
	movss	-132(%rbp), %xmm2
	subss	%xmm2, %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L845
	movss	-80(%rbp), %xmm0
	jmp	.L729
.L845:
	movss	-140(%rbp), %xmm0
	movss	-132(%rbp), %xmm1
	subss	%xmm1, %xmm0
.L729:
	movss	%xmm0, -80(%rbp)
	movss	-76(%rbp), %xmm1
	movss	-136(%rbp), %xmm0
	movss	-132(%rbp), %xmm2
	subss	%xmm2, %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L846
	movss	-76(%rbp), %xmm0
	jmp	.L732
.L846:
	movss	-136(%rbp), %xmm0
	movss	-132(%rbp), %xmm1
	subss	%xmm1, %xmm0
.L732:
	movss	%xmm0, -76(%rbp)
	movss	-140(%rbp), %xmm1
	movss	-132(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L847
	movsd	-32(%rbp), %xmm0
	jmp	.L735
.L847:
	movss	-140(%rbp), %xmm1
	movss	-132(%rbp), %xmm0
	addss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
.L735:
	movsd	%xmm0, -32(%rbp)
	movss	-136(%rbp), %xmm1
	movss	-132(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-40(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L848
	movsd	-40(%rbp), %xmm0
	jmp	.L738
.L848:
	movss	-136(%rbp), %xmm1
	movss	-132(%rbp), %xmm0
	addss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
.L738:
	movsd	%xmm0, -40(%rbp)
	jmp	.L726
.L711:
	movq	-272(%rbp), %rax
	movq	-264(%rbp), %rdx
	movq	%rax, -160(%rbp)
	movq	%rdx, -152(%rbp)
	movl	-256(%rbp), %eax
	movl	%eax, -144(%rbp)
	movss	-80(%rbp), %xmm1
	movss	-160(%rbp), %xmm0
	movss	-152(%rbp), %xmm2
	subss	%xmm2, %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L849
	movss	-80(%rbp), %xmm0
	jmp	.L741
.L849:
	movss	-160(%rbp), %xmm0
	movss	-152(%rbp), %xmm1
	subss	%xmm1, %xmm0
.L741:
	movss	%xmm0, -80(%rbp)
	movss	-76(%rbp), %xmm1
	movss	-156(%rbp), %xmm0
	movss	-148(%rbp), %xmm2
	subss	%xmm2, %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L850
	movss	-76(%rbp), %xmm0
	jmp	.L744
.L850:
	movss	-156(%rbp), %xmm0
	movss	-148(%rbp), %xmm1
	subss	%xmm1, %xmm0
.L744:
	movss	%xmm0, -76(%rbp)
	movss	-160(%rbp), %xmm1
	movss	-152(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L851
	movsd	-32(%rbp), %xmm0
	jmp	.L747
.L851:
	movss	-160(%rbp), %xmm1
	movss	-152(%rbp), %xmm0
	addss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
.L747:
	movsd	%xmm0, -32(%rbp)
	movss	-156(%rbp), %xmm1
	movss	-148(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-40(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L852
	movsd	-40(%rbp), %xmm0
	jmp	.L750
.L852:
	movss	-156(%rbp), %xmm1
	movss	-148(%rbp), %xmm0
	addss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
.L750:
	movsd	%xmm0, -40(%rbp)
	jmp	.L726
.L710:
	movq	-272(%rbp), %rax
	movq	-264(%rbp), %rdx
	movq	%rax, -192(%rbp)
	movq	%rdx, -184(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -176(%rbp)
	movss	-80(%rbp), %xmm1
	movss	-192(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L853
	movss	-80(%rbp), %xmm0
	jmp	.L753
.L853:
	movss	-192(%rbp), %xmm0
.L753:
	movss	%xmm0, -80(%rbp)
	movss	-80(%rbp), %xmm1
	movss	-184(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L854
	movss	-80(%rbp), %xmm0
	jmp	.L756
.L854:
	movss	-184(%rbp), %xmm0
.L756:
	movss	%xmm0, -80(%rbp)
	movss	-76(%rbp), %xmm1
	movss	-188(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L855
	movss	-76(%rbp), %xmm0
	jmp	.L759
.L855:
	movss	-188(%rbp), %xmm0
.L759:
	movss	%xmm0, -76(%rbp)
	movss	-76(%rbp), %xmm1
	movss	-180(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L856
	movss	-76(%rbp), %xmm0
	jmp	.L762
.L856:
	movss	-180(%rbp), %xmm0
.L762:
	movss	%xmm0, -76(%rbp)
	movss	-192(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L857
	movsd	-32(%rbp), %xmm0
	jmp	.L765
.L857:
	movss	-192(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
.L765:
	movsd	%xmm0, -32(%rbp)
	movss	-184(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L858
	movsd	-32(%rbp), %xmm0
	jmp	.L768
.L858:
	movss	-184(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
.L768:
	movsd	%xmm0, -32(%rbp)
	movss	-188(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-40(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L859
	movsd	-40(%rbp), %xmm0
	jmp	.L771
.L859:
	movss	-188(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
.L771:
	movsd	%xmm0, -40(%rbp)
	movss	-180(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-40(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L860
	movsd	-40(%rbp), %xmm0
	jmp	.L774
.L860:
	movss	-180(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
.L774:
	movsd	%xmm0, -40(%rbp)
	jmp	.L726
.L709:
	movq	-272(%rbp), %rax
	movq	%rax, -200(%rbp)
	movss	-80(%rbp), %xmm1
	movss	-200(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L861
	movss	-80(%rbp), %xmm0
	jmp	.L777
.L861:
	movss	-200(%rbp), %xmm0
.L777:
	movss	%xmm0, -80(%rbp)
	movss	-76(%rbp), %xmm1
	movss	-196(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L862
	movss	-76(%rbp), %xmm0
	jmp	.L780
.L862:
	movss	-196(%rbp), %xmm0
.L780:
	movss	%xmm0, -76(%rbp)
	movss	-200(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L863
	movsd	-32(%rbp), %xmm0
	jmp	.L783
.L863:
	movss	-200(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
.L783:
	movsd	%xmm0, -32(%rbp)
	movss	-196(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-40(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L864
	movsd	-40(%rbp), %xmm0
	jmp	.L786
.L864:
	movss	-196(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
.L786:
	movsd	%xmm0, -40(%rbp)
	jmp	.L726
.L708:
	movq	-272(%rbp), %rax
	movq	%rax, -56(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L787
.L788:
	addl	$1, -24(%rbp)
.L787:
	movq	-56(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -24(%rbp)
	jl	.L788
	jmp	.L726
.L707:
	movq	-272(%rbp), %rax
	movq	%rax, -48(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L789
.L790:
	addl	$1, -24(%rbp)
.L789:
	movq	-48(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -24(%rbp)
	jl	.L790
	jmp	.L726
.L706:
	movq	-272(%rbp), %rax
	movq	-264(%rbp), %rdx
	movq	%rax, -224(%rbp)
	movq	%rdx, -216(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, -208(%rbp)
	movss	-80(%rbp), %xmm1
	movss	-224(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L865
	movss	-80(%rbp), %xmm0
	jmp	.L793
.L865:
	movss	-224(%rbp), %xmm0
.L793:
	movss	%xmm0, -80(%rbp)
	movss	-76(%rbp), %xmm1
	movss	-220(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L866
	movss	-76(%rbp), %xmm0
	jmp	.L796
.L866:
	movss	-220(%rbp), %xmm0
.L796:
	movss	%xmm0, -76(%rbp)
	movss	-80(%rbp), %xmm1
	movss	-216(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L867
	movsd	-32(%rbp), %xmm0
	jmp	.L799
.L867:
	movss	-80(%rbp), %xmm1
	movss	-216(%rbp), %xmm0
	addss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
.L799:
	movsd	%xmm0, -32(%rbp)
	movss	-76(%rbp), %xmm1
	movss	-212(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-40(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L868
	movsd	-40(%rbp), %xmm0
	jmp	.L802
.L868:
	movss	-76(%rbp), %xmm1
	movss	-212(%rbp), %xmm0
	addss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
.L802:
	movsd	%xmm0, -40(%rbp)
	jmp	.L726
.L869:
	nop
.L726:
	addl	$1, -20(%rbp)
.L702:
	movq	-288(%rbp), %rax
	movq	40(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L803
	movss	-80(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm0
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -72(%rbp)
	movss	-76(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movsd	-40(%rbp), %xmm0
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -68(%rbp)
	movq	-280(%rbp), %rcx
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-64(%rbp), %rax
	movq	%rax, 16(%rcx)
.L804:
	movq	-280(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE141:
	.size	emb_pattern_bounds, .-emb_pattern_bounds
	.section	.rodata
	.align 8
.LC114:
	.string	"ERROR: emb-pattern.c emb_pattern_flipHorizontal(), "
	.text
	.globl	emb_pattern_flipHorizontal
	.type	emb_pattern_flipHorizontal, @function
emb_pattern_flipHorizontal:
.LFB142:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L871
	leaq	.LC114(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC99(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L870
.L871:
	movq	-8(%rbp), %rax
	movl	$0, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	emb_pattern_flip
.L870:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE142:
	.size	emb_pattern_flipHorizontal, .-emb_pattern_flipHorizontal
	.section	.rodata
	.align 8
.LC115:
	.string	"ERROR: emb-pattern.c emb_pattern_flipVertical(), "
	.text
	.globl	emb_pattern_flipVertical
	.type	emb_pattern_flipVertical, @function
emb_pattern_flipVertical:
.LFB143:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L874
	leaq	.LC115(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC99(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L873
.L874:
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	emb_pattern_flip
.L873:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE143:
	.size	emb_pattern_flipVertical, .-emb_pattern_flipVertical
	.section	.rodata
	.align 8
.LC116:
	.string	"ERROR: emb-pattern.c emb_pattern_flip(), p argument is null"
	.text
	.globl	emb_pattern_flip
	.type	emb_pattern_flip, @function
emb_pattern_flip:
.LFB144:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movl	%edx, -64(%rbp)
	cmpq	$0, -56(%rbp)
	jne	.L877
	leaq	.LC116(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L876
.L877:
	movl	$0, -4(%rbp)
	jmp	.L879
.L882:
	cmpl	$0, -60(%rbp)
	je	.L880
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, 4(%rax)
.L880:
	cmpl	$0, -64(%rbp)
	je	.L881
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	8(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, 8(%rax)
.L881:
	addl	$1, -4(%rbp)
.L879:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L882
	movl	$0, -4(%rbp)
	jmp	.L883
.L921:
	movq	-56(%rbp), %rax
	movq	40(%rax), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	28(%rax), %eax
	cmpl	$14, %eax
	ja	.L922
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L886(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L886(%rip), %rdx
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L886:
	.long	.L922-.L886
	.long	.L895-.L886
	.long	.L894-.L886
	.long	.L922-.L886
	.long	.L922-.L886
	.long	.L893-.L886
	.long	.L922-.L886
	.long	.L892-.L886
	.long	.L922-.L886
	.long	.L891-.L886
	.long	.L890-.L886
	.long	.L889-.L886
	.long	.L888-.L886
	.long	.L887-.L886
	.long	.L922-.L886
	.text
.L895:
	cmpl	$0, -60(%rbp)
	je	.L896
	movq	-16(%rbp), %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, (%rax)
	movq	-16(%rbp), %rax
	movss	8(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 8(%rax)
	movq	-16(%rbp), %rax
	movss	16(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 16(%rax)
.L896:
	cmpl	$0, -64(%rbp)
	je	.L923
	movq	-16(%rbp), %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 4(%rax)
	movq	-16(%rbp), %rax
	movss	12(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 12(%rax)
	movq	-16(%rbp), %rax
	movss	20(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 20(%rax)
	jmp	.L923
.L892:
	cmpl	$0, -60(%rbp)
	je	.L899
	movq	-16(%rbp), %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, (%rax)
	movq	-16(%rbp), %rax
	movss	8(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 8(%rax)
.L899:
	cmpl	$0, -64(%rbp)
	je	.L924
	movq	-16(%rbp), %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 4(%rax)
	movq	-16(%rbp), %rax
	movss	12(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 12(%rax)
	jmp	.L924
.L894:
	cmpl	$0, -60(%rbp)
	je	.L901
	movq	-16(%rbp), %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, (%rax)
.L901:
	cmpl	$0, -64(%rbp)
	je	.L925
	movq	-16(%rbp), %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 4(%rax)
	jmp	.L925
.L893:
	cmpl	$0, -60(%rbp)
	je	.L903
	movq	-16(%rbp), %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, (%rax)
.L903:
	cmpl	$0, -64(%rbp)
	je	.L926
	movq	-16(%rbp), %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 4(%rax)
	jmp	.L926
.L891:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -40(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L905
.L908:
	cmpl	$0, -60(%rbp)
	je	.L906
	movq	-40(%rbp), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-40(%rbp), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, (%rax)
.L906:
	cmpl	$0, -64(%rbp)
	je	.L907
	movq	-40(%rbp), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-40(%rbp), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, 4(%rax)
.L907:
	addl	$1, -8(%rbp)
.L905:
	movq	-40(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L908
	jmp	.L898
.L890:
	cmpl	$0, -60(%rbp)
	je	.L909
	movq	-16(%rbp), %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, (%rax)
.L909:
	cmpl	$0, -64(%rbp)
	je	.L927
	movq	-16(%rbp), %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 4(%rax)
	jmp	.L927
.L889:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L911
.L914:
	cmpl	$0, -60(%rbp)
	je	.L912
	movq	-32(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-32(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, (%rax)
.L912:
	cmpl	$0, -64(%rbp)
	je	.L913
	movq	-32(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-32(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, 4(%rax)
.L913:
	addl	$1, -8(%rbp)
.L911:
	movq	-32(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L914
	jmp	.L898
.L888:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L915
.L918:
	cmpl	$0, -60(%rbp)
	je	.L916
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, (%rax)
.L916:
	cmpl	$0, -64(%rbp)
	je	.L917
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movss	%xmm0, 4(%rax)
.L917:
	addl	$1, -8(%rbp)
.L915:
	movq	-24(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L918
	jmp	.L898
.L887:
	cmpl	$0, -60(%rbp)
	je	.L919
	movq	-16(%rbp), %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, (%rax)
	movq	-16(%rbp), %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 4(%rax)
.L919:
	cmpl	$0, -64(%rbp)
	je	.L928
	movq	-16(%rbp), %rax
	movss	8(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 8(%rax)
	movq	-16(%rbp), %rax
	movss	12(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	.LC13(%rip), %xmm1
	xorps	%xmm1, %xmm0
	movq	-16(%rbp), %rax
	movss	%xmm0, 12(%rax)
	jmp	.L928
.L922:
	nop
	jmp	.L898
.L923:
	nop
	jmp	.L898
.L924:
	nop
	jmp	.L898
.L925:
	nop
	jmp	.L898
.L926:
	nop
	jmp	.L898
.L927:
	nop
	jmp	.L898
.L928:
	nop
.L898:
	addl	$1, -4(%rbp)
.L883:
	movq	-56(%rbp), %rax
	movq	40(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L921
.L876:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE144:
	.size	emb_pattern_flip, .-emb_pattern_flip
	.section	.rodata
	.align 8
.LC117:
	.string	"ERROR: emb-pattern.c emb_pattern_combineJumpStitches(), "
	.text
	.globl	emb_pattern_combineJumpStitches
	.type	emb_pattern_combineJumpStitches, @function
emb_pattern_combineJumpStitches:
.LFB145:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movl	$0, -4(%rbp)
	cmpq	$0, -56(%rbp)
	jne	.L930
	leaq	.LC117(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC99(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L929
.L930:
	movl	$15, %edi
	call	emb_array_create
	movq	%rax, -16(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L932
.L938:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	-48(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L933
	cmpl	$0, -4(%rbp)
	jne	.L934
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	jmp	.L935
.L934:
	movss	-28(%rbp), %xmm1
	movss	-44(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -28(%rbp)
	movss	-24(%rbp), %xmm1
	movss	-40(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -24(%rbp)
.L935:
	addl	$1, -4(%rbp)
	jmp	.L936
.L933:
	cmpl	$0, -4(%rbp)
	jle	.L937
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_array_addStitch
.L937:
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_array_addStitch
.L936:
	addl	$1, -8(%rbp)
.L932:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L938
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdi
	call	emb_array_free
	movq	-56(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 32(%rax)
.L929:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE145:
	.size	emb_pattern_combineJumpStitches, .-emb_pattern_combineJumpStitches
	.section	.rodata
	.align 8
.LC118:
	.string	"ERROR: emb-pattern.c emb_pattern_correctForMaxStitchLength(), "
	.text
	.globl	emb_pattern_correctForMaxStitchLength
	.type	emb_pattern_correctForMaxStitchLength, @function
emb_pattern_correctForMaxStitchLength:
.LFB146:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -104(%rbp)
	movss	%xmm0, -108(%rbp)
	movss	%xmm1, -112(%rbp)
	cmpq	$0, -104(%rbp)
	jne	.L940
	leaq	.LC118(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC99(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L939
.L940:
	movq	-104(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	$1, %eax
	jle	.L942
	movl	$15, %edi
	call	emb_array_create
	movq	%rax, -24(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L943
.L954:
	movq	-104(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)
	movq	%rdx, -72(%rbp)
	movss	-76(%rbp), %xmm0
	movss	%xmm0, -28(%rbp)
	movss	-72(%rbp), %xmm0
	movss	%xmm0, -32(%rbp)
	movq	-104(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	subq	$16, %rdx
	addq	%rdx, %rax
	movss	4(%rax), %xmm0
	subss	-28(%rbp), %xmm0
	movss	%xmm0, -36(%rbp)
	movq	-104(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	subq	$16, %rdx
	addq	%rdx, %rax
	movss	8(%rax), %xmm0
	subss	-32(%rbp), %xmm0
	movss	%xmm0, -40(%rbp)
	movss	-36(%rbp), %xmm0
	movss	.LC100(%rip), %xmm1
	andps	%xmm1, %xmm0
	comiss	-108(%rbp), %xmm0
	ja	.L944
	movss	-40(%rbp), %xmm0
	movss	.LC100(%rip), %xmm1
	andps	%xmm1, %xmm0
	comiss	-108(%rbp), %xmm0
	jbe	.L945
.L944:
	movss	-36(%rbp), %xmm0
	movss	.LC100(%rip), %xmm1
	andps	%xmm1, %xmm0
	movss	-40(%rbp), %xmm1
	movss	.LC100(%rip), %xmm2
	andps	%xmm2, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L956
	movss	-36(%rbp), %xmm0
	movss	.LC100(%rip), %xmm1
	andps	%xmm1, %xmm0
	jmp	.L949
.L956:
	movss	-40(%rbp), %xmm0
	movss	.LC100(%rip), %xmm1
	andps	%xmm1, %xmm0
.L949:
	movss	%xmm0, -44(%rbp)
	movl	-80(%rbp), %eax
	andl	$3, %eax
	testl	%eax, %eax
	je	.L950
	movss	-112(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	jmp	.L951
.L950:
	movss	-108(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
.L951:
	movss	-44(%rbp), %xmm0
	divss	-12(%rbp), %xmm0
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm0, %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	call	ceil@PLT
	cvttsd2sil	%xmm0, %eax
	movl	%eax, -48(%rbp)
	cmpl	$1, -48(%rbp)
	jle	.L945
	pxor	%xmm1, %xmm1
	cvtsi2ssl	-48(%rbp), %xmm1
	movss	-36(%rbp), %xmm0
	divss	%xmm1, %xmm0
	movss	%xmm0, -52(%rbp)
	pxor	%xmm1, %xmm1
	cvtsi2ssl	-48(%rbp), %xmm1
	movss	-40(%rbp), %xmm0
	divss	%xmm1, %xmm0
	movss	%xmm0, -56(%rbp)
	movl	$1, -8(%rbp)
	jmp	.L952
.L953:
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, -96(%rbp)
	movq	%rdx, -88(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-8(%rbp), %xmm0
	mulss	-52(%rbp), %xmm0
	addss	-28(%rbp), %xmm0
	movss	%xmm0, -92(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-8(%rbp), %xmm0
	mulss	-56(%rbp), %xmm0
	addss	-32(%rbp), %xmm0
	movss	%xmm0, -88(%rbp)
	movq	-96(%rbp), %rcx
	movq	-88(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_array_addStitch
	addl	$1, -8(%rbp)
.L952:
	movl	-8(%rbp), %eax
	cmpl	-48(%rbp), %eax
	jl	.L953
.L945:
	movq	-80(%rbp), %rcx
	movq	-72(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_array_addStitch
	addl	$1, -4(%rbp)
.L943:
	movq	-104(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L954
	movq	-104(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdi
	call	emb_array_free
	movq	-104(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 32(%rax)
.L942:
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_end
.L939:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE146:
	.size	emb_pattern_correctForMaxStitchLength, .-emb_pattern_correctForMaxStitchLength
	.section	.rodata
	.align 8
.LC119:
	.string	"ERROR: emb-pattern.c emb_pattern_center(), p argument is null"
	.text
	.globl	emb_pattern_center
	.type	emb_pattern_center, @function
emb_pattern_center:
.LFB147:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	cmpq	$0, -56(%rbp)
	jne	.L958
	leaq	.LC119(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L957
.L958:
	leaq	-48(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds
	movss	-48(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-40(%rbp), %xmm1
	cvtss2sd	%xmm1, %xmm1
	movsd	.LC120(%rip), %xmm2
	divsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movl	%eax, -8(%rbp)
	movss	-44(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movss	-36(%rbp), %xmm1
	cvtss2sd	%xmm1, %xmm1
	movsd	.LC120(%rip), %xmm2
	divsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	cvttsd2sil	%xmm0, %eax
	movl	%eax, -12(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L960
.L961:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	4(%rax), %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2ssl	-8(%rbp), %xmm1
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	subss	%xmm1, %xmm0
	movss	%xmm0, 4(%rax)
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movss	8(%rax), %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2ssl	-12(%rbp), %xmm1
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	subss	%xmm1, %xmm0
	movss	%xmm0, 8(%rax)
	addl	$1, -4(%rbp)
.L960:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L961
.L957:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE147:
	.size	emb_pattern_center, .-emb_pattern_center
	.section	.rodata
	.align 8
.LC121:
	.string	"ERROR: emb-pattern.c emb_pattern_loadExternalColorFile(), p argument is null"
	.align 8
.LC122:
	.string	"ERROR: emb-pattern.c emb_pattern_loadExternalColorFile(), fileName argument is null"
	.text
	.globl	emb_pattern_loadExternalColorFile
	.type	emb_pattern_loadExternalColorFile, @function
emb_pattern_loadExternalColorFile:
.LFB148:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$248, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -248(%rbp)
	movq	%rsi, -256(%rbp)
	cmpq	$0, -248(%rbp)
	jne	.L963
	leaq	.LC121(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L962
.L963:
	cmpq	$0, -256(%rbp)
	jne	.L965
	leaq	.LC122(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L962
.L965:
	movq	-256(%rbp), %rdx
	leaq	-240(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	movq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	emb_identify_format@PLT
	movl	%eax, -24(%rbp)
	movq	-256(%rbp), %rax
	movq	%rax, %rdi
	call	string_len
	movl	%eax, %ebx
	movl	-24(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	formatTable(%rip), %rdx
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	string_len
	subl	%eax, %ebx
	movl	%ebx, %edx
	movl	%edx, -28(%rbp)
	movl	-28(%rbp), %eax
	cltq
	movb	$0, -240(%rbp,%rax)
	leaq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	leaq	-240(%rbp), %rax
	addq	%rdx, %rax
	movl	$1919182126, (%rax)
	movb	$0, 4(%rax)
	leaq	-240(%rbp), %rcx
	movq	-248(%rbp), %rax
	movl	$15, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_read@PLT
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	jne	.L966
	movl	-28(%rbp), %eax
	cltq
	movb	$0, -240(%rbp,%rax)
	leaq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	leaq	-240(%rbp), %rax
	addq	%rdx, %rax
	movl	$1650946606, (%rax)
	movb	$0, 4(%rax)
	leaq	-240(%rbp), %rcx
	movq	-248(%rbp), %rax
	movl	$44, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_read@PLT
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
.L966:
	cmpl	$0, -20(%rbp)
	jne	.L967
	movl	-28(%rbp), %eax
	cltq
	movb	$0, -240(%rbp,%rax)
	leaq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	leaq	-240(%rbp), %rax
	addq	%rdx, %rax
	movl	$1819239214, (%rax)
	movb	$0, 4(%rax)
	leaq	-240(%rbp), %rcx
	movq	-248(%rbp), %rax
	movl	$6, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_read@PLT
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
.L967:
	cmpl	$0, -20(%rbp)
	jne	.L962
	movl	-28(%rbp), %eax
	cltq
	movb	$0, -240(%rbp,%rax)
	leaq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	leaq	-240(%rbp), %rax
	addq	%rdx, %rax
	movl	$1718511918, (%rax)
	movb	$0, 4(%rax)
	leaq	-240(%rbp), %rcx
	movq	-248(%rbp), %rax
	movl	$26, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_read@PLT
	movsbl	%al, %eax
	movl	%eax, -20(%rbp)
.L962:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE148:
	.size	emb_pattern_loadExternalColorFile, .-emb_pattern_loadExternalColorFile
	.section	.rodata
	.align 8
.LC123:
	.string	"ERROR: emb-pattern.c emb_pattern_free(), p argument is null"
	.text
	.globl	emb_pattern_free
	.type	emb_pattern_free, @function
emb_pattern_free:
.LFB149:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L971
	leaq	.LC123(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L970
.L971:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdi
	call	emb_array_free
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, %rdi
	call	emb_array_free
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rdi
	call	emb_array_free
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	safe_free
.L970:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE149:
	.size	emb_pattern_free, .-emb_pattern_free
	.globl	emb_add_geometry
	.type	emb_add_geometry, @function
emb_add_geometry:
.LFB150:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	40(%rax), %rdx
	subq	$8, %rsp
	subq	$40, %rsp
	movq	%rsp, %rax
	movq	16(%rbp), %rcx
	movq	24(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	32(%rbp), %rcx
	movq	40(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	48(%rbp), %rcx
	movq	%rcx, 32(%rax)
	movq	%rdx, %rdi
	call	emb_array_add_geometry
	addq	$48, %rsp
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE150:
	.size	emb_add_geometry, .-emb_add_geometry
	.section	.rodata
	.align 8
.LC124:
	.string	"ERROR: emb-pattern.c emb_add_circle(), p argument is null"
	.text
	.globl	emb_add_circle
	.type	emb_add_circle, @function
emb_add_circle:
.LFB151:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%xmm0, %rax
	movaps	%xmm1, %xmm0
	movq	%rax, -88(%rbp)
	movss	%xmm0, -80(%rbp)
	cmpq	$0, -72(%rbp)
	jne	.L975
	leaq	.LC124(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L974
.L975:
	movq	-88(%rbp), %rax
	movq	%rax, -64(%rbp)
	movl	-80(%rbp), %eax
	movl	%eax, -56(%rbp)
	movl	$2, -36(%rbp)
	movq	-72(%rbp), %rax
	movq	40(%rax), %rdx
	subq	$8, %rsp
	subq	$40, %rsp
	movq	%rsp, %rax
	movq	-64(%rbp), %rcx
	movq	-56(%rbp), %rbx
	movq	%rcx, (%rax)
	movq	%rbx, 8(%rax)
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rbx
	movq	%rcx, 16(%rax)
	movq	%rbx, 24(%rax)
	movq	-32(%rbp), %rcx
	movq	%rcx, 32(%rax)
	movq	%rdx, %rdi
	call	emb_array_add_geometry
	addq	$48, %rsp
.L974:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE151:
	.size	emb_add_circle, .-emb_add_circle
	.section	.rodata
	.align 8
.LC125:
	.string	"ERROR: emb-pattern.c emb_pattern_addEllipseObjectAbs(), p argument is null"
	.text
	.globl	emb_add_ellipse
	.type	emb_add_ellipse, @function
emb_add_ellipse:
.LFB152:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L978
	leaq	.LC125(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L977
.L978:
	movq	-8(%rbp), %rax
	movq	40(%rax), %rsi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movl	32(%rbp), %eax
	movl	%eax, 16(%rcx)
	movq	%rsi, %rdi
	call	emb_array_add_ellipse
	addq	$32, %rsp
.L977:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE152:
	.size	emb_add_ellipse, .-emb_add_ellipse
	.section	.rodata
	.align 8
.LC126:
	.string	"ERROR: emb-pattern.c emb_pattern_addLineObjectAbs(), p argument is null"
	.text
	.globl	emb_add_line
	.type	emb_add_line, @function
emb_add_line:
.LFB153:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L981
	leaq	.LC126(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L980
.L981:
	movq	-8(%rbp), %rax
	movq	40(%rax), %rsi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	%rsi, %rdi
	call	emb_array_addLine
	addq	$32, %rsp
.L980:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE153:
	.size	emb_add_line, .-emb_add_line
	.section	.rodata
	.align 8
.LC127:
	.string	"ERROR: emb-pattern.c emb_pattern_addPathObjectAbs(), p argument is null"
	.align 8
.LC128:
	.string	"ERROR: emb-pattern.c emb_pattern_addPathObjectAbs(), obj->pointList is empty"
	.text
	.globl	emb_add_path
	.type	emb_add_path, @function
emb_add_path:
.LFB154:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L984
	leaq	.LC127(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L983
.L984:
	movq	16(%rbp), %rax
	testq	%rax, %rax
	jne	.L986
	leaq	.LC128(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L983
.L986:
	movq	-8(%rbp), %rax
	movq	40(%rax), %rsi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	%rsi, %rdi
	call	emb_array_addPath
	addq	$32, %rsp
.L983:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE154:
	.size	emb_add_path, .-emb_add_path
	.section	.rodata
	.align 8
.LC129:
	.string	"ERROR: emb-pattern.c emb_pattern_addPointObjectAbs(), p argument is null"
	.text
	.globl	emb_pattern_addPointAbs
	.type	emb_pattern_addPointAbs, @function
emb_pattern_addPointAbs:
.LFB155:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%xmm0, %rdx
	movq	%rsi, %rax
	movq	%rdx, -24(%rbp)
	movq	%rax, -16(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L988
	leaq	.LC129(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L987
.L988:
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	-24(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	%rcx, %xmm0
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_array_addPoint
.L987:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE155:
	.size	emb_pattern_addPointAbs, .-emb_pattern_addPointAbs
	.section	.rodata
	.align 8
.LC130:
	.string	"ERROR: emb-pattern.c emb_pattern_addPolygonObjectAbs(), p argument is null"
	.align 8
.LC131:
	.string	"ERROR: emb-pattern.c emb_pattern_addPolygonObjectAbs(), obj->pointList is empty"
	.text
	.globl	emb_pattern_addPolygonAbs
	.type	emb_pattern_addPolygonAbs, @function
emb_pattern_addPolygonAbs:
.LFB156:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L991
	leaq	.LC130(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L990
.L991:
	movq	16(%rbp), %rax
	testq	%rax, %rax
	jne	.L993
	leaq	.LC131(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L990
.L993:
	movq	-8(%rbp), %rax
	movq	40(%rax), %rsi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	%rsi, %rdi
	call	emb_array_addPolygon
	addq	$32, %rsp
.L990:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE156:
	.size	emb_pattern_addPolygonAbs, .-emb_pattern_addPolygonAbs
	.section	.rodata
	.align 8
.LC132:
	.string	"ERROR: emb-pattern.c emb_pattern_addPolylineObjectAbs(), p argument is null"
	.align 8
.LC133:
	.string	"ERROR: emb-pattern.c emb_pattern_addPolylineObjectAbs(), obj->pointList is empty"
	.text
	.globl	emb_pattern_addPolylineObjectAbs
	.type	emb_pattern_addPolylineObjectAbs, @function
emb_pattern_addPolylineObjectAbs:
.LFB157:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L995
	leaq	.LC132(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L994
.L995:
	movq	16(%rbp), %rax
	testq	%rax, %rax
	jne	.L997
	leaq	.LC133(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L994
.L997:
	movq	-8(%rbp), %rax
	movq	40(%rax), %rsi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	%rsi, %rdi
	call	emb_array_addPolyline
	addq	$32, %rsp
.L994:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE157:
	.size	emb_pattern_addPolylineObjectAbs, .-emb_pattern_addPolylineObjectAbs
	.section	.rodata
	.align 8
.LC134:
	.string	"ERROR: emb-pattern.c emb_pattern_addRectObjectAbs(), p argument is null"
	.text
	.globl	emb_pattern_addRectAbs
	.type	emb_pattern_addRectAbs, @function
emb_pattern_addRectAbs:
.LFB158:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L999
	leaq	.LC134(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L998
.L999:
	movq	-8(%rbp), %rax
	movq	40(%rax), %rsi
	subq	$8, %rsp
	subq	$24, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	%rax, 16(%rcx)
	movq	%rsi, %rdi
	call	emb_array_addRect
	addq	$32, %rsp
.L998:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE158:
	.size	emb_pattern_addRectAbs, .-emb_pattern_addRectAbs
	.globl	emb_pattern_end
	.type	emb_pattern_end, @function
emb_pattern_end:
.LFB159:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	testl	%eax, %eax
	je	.L1004
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cltq
	salq	$4, %rax
	subq	$16, %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$16, %eax
	je	.L1001
	movq	-8(%rbp), %rax
	movl	$1, %edx
	movl	$16, %esi
	pxor	%xmm1, %xmm1
	movl	.LC12(%rip), %ecx
	movd	%ecx, %xmm0
	movq	%rax, %rdi
	call	emb_pattern_addStitchRel
	jmp	.L1001
.L1004:
	nop
.L1001:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE159:
	.size	emb_pattern_end, .-emb_pattern_end
	.section	.rodata
	.align 8
.LC135:
	.string	"ERROR: convert(), cannot allocate memory for p"
	.align 8
.LC136:
	.string	"ERROR: convert(), reading file was unsuccessful: %s\n"
	.align 8
.LC137:
	.string	"ERROR: convert(), writing file %s was unsuccessful\n"
	.text
	.globl	convert
	.type	convert, @function
convert:
.LFB160:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	$0, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	emb_identify_format@PLT
	movl	%eax, -12(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	emb_identify_format@PLT
	movl	%eax, -16(%rbp)
	call	emb_pattern_create
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L1006
	leaq	.LC135(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L1007
.L1006:
	movl	-12(%rbp), %edx
	movq	-24(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_read@PLT
	testb	%al, %al
	jne	.L1008
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC136(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free
	movl	$1, %eax
	jmp	.L1007
.L1008:
	movl	-12(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	404+formatTable(%rip), %rdx
	movl	(%rax,%rdx), %eax
	cmpl	$2, %eax
	jne	.L1009
	movl	-16(%rbp), %eax
	cltq
	imulq	$420, %rax, %rax
	leaq	404+formatTable(%rip), %rdx
	movl	(%rax,%rdx), %eax
	cmpl	$1, %eax
	jne	.L1009
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_movePolylinesTostitch_list
.L1009:
	movl	-16(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_write@PLT
	testb	%al, %al
	jne	.L1010
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC137(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free
	movl	$1, %eax
	jmp	.L1007
.L1010:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_free
	movl	$0, %eax
.L1007:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE160:
	.size	convert, .-convert
	.globl	emb_pattern_color_count
	.type	emb_pattern_color_count, @function
emb_pattern_color_count:
.LFB161:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$0, -4(%rbp)
	movzwl	-48(%rbp), %eax
	movw	%ax, -11(%rbp)
	movzbl	-46(%rbp), %eax
	movb	%al, -9(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L1012
.L1019:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	imulq	$403, %rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %edx
	movw	%dx, -14(%rbp)
	movzbl	2(%rax), %eax
	movb	%al, -12(%rbp)
	movzbl	-11(%rbp), %eax
	movzbl	-10(%rbp), %edx
	salq	$8, %rdx
	orq	%rax, %rdx
	movzbl	-9(%rbp), %eax
	salq	$16, %rax
	orq	%rdx, %rax
	movq	%rax, %rsi
	movzwl	-14(%rbp), %eax
	movzbl	-12(%rbp), %edx
	salq	$16, %rdx
	orq	%rdx, %rax
	movq	%rax, %rdi
	call	embColor_distance
	testl	%eax, %eax
	je	.L1013
	addl	$1, -4(%rbp)
	movzwl	-14(%rbp), %eax
	movw	%ax, -11(%rbp)
	movzbl	-12(%rbp), %eax
	movb	%al, -9(%rbp)
	jmp	.L1016
.L1013:
	movl	-32(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	jne	.L1015
	movl	-32(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L1016
.L1015:
	addl	$1, -4(%rbp)
	jmp	.L1016
.L1018:
	addl	$1, -8(%rbp)
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	subl	$2, %eax
	cmpl	%eax, -8(%rbp)
	jge	.L1021
.L1016:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	addq	$1, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-32(%rbp), %eax
	cmpl	%eax, %edx
	je	.L1018
	jmp	.L1017
.L1021:
	nop
.L1017:
	addl	$1, -8(%rbp)
.L1012:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L1019
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE161:
	.size	emb_pattern_color_count, .-emb_pattern_color_count
	.section	.rodata
.LC138:
	.string	"Design Details"
.LC139:
	.string	"--------------"
.LC140:
	.string	"real_stitches: %d\n"
.LC141:
	.string	"trim_stitches: %d\n"
.LC142:
	.string	"unknown_stitches: %d\n"
.LC143:
	.string	"total_stitches: %d\n"
.LC144:
	.string	"num_colors: %d\n"
.LC145:
	.string	"Total thread usage: %f mm\n"
.LC146:
	.string	"Shortest stitch: %f mm\n"
.LC147:
	.string	"Longest stitch: %f mm\n"
.LC148:
	.string	"Stitches: %d\n"
.LC149:
	.string	"Colors: %d\n"
.LC150:
	.string	"Jumps: %d\n"
.LC151:
	.string	"Top: %f mm\n"
.LC152:
	.string	"Left: %f mm\n"
.LC153:
	.string	"Bottom: %f mm\n"
.LC154:
	.string	"Right: %f mm\n"
.LC155:
	.string	"Width: %f mm\n"
.LC156:
	.string	"Height: %f mm\n"
	.text
	.globl	emb_pattern_details
	.type	emb_pattern_details, @function
emb_pattern_details:
.LFB162:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movl	$1, -4(%rbp)
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, -8(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_realStitches
	movl	%eax, -12(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_jumpStitches
	movl	%eax, -16(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_trimStitches
	movl	%eax, -20(%rbp)
	movl	$0, -24(%rbp)
	leaq	-64(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_pattern_bounds
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_total_thread_length
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_shortest_stitch
	movd	%xmm0, %eax
	movl	%eax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_longest_stitch
	movd	%xmm0, %eax
	movl	%eax, -36(%rbp)
	leaq	.LC138(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC139(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC140(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC141(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC142(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC143(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	movl	%eax, %esi
	leaq	.LC144(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	pxor	%xmm2, %xmm2
	cvtss2sd	-28(%rbp), %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	leaq	.LC145(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	pxor	%xmm3, %xmm3
	cvtss2sd	-32(%rbp), %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	leaq	.LC146(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	pxor	%xmm4, %xmm4
	cvtss2sd	-36(%rbp), %xmm4
	movq	%xmm4, %rax
	movq	%rax, %xmm0
	leaq	.LC147(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC148(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC149(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC150(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movss	-60(%rbp), %xmm0
	pxor	%xmm5, %xmm5
	cvtss2sd	%xmm0, %xmm5
	movq	%xmm5, %rax
	movq	%rax, %xmm0
	leaq	.LC151(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movss	-64(%rbp), %xmm0
	pxor	%xmm6, %xmm6
	cvtss2sd	%xmm0, %xmm6
	movq	%xmm6, %rax
	movq	%rax, %xmm0
	leaq	.LC152(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movss	-52(%rbp), %xmm1
	movss	-60(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm7, %xmm7
	cvtss2sd	%xmm0, %xmm7
	movq	%xmm7, %rax
	movq	%rax, %xmm0
	leaq	.LC153(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movss	-56(%rbp), %xmm1
	movss	-64(%rbp), %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	leaq	.LC154(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movss	-56(%rbp), %xmm0
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm0, %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	leaq	.LC155(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movss	-52(%rbp), %xmm0
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm0, %xmm4
	movq	%xmm4, %rax
	movq	%rax, %xmm0
	leaq	.LC156(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$10, %edi
	call	putchar@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE162:
	.size	emb_pattern_details, .-emb_pattern_details
	.section	.rodata
.LC157:
	.string	"%d: %f %f %d\n"
	.text
	.globl	emb_pattern_print
	.type	emb_pattern_print, @function
emb_pattern_print:
.LFB163:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1024
.L1025:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$4, %rcx
	addq	%rcx, %rax
	movss	8(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$4, %rcx
	addq	%rcx, %rax
	movss	4(%rax), %xmm1
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm1, %xmm2
	movq	%xmm2, %rcx
	movl	-4(%rbp), %eax
	movapd	%xmm0, %xmm1
	movq	%rcx, %xmm0
	movl	%eax, %esi
	leaq	.LC157(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
.L1024:
	movq	-16(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1025
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE163:
	.size	emb_pattern_print, .-emb_pattern_print
	.globl	emb_pattern_lengthHistogram
	.type	emb_pattern_lengthHistogram, @function
emb_pattern_lengthHistogram:
.LFB164:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movl	%edx, -84(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_longest_stitch
	movd	%xmm0, %eax
	movl	%eax, -8(%rbp)
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1027
.L1028:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	addl	$1, -4(%rbp)
.L1027:
	movl	-4(%rbp), %eax
	cmpl	-84(%rbp), %eax
	jle	.L1028
	movl	$1, -4(%rbp)
	jmp	.L1029
.L1031:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	subq	$16, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movl	-64(%rbp), %edx
	movl	-48(%rbp), %eax
	orl	%edx, %eax
	testl	%eax, %eax
	jne	.L1030
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	-48(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	%rdx, %rcx
	movq	%rax, %rdx
	call	emb_stitch_length
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2ssl	-84(%rbp), %xmm0
	mulss	-20(%rbp), %xmm0
	divss	-8(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	call	floor@PLT
	cvttsd2sil	%xmm0, %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	addl	$1, %edx
	movl	%edx, (%rax)
.L1030:
	addl	$1, -4(%rbp)
.L1029:
	movq	-16(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1031
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE164:
	.size	emb_pattern_lengthHistogram, .-emb_pattern_lengthHistogram
	.globl	emb_pattern_realStitches
	.type	emb_pattern_realStitches, @function
emb_pattern_realStitches:
.LFB165:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1033
.L1035:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
	andl	$19, %eax
	testl	%eax, %eax
	jne	.L1034
	addl	$1, -8(%rbp)
.L1034:
	addl	$1, -4(%rbp)
.L1033:
	movq	-16(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1035
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE165:
	.size	emb_pattern_realStitches, .-emb_pattern_realStitches
	.globl	emb_pattern_jumpStitches
	.type	emb_pattern_jumpStitches, @function
emb_pattern_jumpStitches:
.LFB166:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1038
.L1040:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L1039
	addl	$1, -8(%rbp)
.L1039:
	addl	$1, -4(%rbp)
.L1038:
	movq	-16(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1040
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE166:
	.size	emb_pattern_jumpStitches, .-emb_pattern_jumpStitches
	.globl	emb_pattern_trimStitches
	.type	emb_pattern_trimStitches, @function
emb_pattern_trimStitches:
.LFB167:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1043
.L1045:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L1044
	addl	$1, -8(%rbp)
.L1044:
	addl	$1, -4(%rbp)
.L1043:
	movq	-16(%rbp), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1045
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE167:
	.size	emb_pattern_trimStitches, .-emb_pattern_trimStitches
	.globl	threadColor
	.type	threadColor, @function
threadColor:
.LFB168:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1048
.L1051:
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	brand_codes(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L1049
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	brand_codes(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	200(%rax), %eax
	jmp	.L1050
.L1049:
	addl	$1, -4(%rbp)
.L1048:
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	brand_codes(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	204(%rax), %eax
	testl	%eax, %eax
	jns	.L1051
	movl	$-1, %eax
.L1050:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE168:
	.size	threadColor, .-threadColor
	.globl	threadColorNum
	.type	threadColorNum, @function
threadColorNum:
.LFB169:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1053
.L1056:
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	brand_codes(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	200(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jne	.L1054
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	brand_codes(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	204(%rax), %eax
	jmp	.L1055
.L1054:
	addl	$1, -4(%rbp)
.L1053:
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	brand_codes(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	204(%rax), %eax
	testl	%eax, %eax
	jns	.L1056
	movl	$-1, %eax
.L1055:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE169:
	.size	threadColorNum, .-threadColorNum
	.section	.rodata
.LC158:
	.string	"COLOR NOT FOUND"
	.text
	.globl	threadColorName
	.type	threadColorName, @function
threadColorName:
.LFB170:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1058
.L1061:
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	brand_codes(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	200(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jne	.L1059
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	brand_codes(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	jmp	.L1060
.L1059:
	addl	$1, -4(%rbp)
.L1058:
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,8), %rdx
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdx
	leaq	brand_codes(%rip), %rax
	movq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	movl	204(%rax), %eax
	testl	%eax, %eax
	jns	.L1061
	leaq	.LC158(%rip), %rax
.L1060:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE170:
	.size	threadColorName, .-threadColorName
	.globl	scale_and_rotate
	.type	scale_and_rotate, @function
scale_and_rotate:
.LFB171:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%xmm0, -40(%rbp)
	movsd	%xmm1, -48(%rbp)
	movsd	%xmm2, -56(%rbp)
	pxor	%xmm3, %xmm3
	cvtsd2ss	-56(%rbp), %xmm3
	movd	%xmm3, %eax
	movd	%eax, %xmm0
	call	radians@PLT
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	call	cos@PLT
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	call	sin@PLT
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movss	-40(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	mulsd	-48(%rbp), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -32(%rbp)
	movss	-36(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	mulsd	-48(%rbp), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	movss	-32(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	mulsd	-16(%rbp), %xmm0
	movss	-28(%rbp), %xmm1
	cvtss2sd	%xmm1, %xmm1
	mulsd	-24(%rbp), %xmm1
	subsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -32(%rbp)
	movss	-32(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movapd	%xmm0, %xmm1
	mulsd	-24(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	mulsd	-16(%rbp), %xmm0
	addsd	%xmm1, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE171:
	.size	scale_and_rotate, .-scale_and_rotate
	.globl	emb_st_pos
	.type	emb_st_pos, @function
emb_st_pos:
.LFB172:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, %rax
	movq	%rsi, %rcx
	movq	%rcx, %rdx
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	movss	-8(%rbp), %xmm0
	movl	-12(%rbp), %eax
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	emb_vector@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE172:
	.size	emb_st_pos, .-emb_st_pos
	.globl	emb_stitch_length
	.type	emb_stitch_length, @function
emb_stitch_length:
.LFB173:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rsi, %rax
	movq	%rdi, %r8
	movq	%r8, %rsi
	movq	%r9, %rdi
	movq	%rax, %rdi
	movq	%rsi, -48(%rbp)
	movq	%rdi, -40(%rbp)
	movq	%rdx, -64(%rbp)
	movq	%rcx, -56(%rbp)
	movq	-64(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, %rsi
	call	emb_st_pos
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, %rsi
	call	emb_st_pos
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	call	emb_vector_distance@PLT
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE173:
	.size	emb_stitch_length, .-emb_stitch_length
	.globl	emb_pattern_real_count
	.type	emb_pattern_real_count, @function
emb_pattern_real_count:
.LFB174:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1069
.L1071:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	-32(%rbp), %eax
	andl	$3, %eax
	testl	%eax, %eax
	jne	.L1070
	addl	$1, -8(%rbp)
.L1070:
	addl	$1, -4(%rbp)
.L1069:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1071
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE174:
	.size	emb_pattern_real_count, .-emb_pattern_real_count
	.globl	emb_pattern_longest_stitch
	.type	emb_pattern_longest_stitch, @function
emb_pattern_longest_stitch:
.LFB175:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	$1, %eax
	jg	.L1074
	pxor	%xmm0, %xmm0
	jmp	.L1080
.L1074:
	pxor	%xmm0, %xmm0
	movss	%xmm0, -8(%rbp)
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L1076
.L1079:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	-32(%rbp), %eax
	testl	%eax, %eax
	jne	.L1077
	movl	-48(%rbp), %eax
	testl	%eax, %eax
	jne	.L1077
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	-48(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	%rdx, %rcx
	movq	%rax, %rdx
	call	emb_stitch_length
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	pxor	%xmm1, %xmm1
	cvtss2sd	-8(%rbp), %xmm1
	movsd	-16(%rbp), %xmm0
	comisd	%xmm1, %xmm0
	jbe	.L1077
	pxor	%xmm0, %xmm0
	cvtsd2ss	-16(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
.L1077:
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	addl	$1, -4(%rbp)
.L1076:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1079
	movss	-8(%rbp), %xmm0
.L1080:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE175:
	.size	emb_pattern_longest_stitch, .-emb_pattern_longest_stitch
	.globl	emb_pattern_shortest_stitch
	.type	emb_pattern_shortest_stitch, @function
emb_pattern_shortest_stitch:
.LFB176:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	$1, %eax
	jg	.L1083
	pxor	%xmm0, %xmm0
	jmp	.L1089
.L1083:
	movss	.LC159(%rip), %xmm0
	movss	%xmm0, -8(%rbp)
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L1085
.L1088:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	-32(%rbp), %eax
	testl	%eax, %eax
	jne	.L1086
	movl	-48(%rbp), %eax
	testl	%eax, %eax
	jne	.L1086
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	-48(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	%rdx, %rcx
	movq	%rax, %rdx
	call	emb_stitch_length
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	pxor	%xmm0, %xmm0
	cvtss2sd	-8(%rbp), %xmm0
	comisd	-16(%rbp), %xmm0
	jbe	.L1086
	pxor	%xmm0, %xmm0
	cvtsd2ss	-16(%rbp), %xmm0
	movss	%xmm0, -8(%rbp)
.L1086:
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	addl	$1, -4(%rbp)
.L1085:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1088
	movss	-8(%rbp), %xmm0
.L1089:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE176:
	.size	emb_pattern_shortest_stitch, .-emb_pattern_shortest_stitch
	.globl	emb_pattern_count_type
	.type	emb_pattern_count_type, @function
emb_pattern_count_type:
.LFB177:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L1092
.L1094:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	-32(%rbp), %eax
	andl	-44(%rbp), %eax
	testl	%eax, %eax
	je	.L1093
	addl	$1, -8(%rbp)
.L1093:
	addl	$1, -4(%rbp)
.L1092:
	movq	-40(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1094
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE177:
	.size	emb_pattern_count_type, .-emb_pattern_count_type
	.globl	emb_length_histogram
	.type	emb_length_histogram, @function
emb_length_histogram:
.LFB178:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	$1, %eax
	jle	.L1104
	movl	$0, -4(%rbp)
	jmp	.L1099
.L1100:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	addl	$1, -4(%rbp)
.L1099:
	movl	$10, %eax
	cmpl	%eax, -4(%rbp)
	jle	.L1100
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_longest_stitch
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L1101
.L1103:
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movl	-48(%rbp), %eax
	testl	%eax, %eax
	jne	.L1102
	movl	-64(%rbp), %eax
	testl	%eax, %eax
	jne	.L1102
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	-64(%rbp), %rdi
	movq	-56(%rbp), %rsi
	movq	%rdx, %rcx
	movq	%rax, %rdx
	call	emb_stitch_length
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movl	$10, %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	mulsd	-24(%rbp), %xmm0
	divsd	-16(%rbp), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	floor@PLT
	cvttsd2sil	%xmm0, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	addl	$1, %edx
	movl	%edx, (%rax)
.L1102:
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	addl	$1, -4(%rbp)
.L1101:
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1103
	jmp	.L1096
.L1104:
	nop
.L1096:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE178:
	.size	emb_length_histogram, .-emb_length_histogram
	.globl	emb_color_histogram
	.type	emb_color_histogram, @function
emb_color_histogram:
.LFB179:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	$1, %eax
	jle	.L1115
	movl	$0, -8(%rbp)
	jmp	.L1108
.L1111:
	movl	$0, -4(%rbp)
	jmp	.L1109
.L1110:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	$0, (%rax)
	addl	$1, -4(%rbp)
.L1109:
	movl	$10, %eax
	cmpl	%eax, -4(%rbp)
	jle	.L1110
	addl	$1, -8(%rbp)
.L1108:
	movq	-72(%rbp), %rax
	movq	24(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L1111
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	emb_pattern_longest_stitch
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L1112
.L1114:
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movl	-48(%rbp), %eax
	testl	%eax, %eax
	jne	.L1113
	movl	-64(%rbp), %eax
	testl	%eax, %eax
	jne	.L1113
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	-64(%rbp), %rdi
	movq	-56(%rbp), %rsi
	movq	%rdx, %rcx
	movq	%rax, %rdx
	call	emb_stitch_length
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movl	$10, %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	mulsd	-24(%rbp), %xmm0
	divsd	-16(%rbp), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	floor@PLT
	cvttsd2sil	%xmm0, %eax
	movl	%eax, -28(%rbp)
	movq	-80(%rbp), %rax
	movq	(%rax), %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %edx
	addl	$1, %edx
	movl	%edx, (%rax)
.L1113:
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	addl	$1, -4(%rbp)
.L1112:
	movq	-72(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1114
	jmp	.L1105
.L1115:
	nop
.L1105:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE179:
	.size	emb_color_histogram, .-emb_color_histogram
	.globl	emb_total_thread_length
	.type	emb_total_thread_length, @function
emb_total_thread_length:
.LFB180:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	$1, %eax
	jg	.L1117
	pxor	%xmm0, %xmm0
	jmp	.L1122
.L1117:
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L1119
.L1121:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	-48(%rbp), %eax
	testl	%eax, %eax
	jne	.L1120
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	-48(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	%rdx, %rcx
	movq	%rax, %rdx
	call	emb_stitch_length
	movsd	-16(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
.L1120:
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	addl	$1, -4(%rbp)
.L1119:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1121
	movsd	-16(%rbp), %xmm0
.L1122:
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE180:
	.size	emb_total_thread_length, .-emb_total_thread_length
	.globl	emb_total_thread_of_color
	.type	emb_total_thread_of_color, @function
emb_total_thread_of_color:
.LFB181:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	$1, %eax
	jg	.L1124
	pxor	%xmm0, %xmm0
	jmp	.L1129
.L1124:
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L1126
.L1128:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	-36(%rbp), %eax
	cmpl	%eax, -60(%rbp)
	jne	.L1127
	movl	-32(%rbp), %eax
	testl	%eax, %eax
	jne	.L1127
	movl	-48(%rbp), %eax
	testl	%eax, %eax
	jne	.L1127
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	-48(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movq	%rdx, %rcx
	movq	%rax, %rdx
	call	emb_stitch_length
	movsd	-16(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
.L1127:
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -32(%rbp)
	movq	%rdx, -24(%rbp)
	addl	$1, -4(%rbp)
.L1126:
	movq	-56(%rbp), %rax
	movq	32(%rax), %rax
	movl	24(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L1128
	movsd	-16(%rbp), %xmm0
.L1129:
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE181:
	.size	emb_total_thread_of_color, .-emb_total_thread_of_color
	.globl	emb_get_svg_token
	.type	emb_get_svg_token, @function
emb_get_svg_token:
.LFB182:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	jne	.L1131
	addq	$1, -24(%rbp)
.L1131:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L1132
	movl	$0, %eax
	jmp	.L1133
.L1132:
	movl	$0, -4(%rbp)
	jmp	.L1134
.L1136:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rcx
	movq	-32(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	jne	.L1135
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movl	-4(%rbp), %eax
	cltq
	addq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	jmp	.L1133
.L1135:
	addl	$1, -4(%rbp)
.L1134:
	cmpl	$199, -4(%rbp)
	jle	.L1136
	movl	$0, %eax
.L1133:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE182:
	.size	emb_get_svg_token, .-emb_get_svg_token
	.globl	emb_get_svg_vector
	.type	emb_get_svg_vector, @function
emb_get_svg_vector:
.LFB183:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$224, %rsp
	movq	%rdi, -216(%rbp)
	movq	%rsi, -224(%rbp)
	leaq	-208(%rbp), %rdx
	movq	-216(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_get_svg_token
	movq	%rax, -216(%rbp)
	cmpq	$0, -216(%rbp)
	jne	.L1138
	movl	$0, %eax
	jmp	.L1141
.L1138:
	leaq	-208(%rbp), %rax
	movq	%rax, %rdi
	call	atof@PLT
	cvtsd2ss	%xmm0, %xmm0
	movq	-224(%rbp), %rax
	movss	%xmm0, (%rax)
	leaq	-208(%rbp), %rdx
	movq	-216(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	emb_get_svg_token
	movq	%rax, -216(%rbp)
	cmpq	$0, -216(%rbp)
	jne	.L1140
	movl	$0, %eax
	jmp	.L1141
.L1140:
	leaq	-208(%rbp), %rax
	movq	%rax, %rdi
	call	atof@PLT
	cvtsd2ss	%xmm0, %xmm0
	movq	-224(%rbp), %rax
	movss	%xmm0, 4(%rax)
	movq	-216(%rbp), %rax
.L1141:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE183:
	.size	emb_get_svg_vector, .-emb_get_svg_vector
	.section	.rodata
	.align 4
.LC12:
	.long	0
	.align 16
.LC13:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.align 4
.LC37:
	.long	1073741824
	.align 4
.LC45:
	.long	1128792064
	.align 8
.LC46:
	.long	0
	.long	1072693248
	.align 4
.LC76:
	.long	1621981420
	.align 8
.LC77:
	.long	0
	.long	1079574528
	.align 4
.LC79:
	.long	1036831949
	.align 4
.LC80:
	.long	1067030938
	.align 4
.LC81:
	.long	1065353216
	.align 4
.LC85:
	.long	-1082130432
	.align 16
.LC100:
	.long	2147483647
	.long	0
	.long	0
	.long	0
	.align 4
.LC112:
	.long	-943501440
	.align 8
.LC113:
	.long	0
	.long	1090021872
	.align 8
.LC120:
	.long	0
	.long	1073741824
	.align 4
.LC159:
	.long	1343554297
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
