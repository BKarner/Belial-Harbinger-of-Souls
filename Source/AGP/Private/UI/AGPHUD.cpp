// Paul Watkinson - 2014

#include "AGP.h"
#include "ScreenTextManager.h"
#include "AGPHUD.h"

AAGPHUD::AAGPHUD(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer) {}

void AAGPHUD::DrawHUD() {
    Super::DrawHUD();

    const TArray<FScreenText *> ScreenTexts = ScreenTextManager::GetScreenTexts();

    for (const auto ScreenText : ScreenTexts) {
        FCanvasTextItem CanvasText(FVector2D(Canvas->Project(ScreenText->Position)), FText::FromString(ScreenText->Text), UE4Font, ScreenText->Colour); {
            CanvasText.bCentreX = true; CanvasText.bCentreY = true;
            CanvasText.Scale = FVector2D(1.0f, 1.0f) * ScreenText->Scale;

            CanvasText.bOutlined = ScreenText->bIsOutlined; 
            CanvasText.OutlineColor = ScreenText->OutlineColour;
        }

        Canvas->DrawItem(CanvasText);
    }
}