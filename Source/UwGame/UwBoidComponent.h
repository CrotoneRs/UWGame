#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UwBoidComponent.generated.h"


UCLASS( )
class UWGAME_API UUwBoidComponent : public UActorComponent
{
	GENERATED_BODY()

	FVector Velocity;

public:	
	UUwBoidComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
