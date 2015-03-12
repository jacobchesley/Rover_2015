1 - Copy folder plugins and paste into KiCad\bin

2 - Install Saxon
	http://sourceforge.net/projects/saxon/files/Saxon-HE/9.5/


3 - Click BOM in KiCad.
	Add Plugin
	Add C:\Saxonica\SaxonHE9.5N\bin\Transform as the file
	Name - Saxon
	Command Line:
	"C:\Saxonica\SaxonHE9.5N\bin\Transform.exe" -t "%I" -xsl:"C:\KiCad\bin\plugins\bom2csv.xsl" -o:"%O.csv"