#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UwBoidComponent.generated.h"


UCLASS( )
class UWGAME_API UUwBoidComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class UUwBoidSubsystem;

	uint32 BiodID = 0u;

	FVector Position;
	FVector Velocity;

public:	
	UUwBoidComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
