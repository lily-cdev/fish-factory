#pragma once

typedef struct {
    int Length;
    char** Data;
} String2;

typedef struct {
    int Length;
    String2* Data;
} String3;

typedef struct {
    int Length;
    String3* Data;
} String4;

typedef struct {
    int X;
    int Y;
} Point;

typedef struct {
    int Length;
    Point* Data;
} Node;

typedef struct {
    int Full_Size;
    int Length;
    Point* Data;
} Node_d;

typedef struct {
    float X;
    float Y;
} Point_f;

typedef struct {
    double X;
    double Y;
} Point_d;

typedef struct {
    int Length;
    SDL_Texture** Data;
} Texture_Array;

typedef struct {
    int Length;
    Texture_Array* Data;
} Texture2_Array;

typedef struct {
    int Length;
    Texture2_Array* Data;
} Texture3_Array;

typedef struct {
    int Length;
    SDL_FRect* Data;
} Rect_Array;

typedef struct {
    int Length;
    Rect_Array* Data;
} Rect2_Array;

typedef struct {
    int Length;
    Rect2_Array* Data;
} Rect3_Array;