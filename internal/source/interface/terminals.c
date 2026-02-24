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
	for (int C1 = LDE_LOGMAX - 1; C1 > 0; C1++) {
		strncpy(Interface.Terminal_Logs[C1], Interface.Terminal_Logs[C1 - 1], sizeof(Interface.Terminal_Logs[C1]));
	}
	strncpy(Interface.Terminal_Logs[0], Line, sizeof(Interface.Terminal_Logs[0]));
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
	SDL_Surface* Carrying_Surface = TTF_RenderText_Blended(Fonts.Terminal_Font, Carrier, 0, Colors.Cherry_Blossom);
	SDL_Texture* Carrying_Texture = Surface_To_Texture(Core.Renderer, Carrying_Surface);
	SDL_FRect Destination = {
		(Settings.Screen_Size * 230.0f) - (Carrying_Surface->w * 0.5f),
		(Settings.Screen_Size * 180.0f) - (Carrying_Surface->h * 0.5f),
		(float)(Carrying_Surface->w),
		(float)(Carrying_Surface->h)
	};
	Render_Texture(Carrying_Texture, &Destination);
	SDL_DestroySurface(Carrying_Surface);
	free_texture(Carrying_Texture);
	Render_Button(&Textures.Error_Exit, &Rects.Error_Exit, 3, Colors.Cherry_Blossom);
	if (Interface.UI_Selection == 3) {
		const char* Parameters[2] = {
			"quit",
			NULLSTRING
		};
		Return_Command(Execute, Parameters);
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
	for (int C1 = 0; C1 < Hitboxes->Length; C1++) {
		Render_Button(&Buttons->Data[C1], &Hitboxes->Data[C1], C1 + 3, Colors.Pure_White);
	}
}

void Print_Response(const char* Response) {
	char Carrier[256];
	snprintf(Carrier, sizeof(Carrier), ": %s.", Response);
	Push_Terminal(Carrier);
}

void Print_JSON() {
	Push_Terminal("{");
	for (int C1 = 0; C1 < veclen(Buffers.JSON); C1++) {
		char Comma[4] = "\",";
		if (C1 == veclen(Buffers.JSON) - 1) {
			strncpy(Comma, "\"", sizeof(Comma));
		}
		char Buffer[128];
		snprintf(Buffer, sizeof(Buffer), "    \"%s%s", Buffers.JSON[C1], Comma);
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
	snprintf(Buffer, sizeof(Buffer), "librenectere/%s.elf", Machine);
	Process_Supply(&Supplies.Terminal_Title, Buffer, Fonts.Terminal_Font, Colors.Cherry_Blossom, 50, 50);
	Render_Texture(Textures.Terminal_Prompt, &Rects.Terminal_Prompt);
	if (strlen(Interface.Terminal_Entry) > 0) {
		char Carrier[128];
		snprintf(Carrier, sizeof(Carrier), "%s.%s;", Prefix, Interface.Terminal_Entry);
		strncpy(Interface.Terminal_Entry, Carrier, sizeof(Interface.Terminal_Entry));
		char* Result = malloc(sizeof(char) * (strlen(Interface.Terminal_Entry) + 1));
		int Index = 0;
		for (int C1 = 0; C1 < strlen(Interface.Terminal_Entry); C1++) {
			if (C1 >= Temporary.Ticker_Position || C1 > strlen(Interface.Terminal_Entry)) {
				break;
			}
			Result[Index] = Interface.Terminal_Entry[C1];
			Index++;
		}
		Result[Index] = '\0';
		if (strlen(Result) > 0) {
			Process_Supply(&Supplies.Terminal_Command, Result, Fonts.Terminal_Font, Colors.Cherry_Blossom, 64, 300);
		}
		free_c(Result);
	}
	for (int C1 = LDE_LOGMAX - 1; C1 > LDE_INVALID; C1--) {
		Process_Supply(&Supplies.Terminal_Logs[C1], Interface.Terminal_Logs[C1], Fonts.Terminal_Font,
			Colors.Cherry_Blossom, 50, 280 - (C1 * 20));
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

void Return_Command(const int Type, const char* Parameters[]) {
	if (Type == Get_Data) {
		strncpy(Interface.Terminal_Entry, "open(", sizeof(Interface.Terminal_Entry));
	} else {
		strncpy(Interface.Terminal_Entry, "call(", sizeof(Interface.Terminal_Entry));
	}
	for (int C1 = 0; C1 < veclen(Parameters); C1++) {
		charcat(Interface.Terminal_Entry, '\"', sizeof(Interface.Terminal_Entry));
		strcat_c(Interface.Terminal_Entry, Parameters[C1], sizeof(Interface.Terminal_Entry));
		if (C1 == 0) {
			if (Type == Get_Data) {
				strcat_c(Interface.Terminal_Entry, ".json", sizeof(Interface.Terminal_Entry));
			} else {
				strcat_c(Interface.Terminal_Entry, ".so", sizeof(Interface.Terminal_Entry));
			}
		}
		charcat(Interface.Terminal_Entry, '\"',  sizeof(Interface.Terminal_Entry));
		if (C1 < veclen(Parameters) - 1) {
			strcat_c(Interface.Terminal_Entry, ", ", sizeof(Interface.Terminal_Entry));
		}
	}
	charcat(Interface.Terminal_Entry, ')', sizeof(Interface.Terminal_Entry));
}

void Process_Commands() {
	int Base = intlen(Buffers.Commands);
	Buffers.Commands[Base] = Execute;
	strncpy(Buffers.Parameters[Base][0], "clear", sizeof(Buffers.Parameters[Base][0]));
	strncpy(Buffers.Parameters[Base][1], NULLSTRING, sizeof(Buffers.Parameters[Base][1]));
	Buffers.Commands[Base + 1] = Execute;
	strncpy(Buffers.Parameters[Base + 1][0], "quit", sizeof(Buffers.Parameters[Base + 1][0]));
	strncpy(Buffers.Parameters[Base + 1][1], NULLSTRING, sizeof(Buffers.Parameters[Base + 1][1]));
	Buffers.Commands[Base + 2] = LDE_TERMINATOR;
	for (int C1 = 0; C1 < intlen(Buffers.Commands); C1++) {
		if (Interface.UI_Selection == C1 + 3) {
			Return_Command(Buffers.Commands[C1], (const char**)Buffers.Parameters[C1]);
		}
	}
	for (int C1 = 3; C1 < intlen(Buffers.Commands) + 3; C1++) {
		Tick_Input(C1, false);
	}
}