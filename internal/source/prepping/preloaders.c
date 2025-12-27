#include <prepping.h>

void Preload_Fonts() {
	Fonts.Logo_Font = TTF_OpenFont("Assets/Core/Fonts/Oxygen/Oxygen_Regular.ttf",
		Settings.Screen_Size * 32);
	Fonts.Large_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings.Screen_Size * 24);
	Fonts.Text_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings.Screen_Size * 18);
	Fonts.Halftext_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings.Screen_Size * 16);
	Fonts.Subtext_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings.Screen_Size * 12);
	Fonts.Microtext_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings.Screen_Size * 10);
	Fonts.Terminal_Font = TTF_OpenFont("Assets/Core/Fonts/Oxygen/Oxygen_Regular.ttf",
		Settings.Screen_Size * 12);
}