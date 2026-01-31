#include <ui.h>

void Process_Movement() {
	if (Interface.UD_Input != LDE_INVALID || Interface.LR_Input != LDE_INVALID) {
		int Increment = (Interface.Movespeed / Interface.Frame_Rate) * (((int)(Interface.Sprinting) * 4) + 1);
		if (Interface.UD_Input == 0) {
			Core.Camera.Y = Core.Camera.Y - Increment;
			Find_Effect();
			if (Core.Camera.Y < -LDE_BUFFERSIZE) {
				Core.Camera.Y = -LDE_BUFFERSIZE;
				Interface.UD_Input = LDE_INVALID;
			}
		} else if (Interface.UD_Input == 1) {
			Core.Camera.Y = Core.Camera.Y + Increment;
			Find_Effect();
			if (Core.Camera.Y > Interface.Map_Y) {
				Core.Camera.Y = Interface.Map_Y;
				Interface.UD_Input = LDE_INVALID;
			}
		}
		if (Interface.LR_Input == 0) {
			Core.Camera.X = Core.Camera.X - Increment;
			Find_Effect();
			if (Core.Camera.X < -LDE_BUFFERSIZE) {
				Core.Camera.X = -LDE_BUFFERSIZE;
				Interface.LR_Input = LDE_INVALID;
			}
		} else if (Interface.LR_Input == 1) {
			Core.Camera.X = Core.Camera.X + Increment;
			Find_Effect();
			if (Core.Camera.X > Interface.Map_X) {
				Core.Camera.X = Interface.Map_X;
				Interface.LR_Input = LDE_INVALID;
			}
		}
	}
}