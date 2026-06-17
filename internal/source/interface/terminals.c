#include <ui.h>

char Errors[ktn_errors][32] = {
	"no docked sub",
	"sub docked",
	"target empty",
	"file not found",
	"low value",
	"no fish present",
	"fish present",
	"no input",
	"no output",
	"too many inputs",
	"too many outputs",
	"too many controllers",
	"no pool tiles",
	"no impulse"
};

void Push_Terminal(const char* Line) {
	for (int C1 = ktn_log_max - 1; C1 > 0; C1--) {
		strncpy(Interface.Terminal_Logs[C1], Interface.Terminal_Logs[C1 - 1], sizeof(Interface.Terminal_Logs[C1]));
	}
	strncpy(Interface.Terminal_Logs[0], Line, sizeof(Interface.Terminal_Logs[0]));
}

void To_Code(int Input, char* Yield) {
	const char* Lookup = "0123456789abcdef";
	Yield[0] = Lookup[(Input >> 4) & 15];
	Yield[1] = Lookup[Input & 15];
	Yield[2] = '\0';
}

void Print_Error(int Input) {
	char Carrier[256];
	char Code[4];
	To_Code(Input, Code);
	snprintf(Carrier, sizeof(Carrier), ": error 0x%s -> %s", Code, Errors[Input]);
	Push_Terminal(Carrier);
}

void Print_Fatal_Error(int Input) {
	char Carrier[256];
	char Code[4];
	To_Code(Input, Code);
	snprintf(Carrier, sizeof(Carrier), "fatal error 0x%s -> %s", Code, Errors[Input]);
	SDL_Texture* Carrying_Texture = Render_Text(F_Terminal, Carrier, Colors.Cherry_Blossom);
	SDL_FRect Destination = {
		(Settings.Scalar * 230.0f) - (Carrying_Texture->w * 0.5f),
		Core.Screenhalfsize.Y - (Carrying_Texture->h * 0.5f),
		(float)Carrying_Texture->w,
		(float)Carrying_Texture->h
	};
	Render_Texture(Carrying_Texture, &Destination);
	ktn_free_texture(Carrying_Texture);
	if (Render_Button(&Textures.Error_Exit, &Rects.Error_Exit, (UI_Link){ Machine_Exit }, Colors.Cherry_Blossom)) {
		char Parameters[2][ktn_param_max] = { "quit" };
		strcpy(Parameters[1], ktn_null_string);
		Return_Command(Execute, 2, Parameters);
		Tick_Input(1, false);
	}
}

void Render_Backing() {
	Render_Box((Point){ 40, 40 }, 380, 280, Colors.Abyss_Black, Colors.Dark_Grey);
	Render_Box((Point){ 460, 40 }, 140, 280, Colors.Abyss_Black, Colors.Dark_Grey);
}

void Machine_Clear(Parameter Unused, Parameter Unused2) {
	memset(Interface.Terminal_Logs, 0, ktn_log_max * ktn_param_max);
	Interface.Terminal_Length = 0;
	Print_Response("cleared console log");
}

void Render_Sidebuttons(Texture2_Array* Buttons, Rect2_Array* Hitboxes, UI_Link* Links) {
	Links[Hitboxes->Length - 2] = (UI_Link){ Machine_Clear };
	Links[Hitboxes->Length - 1] = (UI_Link){ Machine_Exit };
	bool Hit = false;
	for (int C1 = 0; C1 < Hitboxes->Length; C1++) {
		if (!Render_Button(&Buttons->Data[C1], &Hitboxes->Data[C1], Links[C1], Colors.Pure_White)) {
			continue;
		}
		if (Interface.Engagement != 0) {
			continue;
		}
		Return_Command(Buffers.Commands[C1], 4, Buffers.Parameters[C1]);
		Tick_Input(C1 + 1, false);
		Hit = true;
	}
	if (!Hit && Interface.Engagement == 0) {
		Temporary.Ticker_Frames = 0;
		Temporary.Ticker_Position = 0;
		Temporary.Ticker_Target = 0;
	}
}

void Tick_Input(int Target, bool Slider) {
	if (Slider && -Target != Interface.Engagement) {
		return;
	}
	if (Temporary.Ticker_Target != Target) {
		Temporary.Ticker_Target = Target;
		Temporary.Ticker_Frames = 0;
		Temporary.Ticker_Position = 0;
	}
	Temporary.Ticker_Frames++;
	if (Temporary.Ticker_Frames > Interface.Frame_Rate * 0.05f) {
		Temporary.Ticker_Frames = 0;
		Temporary.Ticker_Position++;
	}
}

