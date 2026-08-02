#include <connectables.h>

void Push_Bridge(Bridges* List, Bridge Input) {
	if (List->Length >= List->Full_Size) {
		Bridge* Buffer = malloc(sizeof(Bridge) * List->Length);
		ktn_memcpy(Buffer, List->Data, sizeof(Bridge) * List->Length);
		ktn_free(List->Data);
		List->Full_Size += 16;
		List->Data = malloc(sizeof(Bridge) * List->Full_Size);
		ktn_memcpy(List->Data, Buffer, sizeof(Bridge) * List->Length);
		ktn_free(Buffer);
	}
	List->Data[List->Length] = Input;
	List->Length++;
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
	ktn_free(List->Data);
}

void Clear_Unconnected_Bridges(Bridges* List) {
	for (int C1 = 0; C1 < List->Length; C1++) {
		if (!List->Data[C1].Filled) {
			Pull_Bridge(List, C1);
		}
	}
}