#include <connectables.h>

void Push_Bridge(Bridges* List, Bridge Input) {
	List->Length++;
	if (List->Length >= List->Full_Size) {
		Bridge* Buffer = malloc(sizeof(Bridge) * List->Length);
		memcpy_c(Buffer, List->Data, sizeof(Bridge) * List->Length);
		free_c(List->Data);
		List->Full_Size += 16;
		List->Data = malloc(sizeof(Bridge) * List->Full_Size);
		memcpy_c(List->Data, Buffer, sizeof(Bridge) * List->Length);
		free_c(Buffer);
	}
	List->Data[List->Length - 1] = Input;
}

void Pull_Bridge(Bridges* List, int Position) {
	if (List->Length > 0) {
		for (int C1 = Position; C1 < List->Length - 1; C1++) {
			List->Data[C1] = List->Data[C1 + 1];
		}
		List->Length--;
	}
}

void Clear_Bridges(Bridges* List) {
	List->Length = 0;
	List->Full_Size = 0;
	free_c(List->Data);
}

void Clear_Unconnected_Bridges(Bridges* List) {
	for (int C1 = 0; C1 < List->Length; C1++) {
		if (!List->Data[C1].Filled) {
			Pull_Bridge(List, C1);
		}
	}
}