// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#define ScreenDebug(color, text) if (GEngine != NULL) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::color, text)

#define ScreenInfo(text) ScreenDebug(White, text)
#define ScreenWarning(text) ScreenDebug(Yellow, text)
#define ScreenError(text) ScreenDebug(Red, text)


// COLOURS

#define OUTLINE_DEFAULT			FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)
#define OUTLINE_DESTRUCTABLE	FLinearColor(0.325f, 0.012f, 0.0f, 1.0f)