#include <Core.h>
#include <Preloader.h>
#include <Terminal_Handler.h>

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
	UI_Access.Terminal_Logs.insert(UI_Access.Terminal_Logs.begin(),
		": ERROR 0x" + To_Code(Input) + " -> " + Errors[Input]);
}

void Print_Fatal_Error(int Input) {
	std::string Text = "FATAL ERROR 0x" + To_Code(Input) + " -> " + Errors[Input];
	SDL_Surface* Carrying_Surface = TTF_RenderText_Blended(Fonts_Access.Terminal_Font,
		Text.c_str(), Text.size(), Colors_Access.Cherry_Blossom);
	SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(
		Core_Access.Application_Renderer, Carrying_Surface);
	SDL_FRect Destination = {
		(Settings_Access.Screen_Size * 230.0f) - (Carrying_Surface->w * 0.5f),
		(Settings_Access.Screen_Size * 180.0f) - (Carrying_Surface->h * 0.5f),
		static_cast<float>(Carrying_Surface->w),
		static_cast<float>(Carrying_Surface->h)
	};
	SDL_RenderTexture(Core_Access.Application_Renderer, Carrying_Texture,
		NULL, &Destination);
	SDL_DestroySurface(Carrying_Surface);
	SDL_DestroyTexture(Carrying_Texture);
	Render_Button(Textures_Access.Error_Exit, Rectangles_Access.Error_Exit, 3);
	if (UI_Access.UI_Selection == 3) {
		UI_Access.Terminal_Entry = Return_Command(Execute, { "quit" });
	}
	Tick_Input(3);
}

void Process_Exit() {
	if (UI_Access.UI_Selection == 3) {
		UI_Access.Prompt_Identifier = LDE_INVALID;
		UI_Access.Subprompt_Identifier = LDE_INVALID;
	}
}

void Render_Backing() {
	Render_Box(40, 40, 380, 280, Colors_Access.Abyss_Black, Colors_Access.Dark_Grey);
	Render_Box(460, 40, 140, 280, Colors_Access.Abyss_Black, Colors_Access.Dark_Grey);
}

void Render_Sidebuttons(const Texture2_Array &Buttons, const Rect2_Array &Hitboxes) {
	for (int Counter = 0; Counter < Hitboxes.Length; Counter++) {
		Render_Button(Buttons.Data[Counter], Hitboxes.Data[Counter],
			Counter + 3, Colors_Access.Pure_White);
	}
}

void Print_Response(std::string Response) {
	UI_Access.Terminal_Logs.insert(UI_Access.Terminal_Logs.begin(), ": " + Response + ".");
}

void Print_JSON(std::vector<std::string> Input) {
	UI_Access.Terminal_Logs.insert(UI_Access.Terminal_Logs.begin(), "{");
	std::string Comma = ",";
	for (int Counter = 0; Counter < Input.size(); Counter++) {
		if (Counter == Input.size() - 1) {
			Comma = "";
		}
		UI_Access.Terminal_Logs.insert(UI_Access.Terminal_Logs.begin(), "    \"" + Input[Counter] + "\"" + Comma);
	}
	UI_Access.Terminal_Logs.insert(UI_Access.Terminal_Logs.begin(), "}");
}

void Print_Input() {
	UI_Access.Terminal_Logs.insert(UI_Access.Terminal_Logs.begin(), "> " + UI_Access.Terminal_Entry);
	Temporary_Access.Ticker_Position = 0;
	Temporary_Access.Ticker_Frames = 0;
}

void Purge_Excess() {
	while (UI_Access.Terminal_Logs.size() > 11) {
		UI_Access.Terminal_Logs.pop_back();
	}
}

void Forward_Essentials(int Buttons, int Sliders) {
	UI_Access.Terminal_Clearing = false;
	if (UI_Access.UI_Selection > 2 && UI_Access.UI_Selection < Buttons + Sliders + 1) {
		Print_Input();
	}
	if (UI_Access.UI_Selection == Buttons + 1) {
		UI_Access.Terminal_Logs.clear();
		UI_Access.Terminal_Clearing = true;
	} else if (UI_Access.UI_Selection == Buttons + 2) {
		UI_Access.Prompt_Identifier = LDE_INVALID;
		UI_Access.Subprompt_Identifier = LDE_INVALID;
		UI_Access.Terminal_Logs.clear();
	}
}

void Backward_Essentials() {
	if (UI_Access.Terminal_Clearing) {
		Print_Response("cleared console log");
	}
}

void Render_Necessities(std::string Machine, std::string Prefix) {
	Render_Dynamic_Text(Fonts_Access.Terminal_Font, "librenectere/" + Machine + ".exe",
		Colors_Access.Cherry_Blossom, 50, 50);
	Render_Dynamic_Text(Fonts_Access.Terminal_Font, "> ", Colors_Access.Cherry_Blossom, 50, 300);
	if (UI_Access.Terminal_Entry.size() > 0) {
		UI_Access.Terminal_Entry = Prefix + "." + UI_Access.Terminal_Entry + ";";
		std::string Result = { };
		for (int Counter = 0; Counter < UI_Access.Terminal_Entry.size(); Counter++) {
			if (Counter >= Temporary_Access.Ticker_Position || Counter > UI_Access.Terminal_Entry.size()) {
				break;
			}
			Result.push_back(UI_Access.Terminal_Entry[Counter]);
		}
		if (Result.size() > 0) {
			Render_Dynamic_Text(Fonts_Access.Terminal_Font, Result, Colors_Access.Cherry_Blossom, 64, 300);
		}
	}
	for (int Counter = static_cast<int>(UI_Access.Terminal_Logs.size()) - 1; Counter > LDE_INVALID; Counter--) {
		Render_Dynamic_Text(Fonts_Access.Terminal_Font, UI_Access.Terminal_Logs[Counter],
			Colors_Access.Cherry_Blossom, 50, 280 - (Counter * 20));
	}
}

void Tick_Input(int Target, bool Slider) {
	int Cross_Checker = UI_Access.UI_Selection;
	if (Slider) {
		Cross_Checker = UI_Access.Engagement;
	}
	if (Cross_Checker == Target) {
		Temporary_Access.Ticker_Target = Target;
		if (Temporary_Access.Ticker_Position < 50) {
			Temporary_Access.Ticker_Frames++;
			if (Temporary_Access.Ticker_Frames > UI_Access.Frame_Rate / 20) {
				Temporary_Access.Ticker_Frames = 0;
				Temporary_Access.Ticker_Position++;
			}
		}
	} else {
		if (Temporary_Access.Ticker_Target == Target) {
			Temporary_Access.Ticker_Position = 0;
			Temporary_Access.Ticker_Frames = 0;
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
		if (UI_Access.UI_Selection == Counter + 3) {
			UI_Access.Terminal_Entry = Return_Command(Types[Counter], Parameters[Counter]);
		}
	}
	for (int Counter = 3; Counter < Types.size() + 3; Counter++) {
		Tick_Input(Counter);
	}
}