#pragma once
#define free_c(Victim) do { if ((Victim) != NULL) { free(Victim); (Victim) = NULL; } } while(0)
#define free_d(Victim) do { free_c(Victim.Data); } while(0)