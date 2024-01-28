\chapter{CAD Command Overview}

\newcommand{\indexi}[1]{\index{#1}#1}
\newcommand{\indext}[1]{\index{#1}\texttt{#1}}


A CAD command\indext{CAD}\indext{command} in Embroidermodder is referred to as
an \emph{action}\indext{action} and the data needed for it to function is stored
in the \indext{action\_table}. For a regular user who wishes to use
more shortcuts and macros

\begin{longtable}{p{1cm} p{2.5cm} p{2cm} p{7cm}}
\caption{Overview of the CAD commands available on all platorms but with
various levels of support and applicability.}
\label{tab:command-table} \\
\textbf{ID} &
\textbf{name} &
\textbf{arguments} &
\textbf{description} \\

0 &
\indext{NEW} &
none &
Create a new EmbPattern with a new tab in the GUI. \\

1 &
\indext{OPEN} &
char array &
Open an EmbPattern with the supplied filename `fname'. \\

2 &
\indext{SAVE} &
char array &
Save the current loaded EmbPattern to the supplied filname `fname'. \\

3 &
\indext{SCALE} &
selected objects, 1 float &
Scale all selected objects by the number supplied, without selection scales the
entire design. \\

4 &
\indext{CIRCLE} &
mouse co-ords &
Adds a circle to the design based on the supplied numbers, converts to stitches
on save for stitch only formats. \\

5 &
\indext{OFFSET} &
mouse co-ords &
Shifts the selected objects by the amount given by the mouse co-ordinates. \\

6 &
\indext{EXTEND} &
 &
\\

7 &
\indext{TRIM} & 
selected stitches &
Sets the flag for the stitches selected to \texttt{TRIM}. \\

8 &
\indext{break\_at\_point} & 
&
\\

9 &
\indext{break\_2\_points} &
&
\\

10 &
\indext{FILLET} &
&
\\

11 &
\indext{STAR} &
mouse co-ords &
Adds a star to the vector layer at the mouse co-ords. \\

12 &
\indext{textsingle} &
&
\\

13 &
\indext{CHAMFER} &
&
\\

14 &
\indext{SPLIT} &
A selected line in the vector layer. Otherwise 2 mouse co-ords in sequence. &
Seperates stitch blocks by cutting threads between those either side of a line
supplied by the user then rerouting the stitches. \\

15 &
\indext{AREA} &
Selected objects &
\\

16 &
\indext{TIME} &
None &
Prints the current time as ISO formatted UTC to the console. \\

17 &
\indext{PICKADD} & 
None &
\\

16 &
\indext{ZOOMFACTOR} & 
float &
Sets the zoom factor to the supplied argument. \\

17 &
\indext{PRODUCT} & 
None &
Prints the name and build code of the running version of Embroidermodder
to disambiguate between forks and build versions. The string may only
start with \texttt{embroidermodder} if the build is from the official Embroidermodder
project under the terms of the license. \\

18 &
\indext{PROGRAM/PROG} &
&
\\

19 &
\indext{ZOOMWINDOW} &
&
\\

20 &
\indext{DIVIDE} &
&
\\

21 &
\indext{FIND} &
int &
Select the stitch at the index given and center the view on it. \\

22 &
\indext{RECORD} &
None &
Start recording all user input that passes through the actuator
(i.e. actions from this table, with all the data passed as arguments)
for forming macros. Stop recording if RECORD/PLAYBACK/END is issued. \\

23 &
\indext{PLAYBACK} &
None &
\\

24 &
\indext{ROTATE} &
&
\\

25 &
\indext{RGB} &
&
\\

26 &
\indext{move} &
&
\\

27 &
\indext{grid} &
&
\\

28 &
\indext{griphot} &
&
\\

29 &
\indext{gripcolor} &
&
\\

30 &
\indext{gripcool} &
&
\\

31 &
\indext{gripsize} &
&
\\

32 &
\indext{highlight} &
&
\\

33 &
\indext{units} &
&
\\

34 &
\indext{locatepoint} &
&
\\

35 &
\indext{distance} &
  &
\\

36 &
 \indext{ARC} &
 &
\\

37 &
\indext{ELLIPSE} &
 &
\\

38 &
\indext{ARRAY} &
 &
\\

39 &
\indext{POINT} &
 &
\\

40 &
\indext{POLYLINE} &
 &
\\

41 &
\indext{POLYGON} &
 &
\\

42 &
\indext{rectangle} &
 &
\\

43 &
\indext{line} &
 &
\\

44 &
\indext{arc-rt} &
 &
\\

45 &
\indext{dolphin} &
&
\\

46 &
\indext{heart} &
&

\end{longtable}

\section{Actions}

\subsection{ABOUT}
\indext{action}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
0 & none & 
\end{tabular}
\end{center}

\subsection{ADD-ARC}
\indext{action}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
1 & mouse co-ords & 
\end{tabular}
\end{center}

\subsection{ADD-CIRCLE}
\indext{ADD-CIRCLE}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
2 & mouse co-ords & 
\end{tabular}
\end{center}

\subsection{ADD-DIM-LEADER}
\indext{ADD-DIM-LEADER}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
3 & none & 
\end{tabular}
\end{center}

\subsection{ADD-ELLIPSE}
\indext{ADD-ELLIPSE}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
4 & none & 
\end{tabular}
\end{center}

\subsection{ADD-GEOMETRY}
\indext{ADD-GEOMETRY}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
5 & none & 
\end{tabular}
\end{center}

\subsection{ADD-HORIZONTAL-DIMENSION}
\indext{ADD-HORIZONTAL-DIMENSION}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
6 & none & 
\end{tabular}
\end{center}

\subsection{ADD-IMAGE}
\indext{ADD-IMAGE}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
7 & none & 
\end{tabular}
\end{center}

\subsection{ADD-INFINITE-LINE}
\indext{ADD-INFINITE-LINE}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
8 & none & 
\end{tabular}
\end{center}

\subsection{ADD-LINE}
\indext{ADD-LINE}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
9 & none & 
\end{tabular}
\end{center}

\subsection{ADD-PATH}
\indext{ADD-PATH}

index 10

\subsection{ADD-POINT}
\indext{ADD-POINT}

index 11

\subsection{ADD-POLYGON}
\indext{ADD-POLYGON}

index 12

\subsection{ADD-POLYLINE}
\indext{ADD-POLYLINE}

index 13

\subsection{ADD-RAY}
\indext{ADD-RAY}

index 14

\subsection{ADD-RECTANGLE}
\indext{ADD-RECTANGLE}

index 15

\subsection{ADD-REGULAR-POLYGON}
\indext{ADD-REGULAR-POLYGON}

index 16

\subsection{ADD-ROUNDED-RECTANGLE}
\indext{action}

index 17

\subsection{ADD-RUBBER}
\indext{ADD-RUBBER}

index 18

\subsection{ADD-SLOT}
\indext{action}

index 19

\subsection{ADD-TEXT-MULTI}
\indext{action}

index 20

\subsection{ADD-TEXT-SINGLE}
\indext{action}

index 21

\subsection{ADD-TO-SELECTION}
\indext{action}

index 22

\subsection{ADD-TRIANGLE}
\indext{action}

index 23

\subsection{ADD-VERTICAL-DIMENSION}
\indext{action}

index 24

\subsection{ALERT}
\indext{action}

index 25

\subsection{ALLOW-RUBBER}
\indext{action}

index 26

\subsection{APPEND-HISTORY}
\indext{action}

index 27

\subsection{CALCULATE-ANGLE}
\indext{action}

index 28

\subsection{CALCULATE-DISTANCE}
\indext{action}

index 29

\subsection{CHANGELOG}
\indext{action}

index 30

\subsection{CLEAR-RUBBER}
\indext{action}

index 31

\subsection{CLEAR-SELECTION}
\indext{action}

index 32

\subsection{COPY}
\indext{action}

index 33

\subsection{COPY-SELECTED}
\indext{action}

index 34

\subsection{CUT}
\indext{action}

index 35

\subsection{CUT-SELECTED}
\indext{action}

index 36

\subsection{DAY}
\indext{action}

index 37

\subsection{DEBUG}
\indext{action}

index 38

\subsection{DELETE-SELECTED}
\indext{action}

index 39

\subsection{DESIGN-DETAILS}
\indext{action}

index 40

\subsection{DO-NOTHING}
\indext{action}

index 41

\subsection{END}
\indext{action}

index 42

\subsection{ERROR}
\indext{action}

index 43

\subsection{HELP}
\indext{action}

index 44

\subsection{ICON}
\indext{action}

index 45

\subsection{INIT}
\indext{action}

index 46

\subsection{MESSAGEBOX}
\indext{action}

index 47, 3 char arrays deliminated by quotes Example Call

\subsection{MIRROR-SELECTED}
\indext{action}

index 48

\subsection{MOUSE-X}
\indext{action}

index 49

\subsection{MOUSE-Y}
\indext{action}

index 50

\subsection{MOVE-SELECTED}
\indext{action}

index 51

\subsection{NEW}
\indext{action}

index 52

\subsection{NIGHT}
\indext{action}

index 53

\subsection{NUM-SELECTED}
\indext{action}

index 54

\subsection{OPEN}
\indext{action}

index 55

\subsection{PAN}
\indext{action}

index 56

\subsection{PASTE}
\indext{PASTE}

index 57

\subsection{PASTE-SELECTED}
\indext{PASTE-SELECTED}

index 58

\subsection{PERPENDICULAR-DISTANCE}
\indext{PERPENDICULAR-DISTANCE}

index 59

\subsection{PLATFORM}
\indext{PLATFORM}

index 60

\subsection{PREVIEW-OFF}
\indext{PREVIEW-OFF}

index 61

\subsection{PREVIEW-ON}
\indext{PREVIEW-ON}

index 62

\subsection{PRINT}
\indext{PRINT}

index 63

\subsection{PRINT-AREA}
\indext{PRINT-AREA}

index 64

\subsection{QSNAP-X}
\indext{QSNAP-X}

index 65

\subsection{QSNAP-Y}
\indext{QSNAP-Y}

index 66

\subsection{EXIT}
\indext{EXIT}

 index 67

\subsection{REDO}
\indext{REDO}

index 68

\subsection{ROTATE-SELECTED}
\indext{ROTATE-SELECTED}

index 69

\subsection{RUBBER}
\indext{RUBBER}

index 70

\subsection{SCALE-SELECTED}
\indext{SCALE-SELECTED}

index 71

\subsection{SELECT-ALL}
\indext{SELECT-ALL}

index 72

\subsection{SETTINGS-DIALOG}
\indext{action}

index 73

\subsection{SET-BACKGROUND-COLOR}
\indext{action}

index 74

\subsection{SET-CROSSHAIR-COLOR}
\indext{action}

index 75

\subsection{SET-CURSOR-SHAPE}
\indext{action}

index 76

\subsection{SET-GRID-COLOR}
\indext{action}

index 77

\subsection{SET-PROMPT-PREFIX}
\indext{action}

index 78

\subsection{SET-RUBBER-FILTER}
\indext{action}

index 79

\subsection{SET-RUBBER-MODE}
\indext{action}

index 80

\subsection{SET-RUBBER-POINT}
\indext{action}

index 81

\subsection{SET-RUBBER-TEXT}
\indext{action}

index 82

\subsection{SPARE-RUBBER}
\indext{action}

index 83

\subsection{TIP-OF-THE-DAY}
\indext{action}

index 84

\subsection{TODO}
\indext{action}

 index 85

\subsection{UNDO}
\indext{action}

 index 86

\subsection{VERSION}
\indext{action}

index 87

\subsection{VULCANIZE}
\indext{action}

index 88

\subsection{WHATS-THIS}
\indext{action}

index 89

\subsection{WINDOW-CLOSE}
\indext{action}

index 90

\subsection{WINDOW-CLOSE-ALL}
\indext{action}

index 91

\subsection{WINDOW-TILE}
\indext{action}

index 92

\subsection{WINDOW-CASCADE}
\indext{action}

index 93

\subsection{WINDOW-NEXT}
\indext{action}

index 94

\subsection{WINDOW-PREVIOUS}
\indext{action}

index 95

\subsection{ZOOM}
\indext{action}

 index 96

\subsection{ZOOM-IN}
\indext{action}

index 97

\subsection{TEST}
\indext{action}

 index 98

\subsection{SLEEP}
\indext{action}

index 99

\subsection{LAYER-EDITOR}
\indext{action}

index 100

\subsection{MAKE-LAYER-CURRENT}
\indext{action}

index 101

\subsection{TEXT-BOLD}
\indext{action}

index 102

\subsection{TEXT-ITALIC}
\indext{action}

index 103

\subsection{TEXT-UNDERLINE}
\indext{action}

index 104

\subsection{TEXT-STRIKEOUT}
\indext{action}

index 105

\subsection{TEXT-OVERLINE}
\indext{action}

index 106

\subsection{LAYER-PREVIOUS}
\indext{action}

index 107

\subsection{ICON16}
\indext{action}

index 108

\subsection{ICON24}
\indext{action}

index 109

\subsection{ICON32}
\indext{action}

index 110

\subsection{ICON48}
\indext{action}

index 111

\subsection{ICON64}
\indext{action}

index 112

\subsection{ICON128}
\indext{action}

index 113

\subsection{SAVE}
\indext{action}

index 114

\subsection{SAVEAS}
\indext{action}

index 115

\subsection{PAN-REAL-TIME}
\indext{action}

index 116

\subsection{PAN-POINT}
\indext{action}

index 117

\subsection{PAN-LEFT}
\indext{action}

index 118

\subsection{PAN-RIGHT}
\indext{action}

index 119

\subsection{PAN-UP}
\indext{action}

index 120

\subsection{PAN-DOWN}
\indext{action}

index 121

\subsection{ZOOM-REAL-TIME}
\indext{action}

index 122

\subsection{ZOOM-PREVIOUS}
\indext{action}

index 123

\subsection{ZOOM-WINDOW}
\indext{action}

index 124

\subsection{ZOOM-DYNAMIC}
\indext{action}

index 125

\subsection{ZOOM-OUT}
\indext{action}

index 126

\subsection{ZOOM-EXTENTS}
\indext{action}

index 127

\subsection{LAYERS}
\indext{action}

index 128

\subsection{LAYER-SELECTOR}
\indext{action}

index 129

\subsection{TREBLECLEF}
\indext{action}

index 130

\subsection{COLOR-SELECTOR}
\indext{action}

index 131

\subsection{LINE-TYPE-SELECTOR}
\indext{action}

index 132

\subsection{LINE-WEIGHT-SELECTOR}
\indext{action}

index 133

\subsection{ZOOM-SCALE}
\indext{action}

index 134

\subsection{ZOOM-CENTER}
\indext{action}

index 135

\subsection{HIDE-ALL-LAYERS}
\indext{action}

index 136

\subsection{ZOOM-SELECTED}
\indext{action}

index 137

\subsection{ZOOM-ALL}
\indext{action}

index 138

\subsection{ADD-HEART}
\indext{action}

index 139

\subsection{ADD-SINGLE-LINE-TEXT}
\indext{action}

index 140

\subsection{SHOW-ALL-LAYERS}
\indext{action}

index 141

\subsection{FREEZE-ALL-LAYERS}
\indext{action}

index 142

\subsection{THAW-ALL-LAYERS}
\indext{action}

index 143

\subsection{LOCK-ALL-LAYERS}
\indext{action}

index 144

\subsection{UNLOCK-ALL-LAYERS}
\indext{UNLOCK-ALL-LAYERS}

index 145

\subsection{ADD-DOLPHIN}
\indext{ADD-DOLPHIN}

index 146

\subsection{ADD-DISTANCE}
\indext{ADD-DISTANCE}

index 147

\subsection{LOCATE-POINT}
\indext{LOCATE-POINT}

index 148

\subsection{QUICKSELECT}
\indext{QUICKSELECT}

index 149

\subsection{SPELLCHECK}
\indext{SPELLCHECK}

index 150

\subsection{DISTANCE}
\indext{DISTANCE}

index 151

\subsection{MOVE}
\indext{MOVE}

index 152

\subsection{QUICKLEADER}
\indext{QUICKLEADER}

index 153

\subsection{RGB}
\indext{RGB}

 index 154

\subsection{ROTATE}
\indext{ROTATE}

index 155

\subsection{SANDBOX}
\indext{SANDBOX}

index 156

\subsection{ADD-SNOWFLAKE}
\indext{ADD-SNOWFLAKE}

index 157

\subsection{ADD-STAR}
\indext{ADD-STAR}

index 158

\subsection{DELETE}
\indext{DELETE}

index 159

\subsection{SCALE}
\indext{SCALE}

index 160

\subsection{SINGLE-LINE-TEXT}
\indext{SINGLE-LINE-TEXT}

index 161

\subsection{SYSWINDOWS}
\indext{SYSWINDOWS}

index 162
