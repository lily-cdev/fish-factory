#include <ui.h>

char Errors[LDE_ERRORS][32] = {
	"NO DOCKED SUB",
	"SUB DOCKED",
	"TARGET EMPTY",
	"FILE NOT FOUND",
	"LOW VALUE",
	"NO FISH PRESENT",
	"FISH PRESENT",
	"NO INPUT",
	"NO OUTPUT",
	"TOO MANY INPUTS",
	"TOO MANY OUTPUTS",
	"TOO MANY CONTROLLERS",
	"NO POOL TILES"
};

void Push_Terminal(const char* Line) {
	for (int Counter = LDE_LOGMAX - 1; Counter > 0; Counter++) {
		strcpy(Interface.Terminal_Logs[Counter], Interface.Terminal_Logs[Counter - 1]);
	}
	strcpy(Interface.Terminal_Logs[0], Line);
}

void To_Code(int Input, char* Yield) {
	int Position = 0;
	while (Input != 0) {
		int Intermediate = Input & 15;
		Yield[Position] = (char)(Intermediate < 10 ? Intermediate + 48 : Intermediate + 55);
		Position++;
		Input /= 16;
	}
	if (Position != 2) {
		Yield[1] = Yield[0];
		Yield[0] = '0';
	}
	Yield[2] = '\0';
}

void Print_Error(int Input) {
	char Carrier[256];
	char Code[4];
	To_Code(Input, Code);
	snprintf(Carrier, sizeof(Carrier), ": ERROR 0x%s -> %s", Code, Errors[Input]);
	Push_Terminal(Carrier);
}

void Print_Fatal_Error(int Input) {
	char Carrier[256];
	char Code[4];
	To_Code(Input, Code);
	snprintf(Carrier, sizeof(Carrier), "FATAL ERROR 0x%s -> %s", Code, Errors[Input]);
	SDL_Surface* Carrying_Surface = TTF_RenderText_Blended(Fonts.Terminal_Font, Carrier, strlen(Carrier),
		Colors.Cherry_Blossom);
	SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Carrying_Surface);
	SDL_FRect Destination = {
		(Settings.Screen_Size * 230.0f) - (Carrying_Surface->w * 0.5f),
		(Settings.Screen_Size * 180.0f) - (Carrying_Surface->h * 0.5f),
		(float)(Carrying_Surface->w),
		(float)(Carrying_Surface->h)
	};
	SDL_RenderTexture(Core.Renderer, Carrying_Texture,
		NULL, &Destination);
	SDL_DestroySurface(Carrying_Surface);
	SDL_DestroyTexture(Carrying_Texture);
	Render_Button(Textures.Error_Exit, Rects.Error_Exit, 3, Colors.Cherry_Blossom);
	if (Interface.UI_Selection == 3) {
		const char* Parameters[2] = {
			"quit",
			NULLSTRING
		};
		Return_Command(Execute, Parameters, Interface.Terminal_Entry);
	}
	Tick_Input(3, false);
}

void Process_Exit() {
	if (Interface.UI_Selection == 3) {
		Interface.Prompt_Identifier = LDE_INVALID;
		Interface.Subprompt_Identifier = LDE_INVALID;
	}
}

void Render_Backing() {
	Render_Box(40, 40, 380, 280, Colors.Abyss_Black, Colors.Dark_Grey);
	Render_Box(460, 40, 140, 280, Colors.Abyss_Black, Colors.Dark_Grey);
}

void Render_Sidebuttons(Texture2_Array* Buttons, Rect2_Array* Hitboxes) {
	for (int Counter = 0; Counter < Hitboxes->Length; Counter++) {
		Render_Button((*Buttons).Data[Counter], (*Hitboxes).Data[Counter], Counter + 3, Colors.Pure_White);
	}
}

void Print_Response(const char* Response) {
	char Carrier[256];
	snprintf(Carrier, sizeof(Carrier), ": %s.", Response);
	Push_Terminal(Carrier);
}

void Print_JSON() {
	Push_Terminal("{");
	for (int Counter = 0; Counter < veclen(Buffers.JSON); Counter++) {
		char Comma[4] = "\",";
		if (Counter == veclen(Buffers.JSON) - 1) {
			strcpy(Comma, "\"");
		}
		char Buffer[128];
		snprintf(Buffer, sizeof(Buffer), "    \"%s%s", Buffers.JSON[Counter], Comma);
		Push_Terminal(Buffer);
	}
	Push_Terminal("}");
}

void Print_Input() {
	char Buffer[256];
	snprintf(Buffer, sizeof(Buffer), "> %s", Interface.Terminal_Entry);
	Push_Terminal(Buffer);
	Temporary.Ticker_Position = 0;
	Temporary.Ticker_Frames = 0;
}

