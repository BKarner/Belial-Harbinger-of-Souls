// Paul Watkinson - 2014

#pragma once

#include "AGP.h"

/*
    FScreenText ScreenText; {
        ScreenText.Text = FString::SanitizeFloat(Damage.Amount / FLinearColor::Dist(Colour, Damage.Colour));
        ScreenText.Position = GetActorLocation();
        ScreenText.Velocity = FVector(500.0f, 0.0f, 0.0f);
		
		const FVector Direction = FMath::VRandCone(FVector(0.0f, 1.0f, 0.0f), PI * 0.5f);
		ScreenText.Acceleration = Direction * (FMath::RandHelper(50) > 25 ? -1.0f : 1.0f) * 250.0f;
		ScreenText.Acceleration.X = -1000.0f;

        ScreenText.Colour = FColor::Yellow;
        ScreenText.OutlineColour = FColor::Black;

        ScreenText.Lifetime = 1.0f;
        ScreenText.Scale = 0.5f;

        ScreenText.bShouldFadeOut = true;
        ScreenText.FadeOutBegin = 0.2f;
    }

    ScreenTextManager::AddText(ScreenText);
*/

struct FScreenText {
	uint32 ID;
    FString Text;
    FVector Position, Velocity, Acceleration;
    FColor Colour, OutlineColour;
    float Lifetime, Life;
    float Scale;
    
	bool bIsStatic;
    bool bIsOutlined;

	bool bShouldFadeOut;
    float FadeOutBegin;

	FScreenText(void) {
		ID = 0;
		Text = "UNINITIALISED";
		
		Position = Velocity = Acceleration = FVector::ZeroVector;

		Colour = FColor::Black;
		OutlineColour = FColor::White;

		Lifetime = 1.0f;
		Life = 0.0f;
		Scale = 1.0f;

		bIsOutlined = true;
		bIsStatic = false;

		bShouldFadeOut = true;
		FadeOutBegin = 0.5f;
	}
};

class AGP_API ScreenTextManager {
    private:
        TArray<FScreenText *> ScreenTexts;

        static ScreenTextManager * ManagerInstance;
		static uint32 NextID;

		ScreenTextManager() { }

    public:
		~ScreenTextManager() {
			ScreenTexts.Empty();
		}

        static ScreenTextManager * GetInstance(void) {
            if (ManagerInstance == NULL) {
                ManagerInstance = new ScreenTextManager();
            }

            return ManagerInstance;
        }

        static void ClearText(void) {
            ScreenTextManager * Instance = GetInstance();
            if (Instance == NULL) { return; }

            Instance->ScreenTexts.Empty();
        }

        static FScreenText * AddText(const FScreenText & Text) {
            ScreenTextManager * Instance = GetInstance();
            if (Instance == NULL) { return NULL; }

			FScreenText * SaveText = new FScreenText(Text);
			SaveText->ID = NextID++;

            Instance->ScreenTexts.Add(SaveText);

			return SaveText;
        }

		static bool RemoveText(const uint32 InID) {
			return (ManagerInstance->ScreenTexts.FindByPredicate([&](FScreenText * ScreenText) { return (ScreenText->ID == InID); }) != NULL);
		}

		static bool RemoveText(FScreenText * ScreenText) {
            return (ManagerInstance->ScreenTexts.Remove(ScreenText) > 0);
		}

        static void Tick(float DeltaSeconds) {
            ScreenTextManager * Instance = GetInstance();
            if (Instance == NULL) { return; }

            TArray<FScreenText *> ToRemove;

            for (auto ScreenText : Instance->ScreenTexts) {
				if (!ScreenText->bIsStatic) {
					if (ScreenText->Life + DeltaSeconds <= ScreenText->Lifetime) {
						ScreenText->Life += DeltaSeconds;
					}
					else {
						ToRemove.Add(ScreenText);
						continue;
					}
				}

				ScreenText->Velocity += ScreenText->Acceleration * DeltaSeconds;
                ScreenText->Position += ScreenText->Velocity * DeltaSeconds;

                if (ScreenText->bShouldFadeOut) {
                    float FadeOutTime = ScreenText->Lifetime * ScreenText->FadeOutBegin;
                    if (ScreenText->Life >= FadeOutTime) {
                        float Alpha = (uint8)((1 - ((ScreenText->Life - FadeOutTime) / (ScreenText->Lifetime - FadeOutTime))) * 255);
                        ScreenText->OutlineColour.A = ScreenText->Colour.A = Alpha;
                    }
                }
            }

            Instance->ScreenTexts.RemoveAll([&](FScreenText * ScreenText) { return ToRemove.Contains(ScreenText); });
        }

        static const TArray<FScreenText *> & GetScreenTexts(void) {
            return GetInstance()->ScreenTexts;
        }
};
