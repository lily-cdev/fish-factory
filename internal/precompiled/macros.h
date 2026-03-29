#pragma once
#define free_c(Victim) do { if ((Victim) != NULL) { free(Victim); (Victim) = NULL; } } while(0)
#define memcpy_c(Victim, Source, Size) do { if ((Source) == NULL) { memset(Victim, 0, Size); } else { memcpy(Victim, \
    Source, Size); } } while (0)
#define intlen(Victim) ({ int Yield = 0; while ((Victim)[Yield] != LDE_TERMINATOR) { Yield++; } Yield; })
#define reclen(Victim) ({ int Yield = 0; while ((Victim)[Yield].ID != LDE_TERMINATOR) { Yield++; } Yield; })
#define ptlen(Victim) ({ int Yield = 0; while ((Victim)[Yield].X != LDE_TERMINATOR || (Victim)[Yield].Y != \
    LDE_TERMINATOR) { Yield++; } Yield; })
#define veclen(Victim) ({ int Yield = 0; while (strcmp((Victim)[Yield], NULLSTRING) != 0) { Yield++; } Yield; })
#define clamp_c(Victim, A, B) ({ int Yield = (Victim); if ((A) < (B)) { if ((Victim) < (A)) { Yield = (A); } else if \
    ((Victim) > (B)) { Yield = (B); } } else { if ((Victim) < (B)) { Yield = (B); } else if ((Victim) > (A)) { Yield = \
    (A); } } Yield; })
#define charcat(Victim, A, B) do { int Length = strlen(Victim); if (Length < B) { (Victim)[Length] = (A); (Victim)[ \
    Length + 1] = '\0'; } } while(0)
#define free_texture(Victim) do { if (Victim != NULL) { SDL_DestroyTexture(Victim); Victim = NULL; } } while(0)
#define jump(Value, Text) do { strcpy(Exception_Text, Text); Exception_Value = Value; longjmp(Exception, Value); } while(0)
#define load_bmp(Victim, Path) do { (Victim) = Load_BMP(Path); if ((Victim) == NULL) { char Carrier[128]; snprintf( \
    Carrier, sizeof(Carrier), "could not load image \"%s\"", Path); jump(I_No_Image, Carrier); } } while(0)
#define sqr(Victim) ((Victim) * (Victim))
#define strcat_c(Victim, Source, Length) do { strncat(Victim, Source, Length - strlen(Source) - 1); } while(0)
#define evn(Victim) (((int)(Victim) & 1) == 0)
#define pt(Victim) (Victim.X)][(Victim.Y)