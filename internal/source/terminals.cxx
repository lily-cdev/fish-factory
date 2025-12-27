#include <ui.h>

std::vector<std::string> Errors = {
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

std::string To_Code(int Input) {
	std::string Yield;
	while (Input != 0) {
		int Intermediate = Input & 15;
		Yield.push_back(static_cast<char>(Intermediate < 10 ?
			Intermediate + 48 : Intermediate + 55));
		Input /= 16;
	}
	if (Yield.size() < 2) {
		Yield.insert(Yield.begin(), '0');
	}
	return Yield;
}

void Print_Error(int Input) {
	Interface_L.Terminal_Logs.insert(Interface_L.Terminal_Logs.begin(),
		": ERROR 0x" + To_Code(Input) + " -> " + Errors[Input]);
}

void Print_Fatal_Error(int Input) {
	std::string Text = "FATAL ERROR 0x" + To_Code(Input) + " -> " + Errors[Input];
	SDL_Surface* Carrying_Surface = TTF_RenderText_Blended(Fonts.Terminal_Font,
		Text.c_str(), Text.size(), Colors.Cherry_Blossom);
	SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(
		Core.Renderer, Carrying_Surface);
	SDL_FRect Destination = {
		(Settings.Screen_Size * 230.0f) - (Carrying_Surface->w * 0.5f),
		(Settings.Screen_Size * 180.0f) - (Carrying_Surface->h * 0.5f),
		static_cast<float>(Carrying_Surface->w),
		static_cast<float>(Carrying_Surface->h)
	};
	SDL_RenderTexture(Core.Renderer, Carrying_Texture,
		NULL, &Destination);
	SDL_DestroySurface(Carrying_Surface);
	SDL_DestroyTexture(Carrying_Texture);
	Render_Button(Textures.Error_Exit, Rects.Error_Exit, 3);
	if (Interface.UI_Selection == 3) {
		Interface_L.Terminal_Entry = Return_Command(Execute, { "quit" });
	}
	Tick_Input(3);
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

void Render_Sidebuttons(const Texture2_Array &Buttons, const Rect2_Array &Hitboxes) {
	for (int Counter = 0; Counter < Hitboxes.Length; Counter++) {
		Render_Button(Buttons.Data[Counter], Hitboxes.Data[Counter],
			Counter + 3, Colors.Pure_White);
	}
}

void Print_Response(std::string Response) {
	Interface_L.Terminal_Logs.insert(Interface_L.Terminal_Logs.begin(), ": " + Response + ".");
}

void Print_JSON(std::vector<std::string> Input) {
	Interface_L.Terminal_Logs.insert(Interface_L.Terminal_Logs.begin(), "{");
	std::string Comma = ",";
	for (int Counter = 0; Counter < Input.size(); Counter++) {
		if (Counter == Input.size() - 1) {
			Comma = "";
		}
		Interface_L.Terminal_Logs.insert(Interface_L.Terminal_Logs.begin(), "    \"" + Input[Counter] + "\"" + Comma);
	}
	Interface_L.Terminal_Logs.insert(Interface_L.Terminal_Logs.begin(), "}");
}

void Print_Input() {
	Interface_L.Terminal_Logs.insert(Interface_L.Terminal_Logs.begin(), "> " + Interface_L.Terminal_Entry);
	Temporary.Ticker_Position = 0;
	Temporary.Ticker_Frames = 0;
}

void Purge_Excess() {
	while (Interface_L.Terminal_Logs.size() > 11) {
		Interface_L.Terminal_Logs.pop_back();
	}
}

void Forward_Essentials(int Buttons, int Sliders) {
	Interface.Terminal_Clearing = false;
	if (Interface.UI_Selection > 2 && Interface.UI_Selection < Buttons + Sliders + 1) {
		Print_Input();
	}
	if (Interface.UI_Selection == Buttons + 1) {
		Interface_L.Terminal_Logs.clear();
		Interface.Terminal_Clearing = true;
	} else if (Interface.UI_Selection == Buttons + 2) {
		Interface.Prompt_Identifier = LDE_INVALID;
		Interface.Subprompt_Identifier = LDE_INVALID;
		Interface_L.Terminal_Logs.clear();
	}
}

void Backward_Essentials() {
	if (Interface.Terminal_Clearing) {
		Print_Response("cleared console log");
	}
}

void Render_Necessities(std::string Machine, std::string Prefix) {
	Render_Dynamic_Text(Fonts.Terminal_Font, "librenectere/" + Machine + ".exe",
		Colors.Cherry_Blossom, 50, 50);
	Render_Dynamic_Text(Fonts.Terminal_Font, "> ", Colors.Cherry_Blossom, 50, 300);
	if (Interface_L.Terminal_Entry.size() > 0) {
		Interface_L.Terminal_Entry = Prefix + "." + Interface_L.Terminal_Entry + ";";
		std::string Result = { };
		for (int Counter = 0; Counter < Interface_L.Terminal_Entry.size(); Counter++) {
			if (Counter >= Temporary.Ticker_Position || Counter > Interface_L.Terminal_Entry.size()) {
				break;
			}
			Result.push_back(Interface_L.Terminal_Entry[Counter]);
		}
		if (Result.size() > 0) {
			Render_Dynamic_Text(Fonts.Terminal_Font, Result, Colors.Cherry_Blossom, 64, 300);
		}
	}
	for (int Counter = static_cast<int>(Interface_L.Terminal_Logs.size()) - 1; Counter > LDE_INVALID; Counter--) {
		Render_Dynamic_Text(Fonts.Terminal_Font, Interface_L.Terminal_Logs[Counter],
			Colors.Cherry_Blossom, 50, 280 - (Counter * 20));
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

std::string Return_Command(int Type, std::vector<std::string> Parameters) {
	std::string Yield = "call";
	if (Type == Get_Data) {
		Yield = "open";
	}
	Yield.push_back('(');
	for (int Counter = 0; Counter < Parameters.size(); Counter++) {
		Yield.push_back('\"');
		Yield += Parameters[Counter];
		if (Counter == 0) {
			Yield.push_back('.');
			if (Type == Get_Data) {
				Yield += "json";
			} else {
				Yield += "dll";
			}
		}
		Yield.push_back('\"');
		if (Counter < Parameters.size() - 1) {
			Yield += ", ";
		}
	}
	Yield.push_back(')');
	return Yield;
}

void Process_Commands(std::vector<int> Types, std::vector<std::vector<std::string>> Parameters) {
	Types.push_back(Execute);
	Parameters.push_back({ "clear" });
	Types.push_back(Execute);
	Parameters.push_back({ "quit" });
	for (int Counter = 0; Counter < Types.size(); Counter++) {
		if (Interface.UI_Selection == Counter + 3) {
			Interface_L.Terminal_Entry = Return_Command(Types[Counter], Parameters[Counter]);
		}
	}
	for (int Counter = 3; Counter < Types.size() + 3; Counter++) {
		Tick_Input(Counter);
	}
}