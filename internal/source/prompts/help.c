#include <ui.h>

void Render_Help(int X, int Y) {
    Render_Box(10, 10, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
	for (int Counter = 0; Counter < 2; Counter++) {
		Render_Texture(Textures.Help_Content.Data[Counter], &Rects.Help_Content[Counter]);
	}
	Render_Slider(Interface.Slider_Texts[3], 1, 2, 1, &Interface.Slider_Positions[3], 130, 300, 380,
		Colors.Abyss_Black, Colors.Cherry_Blossom, true);
	switch (Interface.Slider_Positions[3]) {
	case 0:
		{
			char Flavor[] = "[c]Welcome to Fish Factory! This game"
				" is in the alpha phase, so don't expect much.|More gameplay"
				" mechanics and customization options are planned for future updates."
				"| | | |Thank you for playing, and have fun!";
			Render_Rich_Text(Fonts.Subtext_Font, Flavor, 20, 60, false, false);
		}
		break;
	case 1:
		{
			char Flavor[] = "[c]Tutorials involve placing items. The space"
			" occupied by the selected tutorial will be marked by a bounding|box. For an optimal"
			" experience, please ensure that the indicated area is free of obstructions.";
			Render_Rich_Text(Fonts.Subtext_Font, Flavor, 20, 60, false, false);
		}
		if (Temporary.Tutorial_Step == LDE_INVALID) {
			if (Data.CMD_Placed) {
				for (int Counter = 1; Counter < Textures.Tutorials.Length; Counter++) {
					Rects.Tutorial_Hitbox.Data = Rects.Tutorials.Data[Counter].Data;
					Rects.Tutorial_Hitbox.Data[0].y -= LDE_TILESIZE * Settings.Screen_Size;
					Rects.Tutorial_Hitbox.Data[1].y -= LDE_TILESIZE * Settings.Screen_Size;
					Render_Button(&Textures.Tutorials.Data[Counter], &Rects.Tutorial_Hitbox, Counter + 3,
						Colors.Cherry_Blossom);
				}
			} else {
				Render_Texture(Textures.CMD_Warning2, &Rects.CMD_Warning2);
				Render_Button(&Textures.Tutorials.Data[0], &Rects.Tutorials.Data[0], 3, Colors.Cherry_Blossom);
			}
		} else {
			Render_Button(&Textures.Clear_Tutorial, &Rects.Clear_Tutorial, 2, Colors.Cherry_Blossom);
		}
		break;
	case 2:
		{
			char Flavor[] = "The following cheat items are intentionally unbalanced."
				"| |You can use them for troubleshooting, bug-hunting, or just playing around.";
			Render_Rich_Text(Fonts.Subtext_Font, Flavor, 20, 60, false, false);
		}
		for (int Counter = 0; Counter < 2; Counter++) {
			Render_Button(&Textures.Cheats.Data[Counter], &Rects.Cheats.Data[Counter], Counter + 2, Colors.Cherry_Blossom);
		}
		break;
	default:
		break;
	}
}