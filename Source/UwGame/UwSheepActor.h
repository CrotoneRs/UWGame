#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UwSheepActor.generated.h"

UCLASS()
class UWGAME_API AUwSheepActor : public APawn
{
	GENERATED_BODY()

	UPROPERTY()
	class UUwBoidComponent* BoidComponent;

public:
	
	AUwSheepActor();
};
