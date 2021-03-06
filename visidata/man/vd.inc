.Dd March 05, 2018
.Dt vd \&1 "Quick Reference Guide" 
.Os Linux/MacOS
.
.\" Long option with arg: .Lo f filetype format
.\" Long flag: .Lo f filetype
.de Lo
.It Cm -\\$1 Ns , Cm --\\$2 Ns = Ns Ar \\$3
..
.de Lf
.It Cm -\\$1 Ns , Cm --\\$2
..
.Sh NAME
.
.Nm VisiData
.Nd a terminal utility for exploring and arranging tabular data
.
.Sh SYNOPSIS
.
.Nm vd
.Op Ar options
.Op Ar input No ...
.
.Nm vd
.Op Ar options
.Cm --play Ar cmdlog
.Op Cm -w Ar waitsecs
.Op Cm --batch
.Op Cm -o Ar output
.Op Ar field Ns Cm = Ns Ar value No ...
.
.Sh DESCRIPTION
.Nm VisiData No is a multipurpose tool built on the Sy vdtui No platform that can be used to explore, clean, edit, and restructure data.
Rows can be selected, filtered, and grouped; columns can be rearranged, transformed, and derived via regex or Python expressions; and workflows can be saved, documented, and replayed.
.
.Ss REPLAY MODE
.Bl -tag -width XXXXXXXXXXXXXXXXXXXXXX -compact
.Lo p play cmdlog
.No replay a saved Ar cmdlog No within the interface
.
.Lo w replay-wait seconds
.No wait Ar seconds No between commands
.
.Lf b batch
replay in batch mode (with no interface)
.
.Lo o output file
.No save final visible sheet to Ar file No as .tsv
.
.It Sy --replay-movement= Ns Ar bool
.No toggle Sy --play No to move cursor cell-by-cell
.It Ar field Ns Cm = Ns Ar value
.No replace \&"{ Ns Ar field Ns }\&" in Ar cmdlog No contents with Ar value
.El
.
.Ss Commands During Replay
.Bl -tag -width XXXXXXXXXXXXXXXXXXX -compact -offset XXX
.It Sy ^U
pause/resume replay
.It Sy Tab
execute next row in replaying sheet
.It Sy ^K
cancel current replay
.El
.
.Ss GLOBAL COMMANDS
In most cases, commands that affect selected rows will affect all rows if no rows are selected.
.Pp
.Ss Keystrokes for the Cautious
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic " F1   z?"
view this man page
.It Ic ^Q
abort program immediately
.It Ic ^C
cancel user input or aborts all async threads on current sheet
.It Ic " q"
quit current sheet
.It Ic "gq"
quit all sheets (clean exit)
.It Ic "Backspace"
.No quit current sheet and remove it from the Sy CommandLog
.El
.Ss "Cursor Movement"
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.
.It Ic "Arrow PgUp Home"
move as expected
.It Ic " h   j   k   l"
move left/down/up/right
.It Ic "gh  gj  gk  gl"
move all the way to the left/bottom/top/right of sheet
.It Ic "     G  gg"
move all the way to the bottom/top of sheet
.It Ic "^B  ^F"
scroll one page back/forward
.Pp
.It Ic  " /   ?" Ar regex
.No search for Ar regex No forward/backward in current column
.It Ic  "g/  g?" Ar regex
.No search for Ar regex No forward/backward over all visible columns
.It Ic  " n   N"
move to next/previous match from last search
.Pp
.It Ic  " <   >"
move up/down in current column to the next value
.It Ic " {   }"
move up/down in current column to the next selected row
.
.El
.Pp
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.Pp
.It Ic " c" Ar regex
.No move to next column with name matching Ar regex
.It Ic " r" Ar regex
.No move to next row with key matching Ar regex
.It Ic "zc  zr" Ar number
.No move to column/row Ar number
.Pp
.It Ic " H   J   K   L"
slide current row/column left/down/up/right
.It Ic "gH  gJ  gK  gL"
slide current row/column all the way to the left/bottom/top/right of sheet
.Pp
.It Ic "zh  zj  zk  zl"
scroll one left/down/up/right
.It Ic "  zt  zz  zb  "
scroll current row to top/center/bottom of screen
.El
.
.Ss Column Manipulation
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.
.It Ic " _" Ns " (underscore)"
adjust width of current column
.It Ic "g_"
adjust width of all visible columns
.It Ic "z_" Ar number
.No adjust width of current column to Ar number
.Pp
.It Ic " -" Ns " (hyphen)"
hide current column (to unhide, go to
.Sy C Ns olumns sheet and Sy e Ns dit its width)
.It Ic "z-" Ns
reduce width of current column by half
.Pp
.It Ic "! z!" Ns
toggle/unset current column as a key column
.It Ic "~  #  %  $  @"
set type of current column to untyped/int/float/currency/date
.It Ic "  ^"
edit name of current column
.It Ic " g^"
set names of all unnamed visible columns to contents of selected rows (or current row)
.It Ic " z^"
set name of current column to contents of current cell
.It Ic "gz^"
set name of current column to combined contents of current column for selected rows (or current row)
.Pp
.It Ic "  =" Ar expr
.No create new column from Python Ar expr Ns , with column names as variables
.It Ic " g=" Ar expr
.No set current column for selected rows to result of Python Ar expr
.It Ic "gz=" Ar expr
.No set current column for selected rows to the items in result of Python sequence Ar expr
.It Ic " z=" Ar expr
.No set current cell to result of evaluated Python Ar expr No on current row
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic " '" Ns " (tick)"
add a frozen copy of current column with all cells evaluated
.It Ic "g'"
open a frozen copy of current sheet with all visible columns evaluated
.It Ic "z'  gz'"
add/reset cache for current/all visible column(s)
.Pp
.It Ic "\&:" Ar regex
.No add new columns from Ar regex No split; number of columns determined by example row at cursor
.It Ic "\&;" Ar regex
.No add new columns from capture groups of Ar regex Ns (also requires example row)
.It Ic "*" Ar regex Ns Sy / Ns Ar subst
.No replace Ar regex No with Ar subst Ns , which may include backreferences ( Ns Sy \e1 No etc.)
.El
.Ss Row Selection
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.
.It Ic " s   t   u"
select/toggle/unselect current row
.It Ic "gs  gt  gu"
select/toggle/unselect all rows
.It Ic " |   \e\ " Ns Ar regex
.No select/unselect rows matching Ar regex No in current column
.It Ic "g|  g\e\ " Ns Ar regex
.No select/unselect rows matching Ar regex No in any visible column
.It Ic " \&," Ns " (comma)"
select rows matching current cell in current column
.It Ic "g\&,"
select rows matching current row in all visible columns
.
.El
.
.
.Ss Row Sorting/Filtering
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.
.It Ic " [   ]"
sort ascending/descending by current column
.It Ic "g[  g]"
sort ascending/descending by all key columns
.It Ic " \&""
open duplicate sheet with only selected rows
.It Ic "g\&""
open duplicate sheet with all rows
.It Ic "gz\&""
open duplicate sheet with deepcopy of selected rows
.El
.Ss Editing Rows and Cells
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic "  a   za"
append a blank row/column
.It Ic " ga  gza" Ar number
.No append Ar number No blank rows/columns
.It Ic "  d   gd"
delete current/selected row(s) and move to clipboard
.It Ic "  y   gy"
yank (copy) current/all selected row(s) to clipboard
.It Ic " zy"
yank (copy) current cell to clipboard
.It Ic "  p    P"
paste clipboard rows after/before current row
.It Ic " zp  gzp"
set contents of current column for current/selected row(s) to last clipboard value
.It Ic "  Y   gY"
.No yank (copy) current/all selected row(s) to system clipboard (with Sy options.clipboard_copy_cmd Ns )
.It Ic " zY"
.No yank (copy) current cell to system clipboard (with Sy options.clipboard_copy_cmd Ns )
.It Ic "  f"
fill null cells in current column with contents of non-null cells up the current column
.
.
.It Ic "  e" Ar text
edit contents of current cell
.It Ic " ge" Ar text
.No set contents of current column for selected rows to Ar text
.It Ic " zd   Del"
.No set contents of current cell to Sy None
.It Ic "gzd  gDel"
.No set contents of cells in current column to Sy None No for selected rows
.
.El
.
.Ss "  Commands While Editing Input"
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic "Enter  ^C"
accept/abort input
.It Ic ^O
open external $EDITOR to edit contents
.It Ic ^R
reload initial value
.It Ic "^A  ^E"
move to beginning/end of line
.It Ic "^B  ^F"
move back/forward one character
.It Ic "^H  ^D"
delete previous/current character
.It Ic ^T
transpose previous and current characters
.It Ic "^U  ^K"
clear from cursor to beginning/end of line
.It Ic "Backspace  Del"
delete previous/current character
.It Ic Insert
toggle insert mode
.It Ic "Up  Down"
set contents to previous/next in history
.It Ic "Tab  Shift+Tab"
autocomplete input (when available)
.
.El
.
.Ss Data Toolkit
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic " o" Ar input
open
.Ar input No in Sy VisiData
.It Ic "^S" Ar filename
.No save current sheet to Ar filename No in format determined by extension (default .tsv)
.It Ic "^D" Ar filename.vd
.No save CommandLog to Ar filename.vd No file
.It Ic "A" Ar number
.No open new blank sheet with Ar number No columns
.It Ic "R" Ar number
select a random population subset of
.Ar number No rows
.Pp
.It Ic " +" Ar aggregator
.No add Ar aggregator No to current column (see Sy "Frequency Table" Ns )
.It Ic "z+" Ar aggregator
.No display result of Ar aggregator No over values in selected rows for current column
.Pp
.El
.Ss Data Visualization
.Bl -tag -width XXXXXXXXXXXXX -compact
.It Ic " ." No (dot)
.No plot current numeric column vs key columns. The numeric key column is used for the x-axis; categorical key column values determine color.
.It Ic "g."
.No plot a graph of all visible numeric columns vs key columns.
.Pp
.El
.No If rows on the current sheet represent plottable coordinates (as in .shp or vector .mbtiles sources),
.Ic " ." No plots the current row, and Ic "g." No plots all selected rows (or all rows if none selected).
.Ss "  Canvas-specific Commands"
.Bl -tag -width XXXXXXXXXXXXXXXXXX -compact -offset XXX
.It Ic " +   -"
increase/decrease zoom level, centered on cursor
.It Ic " _" No (underscore)
zoom to fit full extent
.It Ic " s   t   u"
select/toggle/unselect rows on source sheet contained within canvas cursor
.It Ic "gs  gt  gu"
select/toggle/unselect rows on source sheet visible on screen
.It Ic " d"
delete rows on source sheet contained within canvas cursor
.It Ic "gd"
delete rows on source sheet visible on screen
.It Ic " Enter"
open sheet of source rows contained within canvas cursor
.It Ic "gEnter"
open sheet of source rows visible on screen
.It Ic " 1" No - Ic "9"
toggle display of layers
.It Ic "^L"
redraw all pixels on canvas
.It Ic " w"
.No toggle Ic show_graph_labels No option
.It Ic "mouse scrollwheel"
zoom in/out of canvas
.It Ic "left click-drag"
set canvas cursor
.It Ic "right click-drag"
scroll canvas
.El
.Ss Other Commands
.
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.
.It Ic V
view contents of current cell in a new TextSheet
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset xxx
.It Ic "v"
toggle visibility (text wrap on TextSheet, legends/axes on Graph)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic " ^^" No (Ctrl-^)
jump to previous sheet (swaps with current sheet)
.It Ic " ^E"
view traceback for most recent error
.It Ic "g^E"
view traceback for most recent errors
.It Ic "z^E"
view traceback for error in current cell
.It Ic " ^L"
refresh screen
.It Ic " ^G"
show cursor position and bounds of current sheet on status line
.It Ic " ^V"
show version information on status line
.It Ic " ^R"
reload current sheet
.It Ic "z^R"
clear cache for current column
.It Ic " ^Z"
suspend VisiData process
.It Ic " ^P"
.No open Sy Status History
.
.El
.Pp
.Bl -tag -width XXXXXXXXXXXXXXX -compact
.It Ic " ^Y  z^Y  g^Y"
open current row/cell/sheet as Python object
.It Ic " ^X" Ar expr
.No evaluate Python Ar expr No and opens result as Python object
.It Ic "z^X" Ar expr
.No evaluate Python Ar expr No on current row and shows result on status line
.It Ic "g^X" Ar stmt
.No execute Python Ar stmt No in the global scope
.El
.
.Ss Internal Sheets List
.Bl -tag -width Xx -compact
.It " "
.It Sy Metasheets
.It Sy " \&."
.Sy Columns Sheet No (Shift+C) "    edit column properties"
.It Sy " \&."
.Sy Sheets Sheet No (Shift+S) "     jump between sheets or join them together"
.It Sy " \&."
.Sy Options Sheet No (Shift+O) "    edit all configurable options"
.It Sy " \&."
.Sy Commandlog No (Shift+D) "       modify and save commands for replay"
.It Sy " \&."
.Sy Error Sheet No (^E) "           view last error"
.It Sy " \&."
.Sy Status History No (^P) "        view history of status messages"
.It Sy " \&."
.Sy Threads Sheet No (^T) "         view, cancel, and profile asynchronous threads"
.Pp
.It Sy Derived Sheets
.It Sy " \&."
.Sy Frequency Table No (Shift+F) "  group rows by column value, with aggregations of other columns"
.It Sy " \&."
.Sy Describe Sheet No (Shift+I) "   view summary statistics for each column"
.It Sy " \&."
.Sy Pivot Table No (Shift+W) "      group rows by key and summarize current column"
.It Sy " \&."
.Sy Melted Sheet No (Shift+M) "     unpivot non-key columns into variable/value columns"
.El
.Ss METASHEETS
.Ss Columns Sheet (Shift+C)
.Bl -inset -compact
.It Properties of columns on the source sheet can be changed with standard editing commands ( Ns Sy e  ge g= Del Ns ) on the Sy Columns Sheet Ns . Multiple aggregators can be set by listing them (separated by spaces) in the aggregators column.  The 'g' commands affect the selected rows, which are the literal columns on the source sheet.
.It (global commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic gC
.No open Sy Columns Sheet No with all columns from all sheets
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic " &"
add column from concatenating selected source columns
.It Ic "g! gz!"
toggle/unset selected columns as key columns on source sheet
.It Ic "g+"
add aggregator to selected source columns
.It Ic "g-" No (hyphen)
hide selected columns on source sheet
.It Ic "g~ g# g% g$ g@"
set type of selected columns on source sheet to str/int/float/currency/date
.It Ic " Enter"
.No open a Sy Frequency Table No sheet grouped by column referenced in current row
.El
.
.Ss Sheets Sheet (Shift+S)
.Bl -inset -compact 
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic "Enter"
jump to sheet referenced in current row
.It Ic "gC"
.No open Sy Columns Sheet No with all columns from selected sheets
.It Ic "&" Ar jointype
.No merge selected sheets with visible columns from all, keeping rows according to Ar jointype Ns :
.El
.Bl -tag -width x -compact -offset XXXXXXXXXXXXXXXXXXXX 
.It Sy "\&."
.Sy inner No " keep only rows which match keys on all sheets"
.It Sy "\&."
.Sy outer No "  keep all rows from first selected sheet"
.It Sy "\&."
.Sy full No "  keep all rows from all sheets (union)"
.It Sy "\&."
.Sy diff No "  keep only rows NOT in all sheets"
.It Sy "\&."
.Sy append No "keep all rows from all sheets (concatenation)"
.El
.
.Ss Options Sheet (Shift+O)
.Bl -inset -compact 
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic "Enter  e"
edit option
.El
.
.Ss CommandLog (Shift+D)
.Bl -inset -compact
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic " x"
replay command in current row
.It Ic "gx"
replay contents of entire CommandLog
.It Ic " ^C"
abort replay
.El
.
.Ss DERIVED SHEETS
.Ss Frequency Table (Shift+F)
.Bl -inset -compact
.It A Sy Frequency Table No groups rows by one or more columns, and includes summary columns for those with aggregators.
.It (global commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic gF
open Frequency Table, grouped by all key columns on source sheet
.It Ic zF
open one-line summary for selected rows
.It (sheet-specific commands)
.It Ic " s   t   u"
select/toggle/unselect these entries in source sheet
.It Ic " Enter"
open sheet of source rows that are grouped in current cell
.El
.
.Ss Describe Sheet (Shift+I)
.Bl -inset -compact
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic "zs  zu"
select/unselect rows on source sheet that are being described in current cell
.It Ic " !"
toggle/unset current column as a key column on source sheet
.It Ic " Enter"
.No open a Sy Frequency Table No sheet grouped on column referenced in current row
.It Ic "zEnter"
open copy of source sheet with rows described in current cell
.El
.
.Ss Pivot Table (Shift+W)
.Bl -inset -compact
.It Set key column(s) and aggregators on column(s) before pressing Sy Shift+W No on the column to pivot.
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic " Enter"
open sheet of source rows aggregated in current pivot row
.It Ic "zEnter"
open sheet of source rows aggregated in current pivot cell
.El
.Ss Melted Sheet (Shift+M)
.Bl -inset -compact
.It Opens melted sheet (unpivot), with all non-key columns reduced to Variable-Value rows.
.El
.Ss Python Object Sheet (^X ^Y g^Y z^Y)
.Bl -inset -compact
.It (sheet-specific commands)
.El
.Bl -tag -width XXXXXXXXXXXXXXX -compact -offset XXX
.It Ic " Enter"
dive further into Python object
.It Ic " e"
edit contents of current cell
.It Ic "v"
toggle show/hide for methods and hidden properties
.It Ic "gv  zv"
show/hide methods and hidden properties
.It Ic " ("
expand current column of lists or dicts into multiple columns and hide original column
.It Ic " )"
unexpand current column; restore original column and remove other columns at this level
.El
.
.Sh COMMANDLINE OPTIONS
.Bl -tag -width XXXXXXXXXXXXXXXXXXXXXXXXXXX -compact
.
.Lo f filetype filetype
.No "tsv               "
set loader to use for
.Ar filetype
instead of file extension
.
.Lo y confirm-overwrite F
.No "True              "
overwrite existing files without confirmation
.
.It Cm --diff Ns = Ns Ar base
.No "None              "
.No add colorizer for all sheets against Ar base
.
.El
.so vd-cli.inc
.
.Ss DISPLAY OPTIONS
.No Display options can only be set via the Sx Options Sheet No or a config file (see Sx FILES Ns ).
.Pp
.
.so vd-opts.inc
.
.Sh EXAMPLES
.Dl Nm vd Cm foo.tsv
.Pp
.Dl Nm vd Cm -f sqlite bar.db
.Pp
.Dl Nm vd Cm -b countries.fixed -o countries.tsv
.Pp
.Dl Nm vd Cm postgres:// Ns Ar username Ns Sy "\&:" Ns Ar password Ns Sy @ Ns Ar hostname Ns Sy  "\&:" Ns Ar port Ns Sy / Ns Ar database
.Pp
.Dl Nm vd Cm --play tests/pivot.vd --replay-wait 1 --output tests/pivot.tsv
.Pp
.Dl Ic ls -l | Nm vd Cm -f fixed --skip 1 --header 0
.Pp
.Dl Nm vd Cm -p foo.vd -b -o - > foo.tsv
.Pp
.Dl Nm vd --diff foo.tsv bar.tsv
.Pp
.Sh FILES
At the start of every session,
.Sy VisiData No looks for Pa $HOME/.visidatarc Ns , and calls Python exec() on its contents if it exists.
For example:
.Bd -literal
   options.min_memory_mb=100  # stop processing without 100MB free

   globalCommand('0', 'gh')   # alias '0' to move to first column, like vim

   def median(values):
       L = sorted(values)
       return L[len(L)//2]

   aggregator('median', median)
.Ed
.
.Sh SUPPORTED SOURCES
These are the supported sources:
.Pp
.Bl -inset -compact -offset xxx
.It Sy tsv No (tab-separated value)
.Bl -inset -compact -offset xxx
.It Plain and simple.  Nm VisiData No writes tsv format by default.  See the Sy --delimiter No option.
.El
.El
.Pp
.Bl -inset -compact -offset xxx
.It Sy csv No (comma-separated value)
.Bl -inset -compact -offset xxx
.It .csv files are a scourge upon the earth, and still regrettably common.  
.It See the Sy --csv-dialect Ns , Sy --csv-delimiter Ns , Sy --csv-quotechar Ns , and Sy --csv-skipinitialspace No options.  
.It Accepted dialects are Ic excel-tab Ns , Ic unix Ns , and Ic excel Ns .
.El
.El
.Pp
.Bl -inset -compact -offset xxx
.It Sy fixed No (fixed width text)
.Bl -inset -compact -offset xxx
.It Columns are autodetected from the first 1000 rows (adjustable with Sy --fixed-rows Ns ).
.El
.El
.Pp
.Bl -inset -compact -offset xxx
.It Sy json No (single object) and Sy jsonl No (one object per line).
.Bl -inset -compact -offset xxx
.It Cells containing lists (e.g. Sy [3] Ns ) or dicts ( Ns Sy {3} Ns ) can be expanded into new columns with Sy "\&(" Ns and unexpanded with Sy "\&)" Ns .
.El
.El
.Pp
.Bl -inset -compact -offset xxx
.It Sy png No (requires Sy pypng Ns )
.Bl -inset -compact -offset xxx
.It Pixels can be edited and saved in data form. Images can be plotted with Ic "\&." No (dot).
.El
.El
.
.Pp
The following URL schemes are supported:
.Bl -inset -compact -offset xxx
.It Sy http No (requires Sy requests Ns ); can be used as transport for with another filetype
.It Sy postgres No (requires Sy psycopg2 Ns )
.El
.
.Pp
.Bl -inset -compact
.It The following sources may include multiple tables.  The initial sheet is the table directory;
.Sy Enter No loads the entire table into memory.
.El
.
.Pp
.Bl -inset -compact -offset xxx
.It Sy sqlite
.It Sy xlsx No (requires Sy openpyxl Ns )
.It Sy xls No (requires Sy xlrd Ns )
.It Sy hdf5 No (requires Sy h5py Ns )
.It Sy shp No (requires Sy pyshp Ns )
.It Sy ttf Ns / Ns Sy otf No (requires Sy fonttools Ns )
.It Sy mbtiles No (requires Sy mapbox-vector-tile Ns )
.It Sy html No (requires Sy lxml Ns )
.El
.Pp
In addition, 
.Sy .zip Ns , Sy .gz Ns , Sy .bz2 Ns , and Sy .xz No files are decompressed on the fly.
.
.Sh SUPPORTED OUTPUT FORMATS
These are the supported savers:
.Pp
.Bl -inset -compact -offset xxx
.It Sy tsv No (tab-separated value)
.It Sy csv No (comma-separated value)
.It Sy json No (one object with all rows)
.Bl -inset -compact -offset xxx
.It All expanded subcolumns must be closed (with Sy "\&)" Ns ) to retain the same structure.
.El
.It Sy md No (org-mode compatible markdown table)
.It Sy html No (requires Sy lxml Ns )
.It Sy png No (requires Sy pypng Ns )
.El
.Pp
.
.Sh AUTHOR
.Nm VisiData
was made by
.An Saul Pwanson Aq Mt vd@saul.pw Ns .
