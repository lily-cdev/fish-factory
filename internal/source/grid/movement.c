#include <ui.h>

void Process_Movement() {
	if (Interface.UD_Input != ktn_invalid || Interface.LR_Input != ktn_invalid) {
		int Increment = (Interface.Movespeed / Interface.Frame_Rate) * (((int)(Interface.Sprinting) * 4) + 1);
		if (Interface.UD_Input == 0) {
			Core.Camera.Y = Core.Camera.Y - Increment;
			Find_Effect();
			if (Core.Camera.Y < -ktn_buffer_size) {
				Core.Camera.Y = -ktn_buffer_size;
				Interface.UD_Input = ktn_invalid;
			}
		} else if (Interface.UD_Input == 1) {
			Core.Camera.Y = Core.Camera.Y + Increment;
			Find_Effect();
			if (Core.Camera.Y > Interface.Map_Y) {
				Core.Camera.Y = Interface.Map_Y;
				Interface.UD_Input = ktn_invalid;
			}
		}
		if (Interface.LR_Input == 0) {
			Core.Camera.X = Core.Camera.X - Increment;
			Find_Effect();
			if (Core.Camera.X < -ktn_buffer_size) {
				Core.Camera.X = -ktn_buffer_size;
				Interface.LR_Input = ktn_invalid;
			}
		} else if (Interface.LR_Input == 1) {
			Core.Camera.X = Core.Camera.X + Increment;
			Find_Effect();
			if (Core.Camera.X > Interface.Map_X) {
				Core.Camera.X = Interface.Map_X;
				Interface.LR_Input = ktn_invalid;
			}
		}
	}
}