void Print_Response(const char* Response) {
	char Carrier[256];
	snprintf(Carrier, sizeof(Carrier), ": %s.", Response);
	Push_Terminal(Carrier);
}

void Print_JSON() {
	Push_Terminal("{");
	for (int C1 = 0; C1 < ktn_veclen(Buffers.JSON); C1++) {
		char Comma[4] = "\",";
		if (C1 == ktn_veclen(Buffers.JSON) - 1) {
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

void Render_Necessities(char* Machine, char* Prefix) {
	char Buffer[64];
	snprintf(Buffer, sizeof(Buffer), "librenectere/%s.elf", Machine);
	Process_Supply(&Supplies.Terminal_Title, Buffer, F_Terminal, Colors.Cherry_Blossom, (Point){ 50, 50 });
	//Render_Texture(Textures.Terminal_Prompt, &Rects.Terminal_Prompt); TMP
	if (strlen(Interface.Terminal_Entry) > 0) {
		char Carrier[128];
		snprintf(Carrier, sizeof(Carrier), "%s.%s;", Prefix, Interface.Terminal_Entry);
		strncpy(Interface.Terminal_Entry, Carrier, sizeof(Interface.Terminal_Entry));
		char* Result = malloc(strlen(Interface.Terminal_Entry) + 3);
		strcpy(Result, "> ");
		int Index = 2;
		for (int C1 = 0; C1 < strlen(Interface.Terminal_Entry); C1++) {
			if (C1 >= Temporary.Ticker_Position || C1 > strlen(Interface.Terminal_Entry)) {
				break;
			}
			Result[Index] = Interface.Terminal_Entry[C1];
			Index++;
		}
		Result[Index] = '\0';
		if (strlen(Result) > 0) {
			Process_Supply(&Supplies.Terminal_Command, Result, F_Terminal, Colors.Cherry_Blossom, (Point){ 50, 300 });
		}
		ktn_free(Result);
	}
	for (int C1 = ktn_log_max - 1; C1 > ktn_invalid; C1--) {
		Process_Supply(&Supplies.Terminal_Logs[C1], Interface.Terminal_Logs[C1], F_Terminal, Colors.Cherry_Blossom,
			(Point){ 50, 280 - (C1 * 20) });
	}
}

void Return_Command(const int Type, const int Length, const char Parameters[Length][ktn_param_max]) {
	if (Type == Get_Data) {
		strcpy(Interface.Terminal_Entry, "open(");
	} else {
		strcpy(Interface.Terminal_Entry, "call(");
	}
	for (int C1 = 0; C1 < ktn_veclen(Parameters); C1++) {
		ktn_charcat(Interface.Terminal_Entry, '\"', sizeof(Interface.Terminal_Entry));
		strcat(Interface.Terminal_Entry, Parameters[C1]);
		if (C1 == 0) {
			strcat(Interface.Terminal_Entry, (Type == Get_Data) ? ".json" : ".so");
		}
		ktn_charcat(Interface.Terminal_Entry, '\"', sizeof(Interface.Terminal_Entry));
		if (C1 < ktn_veclen(Parameters) - 1) {
			strcat(Interface.Terminal_Entry, ", ");
		}
	}
	ktn_charcat(Interface.Terminal_Entry, ')', sizeof(Interface.Terminal_Entry));
}

void Process_Commands() {
	int Base = ktn_intlen(Buffers.Commands);
	Buffers.Commands[Base] = Execute;
	strncpy(Buffers.Parameters[Base][0], "clear", sizeof(Buffers.Parameters[Base][0]));
	strncpy(Buffers.Parameters[Base][1], ktn_null_string, sizeof(Buffers.Parameters[Base][1]));
	Buffers.Commands[Base + 1] = Execute;
	strncpy(Buffers.Parameters[Base + 1][0], "quit", sizeof(Buffers.Parameters[Base + 1][0]));
	strncpy(Buffers.Parameters[Base + 1][1], ktn_null_string, sizeof(Buffers.Parameters[Base + 1][1]));
	Buffers.Commands[Base + 2] = ktn_terminator;
}