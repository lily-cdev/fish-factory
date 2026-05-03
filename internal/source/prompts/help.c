#include <ui.h>

void Render_Help(Point Pos) {
    Render_Box((Point){ 10, 10 }, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
	for (int C1 = 0; C1 < 2; C1++) {
		Render_Texture(Textures.Help_Content.Data[C1], &Rects.Help_Content[C1]);
	}
	Render_Slider(Interface.Slider_Texts[3], 1, 2, &Interface.Slider_Positions[3], (Point){ 130, 300 }, 380, Colors.Abyss_Black,
		Colors.Cherry_Blossom, true);
	switch (Interface.Slider_Positions[3]) {
	case 0:
		{
			char Flavor[] = "[c]Welcome to Fish Factory! This game"
				" is in the alpha phase, so don't expect much.|More gameplay"
				" mechanics and customization options are planned for future updates."
				"| | | |Thank you for playing, and have fun!";
			Render_Rich_Text(F_Subtext, Flavor, (Point){ 20, 60 }, false, false);
		}
		break;
	case 1:
		{
			char Flavor[] = "[c]Tutorials involve placing items. The space occupied by the selected tutorial will be"
				" marked by a bounding|box. For an optimal experience, please ensure that the indicated area is free of"
				" obstructions.";
			Render_Rich_Text(F_Subtext, Flavor, (Point){ 20, 60 }, false, false);
		}
		if (Temporary.Tutorial_Step == ktn_invalid) {
			if (Data.CMD_Placed) {
				for (int C1 = 1; C1 < Textures.Tutorials.Length; C1++) {
					for (int C2 = 0; C2 < 2; C2++) {
						Rects.Tutorials.Data[C1].Data[C2].y -= ktn_fscale(ktn_tile_size);
					}
					Render_Button(&Textures.Tutorials.Data[C1], &Rects.Tutorials.Data[C1], (UI_Link){ (C1 == 1) ?
						Gen_Tutorial : Fish_Tutorial }, Colors.Cherry_Blossom);
					for (int C2 = 0; C2 < 2; C2++) {
						Rects.Tutorials.Data[C1].Data[C2].y += ktn_fscale(ktn_tile_size);
					}
				}
			} else {
				Render_Texture(Textures.CMD_Warning2, &Rects.CMD_Warning2);
				Render_Button(&Textures.Tutorials.Data[0], &Rects.Tutorials.Data[0], (UI_Link){ CMD_Tutorial },
					Colors.Cherry_Blossom);
			}
		} else {
			Render_Button(&Textures.Clear_Tutorial, &Rects.Clear_Tutorial, (UI_Link){ Cancel_Tutorial }, Colors.Cherry_Blossom);
		}
		break;
	case 2:
		{
			char Flavor[] = "The following cheat items are intentionally unbalanced."
				"| |You can use them for troubleshooting, bug-hunting, or just playing around.";
			Render_Rich_Text(F_Subtext, Flavor, (Point){ 20, 60 }, false, false);
		}
		for (int C1 = 0; C1 < 3; C1++) {
			Render_Button(&Textures.Cheats.Data[C1], &Rects.Cheats.Data[C1], (UI_Link){ Spawn_Cheat, .Param.Integer = C1 },
				Colors.Cherry_Blossom);
		}
		break;
	default:
		break;
	}
}