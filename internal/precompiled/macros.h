#pragma once
#define ktn_min(A, B) ((A) > (B) ? (B) : (A))
#define ktn_max(A, B) ((A) > (B) ? (A) : (B))
#define ktn_free(Victim) do { if ((Victim)) { free(Victim); (Victim) = NULL; } } while (0)
#define ktn_memcpy(Victim, Source, Size) do { if ((Source) == NULL) { memset(Victim, 0, Size); } else { memcpy(Victim, \
    Source, Size); } } while (0)
#define ktn_intlen(Victim) ({ int Yield = 0; while ((Victim)[Yield] != ktn_terminator) { Yield++; } Yield; })
#define ktn_ptlen(Victim) ({ int Yield = 0; while ((Victim)[Yield].X != ktn_terminator || (Victim)[Yield].Y != \
    ktn_terminator) { Yield++; } Yield; })
#define ktn_veclen(Victim) ({ int Yield = 0; while (strcmp((Victim)[Yield], ktn_null_string)) { Yield++; } Yield; })
#define ktn_clamp(Victim, Low, High) (ktn_max(ktn_min((Victim), (High)), (Low)))
#define ktn_charcat(Victim, A, B) do { int Length = strlen(Victim); if (Length < B) { (Victim)[Length] = (A); (Victim)[ \
    Length + 1] = '\0'; } } while (0)
#define ktn_free_texture(Victim) do { if (Victim) { SDL_DestroyTexture(Victim); Victim = NULL; } } while (0)
#define ktn_load_bmp(Victim, Path) do { (Victim) = Load_BMP(Path); if ((Victim) == NULL) { char Carrier[128]; snprintf( \
    Carrier, sizeof(Carrier), "could not load image \"%s\"", Path); ktn_jump(I_No_Image, Carrier); } } while (0)
#define ktn_sqr(Victim) ((Victim) * (Victim))
#define ktn_evn(Victim) (((int)(Victim) & 1) == 0)
#define ktn_scale(Victim) (((int)(Victim)) * Settings.Scalar)
#define ktn_fscale(Victim) (((float)(Victim)) * (float)Settings.Scalar)
#define ktn_sgn(Victim) (((Victim) == 0) ? 0 : (((Victim) > 0) ? 1 : -1))
#define ktn_tick() do { Core.State = (Core.State * 2891336453u) + 747796405u; Core.State ^= Core.State >> 16; } while (0)
#define ktn_jump(Value, Text) do { strcpy(Exception_Text, Text); Exception_Value = Value; longjmp(Exception, Value); } while (0)
#define ktn_stricmp(A, B) (_stricmp((A), (B)) == 0)//add unix support via ifdef
#define ktn_reset_target() do { SDL_SetRenderTarget(Core.Renderer, Core.Game_Texture); } while (0)