void Forward_Essentials(int Buttons, int Sliders) {
	Interface.Terminal_Clearing = false;
	if (Interface.UI_Selection > 2 && Interface.UI_Selection < Buttons + Sliders + 1) {
		Print_Input();
	}
	if (Interface.UI_Selection == Buttons + 1) {
		Interface.Terminal_Clearing = true;
		Interface.Terminal_Length = 0;
	} else if (Interface.UI_Selection == Buttons + 2) {
		Interface.Prompt_Identifier = LDE_INVALID;
		Interface.Subprompt_Identifier = LDE_INVALID;
		Interface.Terminal_Length = 0;
	}
}

void Backward_Essentials() {
	if (Interface.Terminal_Clearing) {
		Print_Response("cleared console log");
	}
}

void Render_Necessities(char* Machine, char* Prefix) {
	char Buffer[64];
	snprintf(Buffer, sizeof(Buffer), "librenectere/%s.exe", Machine);
	Render_Dynamic_Text(Fonts.Terminal_Font, Buffer, Colors.Cherry_Blossom, 50, 50);
	Render_Dynamic_Text(Fonts.Terminal_Font, "> ", Colors.Cherry_Blossom, 50, 300);
	if (strlen(Interface.Terminal_Entry) > 0) {
		char Carrier[128];
		snprintf(Carrier, sizeof(Carrier), "%s.%s;", Prefix, Interface.Terminal_Entry);
		strcpy(Interface.Terminal_Entry, Carrier);
		char* Result = malloc(sizeof(char) * (strlen(Interface.Terminal_Entry) + 1));
		int Index = 0;
		for (int Counter = 0; Counter < strlen(Interface.Terminal_Entry); Counter++) {
			if (Counter >= Temporary.Ticker_Position || Counter > strlen(Interface.Terminal_Entry)) {
				break;
			}
			Result[Index] = Interface.Terminal_Entry[Counter];
			Index++;
		}
		Result[Index] = '\0';
		if (strlen(Result) > 0) {
			Render_Dynamic_Text(Fonts.Terminal_Font, Result, Colors.Cherry_Blossom, 64, 300);
		}
	}
	for (int Counter = LDE_LOGMAX - 1; Counter > LDE_INVALID; Counter--) {
		Render_Dynamic_Text(Fonts.Terminal_Font, Interface.Terminal_Logs[Counter], Colors.Cherry_Blossom,
			50, 280 - (Counter * 20));
	}
}

void Tick_Input(int Target, bool Slider) {
	int Cross_Checker = Interface.UI_Selection;
	if (Slider) {
		Cross_Checker = Interface.Engagement;
	}
	if (Cross_Checker == Target) {
		Temporary.Ticker_Target = Target;
		if (Temporary.Ticker_Position < 50) {
			Temporary.Ticker_Frames++;
			if (Temporary.Ticker_Frames > Interface.Frame_Rate / 20) {
				Temporary.Ticker_Frames = 0;
				Temporary.Ticker_Position++;
			}
		}
	} else {
		if (Temporary.Ticker_Target == Target) {
			Temporary.Ticker_Position = 0;
			Temporary.Ticker_Frames = 0;
		}
	}
}

void Return_Command(const int Type, const char* Parameters[], char* Yield) {
	if (Type == Get_Data) {
		strcpy(Yield, "open(");
	} else {
		strcpy(Yield, "call(");
	}
	for (int Counter = 0; Counter < veclen(Parameters); Counter++) {
		charcat(Yield, '\"');
		strcat(Yield, Parameters[Counter]);
		if (Counter == 0) {
			if (Type == Get_Data) {
				strcat(Yield, ".json");
			} else {
				strcat(Yield, ".so");
			}
		}
		charcat(Yield, '\"');
		if (Counter < veclen(Parameters) - 1) {
			strcat(Yield, ", ");
		}
	}
	charcat(Yield, ')');
}

void Process_Commands() {
	int Base = intlen(Buffers.Commands);
	Buffers.Commands[Base] = Execute;
	strcpy(Buffers.Parameters[Base][0], "clear");
	strcpy(Buffers.Parameters[Base][1], NULLSTRING);
	Buffers.Commands[Base + 1] = Execute;
	strcpy(Buffers.Parameters[Base + 1][0], "quit");
	strcpy(Buffers.Parameters[Base + 1][1], NULLSTRING);
	Buffers.Commands[Base + 2] = LDE_TERMINATOR;
	for (int Counter = 0; Counter < intlen(Buffers.Commands); Counter++) {
		if (Interface.UI_Selection == Counter + 3) {
			Return_Command(Buffers.Commands[Counter], Buffers.Parameters[Counter], Interface.Terminal_Entry);
		}
	}
	for (int Counter = 3; Counter < intlen(Buffers.Commands) + 3; Counter++) {
		Tick_Input(Counter, false);
	}
}