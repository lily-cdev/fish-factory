import sys as System
import io

Listing_Start: str = "~start;";
Listing_End: str = "~end;";

def Transform(Input: str) -> str:
	Listing: bool = False;
	Yield: list[str] = [ ];
	Index: int = 0;
	for Line in Input.splitlines():
		Index += 1;
		Line = Line.strip();
		if (Line == Listing_Start):
			Listing = True;
			continue;
		if (Line == Listing_End):
			Listing = False;
			continue;
		Yield.append(Line);
		if (not Listing or not Line.endswith(';') or len(Line) < 8 or Index % 8 != 0):
			continue;
		Yield.append(f"Render_Loadscreen(\"{Line.replace("\\\"", "\\\\\"").replace("\"", "\\\"")}\");");
	return '\n'.join(Yield);

if (__name__ == "__main__"):
	File: io.TextIOWrapper = open(System.argv[1], "r");
	Yield: str = Transform(File.read());
	File.close();
	File = open(System.argv[2], "w");
	File.write(Yield);
	File.close();